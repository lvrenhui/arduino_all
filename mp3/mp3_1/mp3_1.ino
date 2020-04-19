#include "SoftwareSerial.h"//引用软串口库文件
SoftwareSerial mySerial(10, 11);//定义引脚，D10为RX,D11为TX
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //定义指令的相关参数

# define ACTIVATED LOW

int buttonNext = 2;//定义按键下一曲为D2
int buttonPause = 3;//定义按键播放/暂停为D3
int buttonPrevious = 4;//定义按键上一曲为D4
boolean isPlaying = false;//布尔型isPlaying为假。

void setup () {

  pinMode(buttonPause, INPUT);
  digitalWrite(buttonPause, HIGH);
  pinMode(buttonNext, INPUT);
  digitalWrite(buttonNext, HIGH);
  pinMode(buttonPrevious, INPUT);
  digitalWrite(buttonPrevious, HIGH); //定义引脚通信，默认拉高。

  mySerial.begin (9600);//软串口初始化，波特率9600.
  delay(1000);//延时1秒
  playFirst();//开始播放第一首歌曲
  isPlaying = true;//isPlaying为真

}

void loop () {

  if (digitalRead(buttonPause) == ACTIVATED)//判断暂停键如果为低电平
  {
    if (isPlaying) //判断isPlaying状态
    {
      pause();//暂停播放
      isPlaying = false;//isPlaying为假
    } else
    {
      isPlaying = true;//反之isPlaying为真
      play();//开始播放
    }
  }

  if (digitalRead(buttonNext) == ACTIVATED)//判断下一曲键为低电平
  {
    if (isPlaying) //判断isPlaying状态
    {
      playNext();//播放下一曲，此处不管isPlaying是什么状态，均播放下一曲。
    }
  }

  if (digitalRead(buttonPrevious) == ACTIVATED)//判断上一曲键为低电平
  {
    if (isPlaying) //判断isPlaying状态
    {
      playPrevious();//播放上一曲，此处不管isPlaying是什么状态，均播放上一曲。
    }
  }
}

void playFirst()
{
  execute_CMD(0x3F, 0, 0);//发送初始化参数指令
  delay(500);//延时500ms
  setVolume(20);//设置音量为20
  delay(500);//延时500ms
  execute_CMD(0x11, 0, 1); //全部循环播放指令触发。
  delay(500);//延时500ms
}

void pause()
{
  execute_CMD(0x0E, 0, 0); //暂停指令触发。
  delay(500);//延时500ms
}

void play()
{
  execute_CMD(0x0D, 0, 1); //播放指令触发。
  delay(500);
}

void playNext()
{
  execute_CMD(0x01, 0, 1); //下一曲指令触发
  delay(500);//延时500ms
}

void playPrevious()
{
  execute_CMD(0x02, 0, 1); //上一曲指令触发
  delay(500);//延时500ms
}

void setVolume(int volume)
{
  execute_CMD(0x06, 127, volume); // 音量指令，这里设置了127响一点~~
  delay(2000);//延时2秒
}

void execute_CMD(byte CMD, byte Par1, byte Par2)
// 执行的命令和参数
{
  // Calculate the checksum (2 bytes)
  word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
  // Build the command line
  byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
                            Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte
                          };
  //Send the command line to the module
  for (byte k = 0; k < 10; k++)
  {
    mySerial.write( Command_line[k]);//软串口输入命令行
  }
}
