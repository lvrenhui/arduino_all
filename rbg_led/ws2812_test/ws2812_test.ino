/*
   NOTE: The code below is based on the "strandtest" example that comes with
   the Adafruit NeoPixel library.  I left in most of the original comments.
*/

// Left as-is from the example
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include "timer.h"
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 6

int NUMS=30;

SoftwareSerial BTSerial(10, 11); // RX | TX

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMS, PIN, NEO_GRB + NEO_KHZ800);
Timer timer_tick;

uint32_t c = 0;
uint32_t white = strip.Color(255, 255, 255);
uint32_t red = strip.Color(255, 0, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t blue = strip.Color (0, 0, 255);
uint32_t purple = strip.Color(160 , 32 , 240);
uint32_t  yellow = strip.Color(255 , 255 , 0);
char d;

void setup() {
  // This stuff is from the example, I commented it out since I am not using a Trinket
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  //#if defined (__AVR_ATtiny85__)
  // if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  //#endif
  // End of trinket special code
  strip.begin();
  strip.show();

  c = strip.Color(0, 0, 255);
  Serial.begin(9600);
  BTSerial.begin(9600);

  timer_tick.setInterval(200);
  timer_tick.setCallback(Test);
  timer_tick.start();
}

void loop() {

  timer_tick.update();

  if (BTSerial.available()) {
    d = BTSerial.read();
    switch (d) {
      case '1':
        c = 0;
        break;
      case '2':
        c = red;
        break;
      case '3':
        c = green;
        break;
      case '4':
        c = yellow;
        break;
      case '5':
        c = white;
        break;
    }
  }

}

void Test() {
  for (int j = 0; j < strip.numPixels(); j++) {
    strip.setPixelColor(j, c);
  }
  strip.show();
}
