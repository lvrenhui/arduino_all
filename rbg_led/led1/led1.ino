int r = 9;
int b = 10;
int g = 11;


void setup() {
  // put your setup code here, to run once:

  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
}

void loop() {
  for (int i = 200; i > 0; i--) //渐亮
  {
    analogWrite(r, i);    //慢慢开启红色和绿色会搭配出黄色
    analogWrite(g, i);
    analogWrite(b, 255);
    delay(10);
  }

  for (int i = 0; i < 200; i++) //渐灭
  {
    analogWrite(r, 255);   //慢慢关闭绿色和蓝色会搭配出较鲜艳的蓝色
    analogWrite(g, i);
    analogWrite(b, i);
    delay(10);
  }
}
