#include <Servo.h>

#define PIN_SERVO_LAND 10
#define PIN_SERVO_SKY 11
Servo myservo_land;
Servo myservo_sky;

int last_land = 90;
int last_sky = 150;

#define left 1
#define right  2
#define up  3
#define down  4

void setup()
{
  myservo_land.attach(PIN_SERVO_LAND);
  myservo_sky.attach(PIN_SERVO_SKY);

  //init
  Serial.begin(9600);
  myservo_land.write(last_land);
  myservo_sky.write(last_sky);

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

void loop()
{

  while (Serial.available()) {

    char x = char(Serial.read());
    Serial.println(x);
    switch (x) {
      case '4':
        move(1);
        break;
      case '6':
        move(2);
        break;
      case '8':
        move(3);
        break;
      case '2':
        move(4);
        break;
    }
  }
}
