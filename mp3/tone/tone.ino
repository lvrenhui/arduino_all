void setup()
{
}

void loop()
{
  for (int i = 200; i <= 800; i++)             //用循环的方式将频率从200HZ 增加到800HZ
  {
    pinMode(4, OUTPUT);
    tone(4, i);                           //在四号端口输出频率
    delay(5);                              //该频率维持5毫秒
  }
  delay(2000);                            //最高频率下维持4秒钟
  for (int i = 800; i >= 200; i--)
  {
    pinMode(4, OUTPUT);
    tone(4, i);
    delay(10);
  }
}
