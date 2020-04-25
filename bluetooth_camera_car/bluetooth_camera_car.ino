/*
  Name:    Bluetooth.ino
  Created: 2016/7/30 13:26:47
  Author:  Fing
*/
#include <SoftwareSerial.h>;
#include <Servo.h>


//使用软件串口，能讲数字口模拟成串口
SoftwareSerial BT(8, 9);  //新建对象，接收脚为8，发送脚为9

#define PIN_SERVO_LAND 10
#define PIN_SERVO_SKY 11
Servo myservo_land;
Servo myservo_sky;

int last_land = 90;
int last_sky = 100;


#define left 1
#define right  2
#define up  3
#define down  4

char val;

void setup() {
  Serial.begin(9600);   //与电脑的串口连接
  Serial.println("BT is ready!");
  BT.begin(9600);  //设置波特率

  myservo_land.attach(PIN_SERVO_LAND);
  myservo_sky.attach(PIN_SERVO_SKY);

  //init
  Serial.begin(9600);
  myservo_land.write(90);
  myservo_sky.write(90);
}

void move(int type) {
  Servo servo;
  int cur = 0;
  int depth = 10;
  switch (type) {
    case left:
      servo = myservo_land;
      cur = last_land + depth;
      if (cur >= 180) {
        cur = 180;
      }
      last_land = cur;
      break;
    case right:
      servo = myservo_land;
      cur = last_land - depth;
      if (cur <= 0) {
        cur = 0;
      }
      last_land = cur;
      break;
    case down:
      servo = myservo_sky;
      cur = last_sky + depth;
      if (cur >= 180) {
        cur = 180;
      }
      last_sky = cur;
      break;
    case up:
      servo = myservo_sky;
      cur = last_sky - depth;
      if (cur <= 0) {
        cur = 0;
      }
      last_sky = cur;
      break;

  }
  Serial.println(cur);
  servo.write(cur);
}

void loop() {
  //如果串口接收到数据，就输出到蓝牙串口
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }

  //如果接收到蓝牙模块的数据，输出到屏幕
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);

    switch (val) {
      case 'w':
        move(3);
        break;
      case 's':
        move(4);
        break;
      case 'a':
        move(1);
        break;
      case 'd':
        move(2);
        break;
    }
  }
}
