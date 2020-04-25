#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
#include "timer.h"
#ifdef __AVR__
#include <avr/power.h>
#endif
#include <Wire.h>
#include "DS3231.h"
#define WS2812_PIN 6
#define CLOCK_LED_NUMS  30
RTClib RTC;
Timer timer_tick, timer_clock, timer_color;

int color_minute = 0;//根据分钟变化颜色
uint32_t color = 0; //时钟颜色
int last_show = 0; //控制2个点的显示
int mode = 1; // 1 普通,2 彩虹,3调亮度,4熄灯

int BRIGHT_VAL = 20; //亮度

//SoftwareSerial BTSerial(10, 11); //蓝牙读写
Adafruit_NeoPixel strip = Adafruit_NeoPixel(CLOCK_LED_NUMS, WS2812_PIN, NEO_GRB + NEO_KHZ800);


uint32_t white = strip.Color(255, 255, 255);
uint32_t red = strip.Color(255, 0, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t blue = strip.Color (0, 0, 255);
uint32_t purple = strip.Color(160 , 32 , 240);
uint32_t  yellow = strip.Color(255 , 255 , 0);
uint32_t magenta = strip.Color(255, 0, 255);
uint32_t cyan = strip.Color(0, 255, 255);
uint32_t orange = strip.Color(255, 165, 0);

int* clock_arr;
int updating = 0; //更新中不刷新，防止数据为更新完显示不完整

void setup() {
  Serial.begin(9600); //9600（PC端使用）
  //  BTSerial.begin(9600); //蓝牙频率

  Wire.begin();//RTC时钟

  timer_tick.setInterval(1000);
  timer_tick.setCallback(showTick);
  timer_tick.start();
  //
  timer_clock.setInterval(3000);
  timer_clock.setCallback(showTimeNow);
  timer_clock.start();

  //  timer_color.setInterval(60000);
  //  timer_color.setCallback(changeColor);
  //  timer_color.start();

  strip.begin();
  strip.setBrightness(BRIGHT_VAL);
  color = strip.Color(255, 255, 255);
  //  clearLights();
  strip.clear();

  //  showTimeNow();
  TestLED();

}

void loop() {

  //  bluetoothListen(); 太耗电了，不用控制颜色了
  timer_tick.update();
  timer_clock.update();
}
/**
  void bluetoothListen() {
  if (BTSerial.available()) {
    char d = BTSerial.read();
    //    Serial.print(d);
    switch (d) {
      case '1':
        color = red;
        mode = 1;
        break;
      case '2':
        color = green;
        mode = 1;
        break;
      case '3':
        color = blue;
        mode = 1;
        break;
      case '4':
        color = yellow;
        mode = 1;
        break;
      case '5':
        color = white;
        mode = 1;
        break;
      case '6':
        color = purple;
        mode = 1;
        break;
      case '7':
        color = magenta;
        mode = 1;
        break;
      case '8':
        color = cyan;
        mode = 1;
        break;
      case '9':
        color = orange;
        mode = 1;
        break;
      case 'y':
        color = white;
        mode = 2;
        break;
      case 'z':
        color = 0;
        mode = 1;
        break;
      case 'L':
        light_adjust(1);
        mode = 3;
        break;
      case 'H':
        light_adjust(2);
        mode = 3;
        break;
    }
    light_up();
  }
  }
**/

void light_adjust(int level) {
  int val = 0;
  if (level == 1) {
    val = BRIGHT_VAL - 10;
  } else {
    val = BRIGHT_VAL + 10;
  }
  if (val <= 0) {
    val = 1;
  }
  if (val >= 255) {
    val = 255;
  }
  BRIGHT_VAL = val;
  strip.setBrightness(BRIGHT_VAL);
}

void changeColor() {
  switch (color_minute % 6) {
    case 0:
      color = white;
      break;
    case 1:
      color = red;
      break;
    case 2:
      color = green;
      break;
    case 3:
      color = blue;
      break;
    case 4:
      color = yellow;
      break;
    case 5:
      color = purple;
      break;
  }
}
void showTimeNow() {
  DateTime now = RTC.now();
  int hour = now.hour();
  int hour1 = hour / 10;
  int hour2 = hour % 10;

  int minute = now.minute();
  int min1 = minute / 10;
  int min2 = minute % 10;

  //  int second = now.second();
  //  Serial.println(second);
  if (hour < 6) {
    mode = 4; //熄灯了
  } else {
    mode = 1;
  }

  //  if (minute != color_minute) {
  //    color_minute = minute;
  //    changeColor();
  //  }
  updating = 1; //开始更新
  updateClockArr(hour1, hour2, min1, min2);
  updating = 0; //更新结束

  light_up();
}

void light_up() {
  if (updating == 1) {
    return;
  }
  if (mode == 1) {
    light_color();
  }
  if (mode == 2) {
    light_rainbow();
  }
  if (mode == 4) {
    strip.clear();
    strip.show();
    //    clearLights();
  }
}

void updateClockArr(int hour1, int hour2, int min1, int min2) {

  int arr[CLOCK_LED_NUMS], tmp1[14], tmp2[14];
  //  int* arr = new int[30], tmp1 = new int[14], tmp2 = new int[14];
  int* arr1 = getNumArr(hour1);
  int* arr2 = getNumArr(hour2);
  int* arr3 = getNumArr(min1);
  int* arr4 = getNumArr(min2);

  append_array(arr1, arr2, tmp1, 7, 7);
  append_array(arr3, arr4, tmp2, 7, 7);
  append_array(tmp1, tmp2, arr, 14, 14);
  arr[CLOCK_LED_NUMS - 2] = 1;
  arr[CLOCK_LED_NUMS - 1] = 1;

  //  Serial.println(arr[CLOCK_LED_NUMS - 2]);
  //  Serial.println(arr[CLOCK_LED_NUMS - 1]);

  clock_arr = arr;

  //疑似内存不够，导致数据错乱
  delete arr1;
  delete arr2;
  delete arr3;
  delete arr4;
}

int* getNumArr( int num) {
  int nums[][7] = {
    { 1, 1, 1, 0, 1, 1, 1 }, //0
    { 0, 0, 1, 0, 0, 0, 1 }, //1
    { 0, 1, 1, 1, 1, 1, 0 }, //2
    { 0, 1, 1, 1, 0, 1, 1 }, //3
    { 1, 0, 1, 1, 0, 0, 1 }, //4
    { 1, 1, 0, 1, 0, 1, 1 }, //5
    { 1, 1, 0, 1, 1, 1, 1 }, //6
    { 0, 1, 1, 0, 0, 0, 1 }, //7
    { 1, 1, 1, 1, 1, 1, 1 }, //8
    { 1, 1, 1, 1, 0, 1, 1 } //9
  };

  int * tmp = nums[num];
  //  static int arr[7]; //这里不能用staic;否则后面多次获得的值是一样的
  int* arr = new int[7];

  for (int i = 0; i < 7; i++) {
    arr[i] = *(tmp + i);
  }
  return arr;
}



void append_array(int* a, int* b, int* c, int n1, int n2)
{
  int i;

  for (i = 0; i < n1 + n2; i++)
  {
    if (i < n1)
      c[i] = a[i];
    else
      c[i] = b[i - n1];
  }
}

void showTick() {
  if (mode == 4) { //熄灯了
    strip.clear();
    strip.show();
    //    clearLights();
    return;
  }

  int tick1 = CLOCK_LED_NUMS - 2, tick2 = CLOCK_LED_NUMS - 1; //最后两个灯

  if (last_show == 1) {

    strip.setPixelColor(tick1, 0);
    strip.setPixelColor(tick2, 0);
    last_show = 0;
  } else {
    strip.setPixelColor(tick1, color);
    strip.setPixelColor(tick2, color);
    last_show = 1;
  }
  strip.show();

}

void TestLED() {
  //  light_clock();
  //  light_num(1, 1);
  //  light_num(2, 2);
  //  light_num(3, 3);
  //  light_num(4, 4);

  for (int i = 0; i < CLOCK_LED_NUMS; i++) {
    strip.setPixelColor(i , color);
  }
  strip.show();
}

void light_color()
{
  for (int i = 0; i < CLOCK_LED_NUMS; i++) {
    if (*(clock_arr + i) == 1) {
      strip.setPixelColor(i , color);
    } else {
      strip.setPixelColor(i , 0);
    }
  }
  strip.show();
}

void light_rainbow() {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < CLOCK_LED_NUMS; i++) { // For each pixel in strip...
      if (i == CLOCK_LED_NUMS - 1 || i == CLOCK_LED_NUMS - 2) {
        continue;
      }
      if (*(clock_arr + i) == 1) {
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      } else {
        strip.setPixelColor(i, 0);
      }
    }
  }
  strip.show(); // Update strip with new contents
}


void light_num(int order, int num) {
  int* arr = getNumArr(num);
  int deta = (order - 1) * 7;
  for (int i = 0; i < 7; i++) {
    int val = *(arr + i);
    //    Serial.print("\n");
    //    Serial.print(val);
    if (val == 0) {
      strip.setPixelColor(i + deta, 0);
    } else {
      strip.setPixelColor(i + deta, color);
    }
  }
  strip.show();
}

void clearLights() {
  for (int i = 0; i < strip.numPixels(); i = i + 1) {
    strip.setPixelColor(i, 0);    //turn every pixel off
  }
  strip.show();
}
