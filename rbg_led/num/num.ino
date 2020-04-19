/*
   NOTE: The code below is based on the "strandtest" example that comes with
   the Adafruit NeoPixel library.  I left in most of the original comments.
*/

// Left as-is from the example
#include <Adafruit_NeoPixel.h>
#include "timer.h"
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 6


uint32_t color = 0;
int last_show = 0; //控制2个点的显示

int led_nums = 30;

Timer timer;
// All of this stuff below is from the example
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(led_nums, PIN, NEO_GRB + NEO_KHZ800);

//NOTE: I tested this code with an 8 LED module, but you should be able to daisy chain multiple modules
//NOTE: Try changing the "8" to "4" to see how it reacts.

// This warning is from the example, probably worth considering
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This stuff is from the example, I commented it out since I am not using a Trinket
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  //#if defined (__AVR_ATtiny85__)
  // if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  //#endif
  // End of trinket special code

  Serial.begin(9600); //9600（PC端使用）

  timer.setInterval(1000);
  timer.setCallback(showTimeTick);
  timer.start();

  strip.begin();
  strip.setBrightness(20);
  color = strip.Color(255, 255, 255);
  clearLights();

  showTime();

}

void loop() {
  timer.update();
}

void showTimeTick() {
  int tick1 = led_nums - 2, tick2 = led_nums - 1; //最后两个灯

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

void showTime() {

  light_num(1, 1);
  light_num(2, 5);
  light_num(3, 1);
  light_num(4, 0);

}

void light_num(int order, int num) {
  int* arr = getNumArr(num);
  int deta = (order - 1) * 7;
  for (int i = 0; i < 7; i++) {
    int val = *(arr + i);
    Serial.print("\n");
    Serial.print(val);
    if (val != 0) {
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


int* getNumArr( int num) {
  int nums[][7] = {
    { 1, 1, 1, 0, 1, 1, 1 },
    { 0, 0, 1, 0, 0, 0, 1 },
    { 0, 1, 1, 1, 1, 1, 0 },
    { 0, 1, 1, 1, 0, 1, 1 },
    { 1, 0, 1, 1, 0, 0, 1 },
    { 1, 1, 0, 1, 0, 1, 1 },
    { 1, 1, 0, 1, 1, 1, 1 },
    { 0, 1, 1, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 0, 1, 1 }
  };

  int * tmp = nums[num];
  static int arr[7];

  for (int i = 0; i < 7; i++) {

    arr[i] = *(tmp + i);
  }
  return arr;

}
