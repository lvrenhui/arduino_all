/*

  Sets the time and prints back time stamps for 5 seconds

  Based on DS3231_set.pde
  by Eric Ayars
  4/11

  Added printing back of time stamps and increased baud rate
  (to better synchronize computer and RTC)
  Andy Wickert
  5/15/2011

*/

#include <DS3231.h>
#include <Wire.h>

DS3231 Clock;

byte Year;
byte Month;
byte Date;
byte DoW;
byte Hour;
byte Minute;
byte Second;

bool Century = false;
bool h12;
bool PM;

void setup() {
  // Start the serial port
  Serial.begin(9600);

  // Start the I2C interface
  Wire.begin();


//  Clock.setClockMode(false);  // set to 24h
//  //setClockMode(true); // set to 12h
//
//  Clock.setYear(20);
//  Clock.setMonth(4);
//  Clock.setDate(18);
//  Clock.setDoW(DoW);
//  Clock.setHour(16);
//  Clock.setMinute(18);
//  Clock.setSecond(45);

}

void loop() {

  // If something is coming in on the serial line, it's
  // a time correction so set the clock accordingly.


  // Give time at next five seconds

  Serial.print(Clock.getYear(), DEC);
  Serial.print("-");
  Serial.print(Clock.getMonth(Century), DEC);
  Serial.print("-");
  Serial.print(Clock.getDate(), DEC);
  Serial.print(" ");
  Serial.print(Clock.getHour(h12, PM), DEC); //24-hr
  Serial.print(":");
  Serial.print(Clock.getMinute(), DEC);
  Serial.print(":");
  Serial.print(Clock.getSecond(), DEC);

  Serial.println();


  delay(1000);
}
