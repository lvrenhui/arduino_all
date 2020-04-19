/*
 * NOTE: The code below is based on the "strandtest" example that comes with
 * the Adafruit NeoPixel library.  I left in most of the original comments.
 */

// Left as-is from the example
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 6

// All of this stuff below is from the example
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, PIN, NEO_GRB + NEO_KHZ800);

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
  strip.begin();
  strip.show();
}

void loop() {
  /*
   * For strip.Color(R, G, B), use 0-255 to set intensity
   * for each color (R)ed, (G)reen, (B)lue
   *
   * The last number is a delay 0-255 range.
   */

  // These are left/right signals
  ArrowLeft(strip.Color(0, 0, 255), 100); // Blue
  ArrowRight(strip.Color(255, 0, 0), 200); //Red

  // These are side to side or wig/wag
  WigWag(strip.Color(255, 0, 0), 200); // Red
  WigWag(strip.Color(0, 0, 255), 63); // Blue faster
  WigWag(strip.Color(0, 0, 255), 127); // Blue medium
  WigWag(strip.Color(0, 0, 255), 255); // Blue slowest
  WigWag(strip.Color(0, 255, 0), 200); // Green
  WigWag(strip.Color(255, 255, 0), 200); // Yellow
  ClearLights();
  delay(1000);
  // This is a 2 color wigwag
  WigWag2(strip.Color(0, 0, 255), strip.Color(255, 0, 0), 200); // Blue and Red
  ClearLights();
  delay(1000);

  // Blinks the outer most lights
  BlinkOuter(strip.Color(0, 0, 255), 200); //Blue
  BlinkOuter(strip.Color(0, 0, 255), 50); //Blue faster
  BlinkOuter(strip.Color(255, 255, 0), 200); //Yellow
  ClearLights();
  delay(1000);

  // Turns the outer most lights on
  OnOuter(strip.Color(63, 0, 0)); // Red 25%
  OnOuter(strip.Color(127, 0, 0)); // Red 50%
  OnOuter(strip.Color(191, 0, 0)); // Red 75%
  OnOuter(strip.Color(255, 0, 0)); // Red 100%
  ClearLights();
  delay(1000);
  OnOuter(strip.Color(0, 0, 255)); // Blue
  OnOuter(strip.Color(0, 255, 0)); // Green
  // Turns off all lights
  ClearLights();
  delay(5000);
}

void ArrowRight(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 4; j++) { // The j<# determines how many cycles
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
    }
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 0);
    }
    strip.show();
    delay(wait);
  }
}

void ArrowLeft(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 4; j++) { // The j<# determines how many cycles
    for (uint16_t i = strip.numPixels(); i + 1 > 0 ; i--) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
    }
    for (uint16_t i = strip.numPixels(); i + 1 > 0 ; i--) {
      strip.setPixelColor(i, 0);
    }
    strip.show();
    delay(wait);
  }
}

void WigWag(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { // The j<# determines how many cycles
    for (int i = 0; i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, c);
    }
    for (int i = (strip.numPixels() / 2); i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, 0);
    }
    strip.show();
    delay(wait);

    for (int i = 0; i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, 0);
    }
    for (int i = (strip.numPixels() / 2); i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, c);
    }
    strip.show();
    delay(wait);
  }
}


void WigWag2(uint32_t c, uint32_t c2, uint8_t wait) {
  for (int j = 0; j < 20; j++) { // The j<# determines how many cycles
    for (int i = 0; i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, c);
    }
    for (int i = (strip.numPixels() / 2); i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, 0);
    }
    strip.show();
    delay(wait);

    for (int i = 0; i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, 0);
    }
    for (int i = (strip.numPixels() / 2); i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, c2);
    }
    strip.show();
    delay(wait);
  }
}

void ClearLights() {
  for (int i = 0; i < strip.numPixels(); i = i + 1) {
    strip.setPixelColor(i, 0);    //turn every pixel off
  }
  strip.show();
}

void BlinkOuter(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { // The j<# determines how many cycles
    strip.setPixelColor(strip.numPixels() - 1, c);
    strip.setPixelColor(0, c);
    strip.show();
    delay(wait);
    strip.setPixelColor(strip.numPixels() - 1, 0);
    strip.setPixelColor(0, 0);
    strip.show();
    delay(wait);
  }
}

void OnOuter(uint32_t c) {
  strip.setPixelColor(strip.numPixels() - 1, c);
  strip.setPixelColor(0, c);
  strip.show();
  delay(3000);
}
