/*
  Name:    Bluetooth.ino
  Created: 2016/7/30 13:26:47
  Author:  Fing
*/
#include <SoftwareSerial.h>;
#include <Servo.h>


//使用软件串口，能讲数字口模拟成串口
SoftwareSerial BT(2, 3);  //新建对象，接收脚为2，发送脚为3
#define PIN_SERVO_LAND 9
#define PIN_SERVO_SKY 10

#define leftA_PIN 5
#define leftB_PIN 6
#define rightA_PIN 11
#define rightB_PIN 12


Servo myservo_land;
Servo myservo_sky;

int last_land = 100;
int last_sky = 150;


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
  myservo_land.write(last_land);
  myservo_sky.write(last_sky);

  motor_pinint();  //电机引脚初始化
}

void move(int type) {
  Servo servo;
  int cur = 0;
  int depth = 5;
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
      //挡住了，不能再转了
      if (cur <= 80) {
        cur = 80;
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
      case 'I':
        move(left);
        break;
      case 'J':
        move(right);
        break;
      case 'K':
        move(up);
        break;
      case 'L':
        move(down);
        break;
      case 'C':
        forward();
        break;
      case 'D':
        back();
        break;
      case 'A':
        turnLeftOrigin();
        break;
      case 'B':
        turnRightOrigin();
        break;
      case 'E':
        turnLeftForward();
        break;
      case 'F':
        turnLeftBack();
        break;
      case 'G':
        turnRightForward();
        break;
      case 'H':
        turnRightBack();
        break;
      case 'S':
        _stop();
        break;
    }
  }
}


/*电机引脚初始化*/
void motor_pinint( )
{
  pinMode (leftA_PIN, OUTPUT); //设置引脚为输出引脚
  pinMode (leftB_PIN, OUTPUT); //设置引脚为输出引脚
  pinMode (rightA_PIN, OUTPUT); //设置引脚为输出引脚
  pinMode (rightB_PIN, OUTPUT); //设置引脚为输出引脚
}
/**************************************************
  forward子函数——前进子函数
  函数功能：控制车前进
**************************************************/
void forward( )
{
  analogWrite(leftA_PIN, 180);
  analogWrite(leftB_PIN, 0);        //左轮前进
  analogWrite(rightA_PIN, 180);
  analogWrite(rightB_PIN, 0);        //右轮前进
}
/**************************************************
  back子函数——后退子函数
  函数功能：控制车后退
**************************************************/
void back( )
{
  analogWrite(leftA_PIN, 0);
  analogWrite(leftB_PIN, 180);       //左轮后退
  analogWrite(rightA_PIN, 0);
  analogWrite(rightB_PIN, 180);       //右轮后退
}
/**************************************************
  turnLeftOrigin子函数——原地左转子函数
  函数功能：控制车原地左转
**************************************************/
void turnLeftOrigin( )
{
  analogWrite(leftA_PIN, 0);
  analogWrite(leftB_PIN, 120);       //左轮后退
  analogWrite(rightA_PIN, 120);
  analogWrite(rightB_PIN, 0);         //右轮前进
}
/**************************************************
  turnRightOrigin子函数——原地右转子函数
  函数功能：控制车原地右转
**************************************************/
void turnRightOrigin( )
{
  analogWrite(leftA_PIN, 120);
  analogWrite(leftB_PIN, 0);       //左轮前进
  analogWrite(rightA_PIN, 0);
  analogWrite(rightB_PIN, 120);     //右轮后退
}
/**************************************************
  turnRightforword子函数——右前运动子函数
  函数功能：控制车右前
**************************************************/
void turnRightForward( )
{
  analogWrite(leftA_PIN, 200);
  analogWrite(leftB_PIN, 0);       //左轮快前进
  analogWrite(rightA_PIN, 120);
  analogWrite(rightB_PIN, 0);       //右轮慢前进
}
/**************************************************
  turnLeftforword子函数——左前运动子函数
  函数功能：控制车左前
**************************************************/
void turnLeftForward( )
{
  analogWrite(leftA_PIN, 120);
  analogWrite(leftB_PIN, 0);      //左轮慢前进
  analogWrite(rightA_PIN, 200);
  analogWrite(rightB_PIN, 0);      //右轮快前进
}
/**************************************************
  turnRightforword子函数——右后运动子函数
  函数功能：控制车右后
**************************************************/
void turnRightBack( )
{
  analogWrite(leftA_PIN, 0);
  analogWrite(leftB_PIN, 200);       //左轮快后退
  analogWrite(rightA_PIN, 0);
  analogWrite(rightB_PIN, 120);       //右轮慢后退
}
/**************************************************
  turnLeftforword子函数——左后运动子函数
  函数功能：控制车左后
**************************************************/
void turnLeftBack( )
{
  analogWrite(leftA_PIN, 0);
  analogWrite(leftB_PIN, 120);       //左轮慢后退
  analogWrite(rightA_PIN, 0);
  analogWrite(rightB_PIN, 200);       //右轮快后退
}
/**************************************************
  stop子函数—停止子函数
  函数功能：控制车停止
**************************************************/
void _stop()
{
  analogWrite(leftA_PIN, 0);
  analogWrite(leftB_PIN, 0);        //左轮静止不动
  analogWrite(rightA_PIN, 0);
  analogWrite(rightB_PIN, 0);        //右轮静止不动
}
