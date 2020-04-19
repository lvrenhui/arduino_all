/*
  Police Chaser Lights
  Author: Jista Awesome
  Date: December 2, 2016

  This program flashes the middle red and blue LED and the LED directly to the left of
  each color. Then flashes the middle red and blue LED as well as the LED directly to the
  Right of each color.
*/

#include "TaskScheduler.h"

// the setup function runs once when you press reset or power the board
void setup() {
  //                      RED LED's <   >BLUE LED's
  // initialize digital pin 13, 12, 11, 10, 9, 8 as an output.
  pinMode(13, OUTPUT);  //Left Red
  pinMode(12, OUTPUT);  //Middle Red
  pinMode(11, OUTPUT);  //Right Red
  pinMode(10, OUTPUT);  //Left Blue
  pinMode(9, OUTPUT);   //Middle Blue
  pinMode(8, OUTPUT);   //Right Blue

  Sch.init();
  Sch.addTask(led_task, 0, 1, 1); // Add task1. Starts at the 0th ms, and runs every 1000 ms
  //  Sch.addTask(voice_task, 20, 10, 1); // Add task2. Starts at the 20th ms, and runs every 500 ms
  Sch.start();
}

// the loop function runs over and over again forever
void loop() {
  Sch.dispatchTasks();

}

void led_task() {
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(9,  HIGH);
  delay(100);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
  delay(100);
  /////LED Alternate sides/////
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9,  HIGH);
  delay(100);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  delay(100);

  led_test();

}

void led_test() {
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  delay(150);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  delay(50);
  /////LED Alternate sides/////
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  delay(150);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  delay(50);
}

void voice_task() {
  for (int i = 200; i <= 800; i++)             //用循环的方式将频率从200HZ 增加到800HZ
  {
    pinMode(4, OUTPUT);
    tone(4, i);                           //在四号端口输出频率
    delay(5);                              //该频率维持5毫秒
  }
  //  delay(2000);                            //最高频率下维持4秒钟
  for (int i = 800; i >= 200; i--)
  {
    pinMode(4, OUTPUT);
    tone(4, i);
    delay(10);
  }
}
