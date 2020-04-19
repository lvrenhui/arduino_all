#include <IRremote.h>  // 使用IRRemote函数库
#include "timer.h"
///////////////选择///////////////
//-------------------------------------------------------------------//
//*******************************************************************//
///////////////////////////////////////////////////////////////////////
//////////////////////////////红外遥控/////////////////////////////////
///////////////////////////////////////////////////////////////////////

const int irReceiverPin = 2;  // 红外接收器的 OUTPUT 引脚接在 PIN2 接口 定义irReceiverPin变量为PIN2接口
IRrecv irrecv(irReceiverPin); // 设置irReceiverPin定义的端口为红外信号接收端口
decode_results results;    // 定义results变量为红外结果存放位置

Timer timer;
//-------------------------------------------------------------------------//

void setup()
{
  Serial.begin(9600); //9600（PC端使用）

  timer.setInterval(5000);

  // The function to be called
  timer.setCallback(helloCallback);


  irrecv.enableIRIn();   // 启动红外解码


}

void helloCallback() {

  digitalWrite(LED_BUILTIN, LOW);
}
void loop()
{
  timer.update();
  scan();

}


void scan(void)
{
  if (irrecv.decode(&results)) {   // 解码成功，把数据放入results变量中
    // 把数据输入到串口
    Serial.print("irCode: ");
    Serial.print(results.value, DEC); // 显示红外编码
    Serial.print(",  HEX: "); // 显示红外编码
    Serial.print(results.value, HEX); // 显示红外编码
    Serial.print(",  bits: ");
    Serial.println(results.bits); // 显示红外编码位数

    if ((results.value == 3238126971) || (results.value == 16738455)) {
      digitalWrite(LED_BUILTIN, HIGH);
      timer.start();

    }
    if ((results.value == 2534850111) || (results.value == 16724175)) {
      digitalWrite(LED_BUILTIN, LOW);
    }

    irrecv.resume();    // 继续等待接收下一组信号
  } if (results.value == 0x16)
    digitalWrite(9, HIGH);
  delay(600); //延时600毫秒，做一个简单的消抖
}
