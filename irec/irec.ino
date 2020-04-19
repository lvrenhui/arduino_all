#include <IRremote.h>  // 使用IRRemote函数库
///////////////选择///////////////
#define choose 1    //1为通过串口打印码值模式  
//2为主函数运行模式



//-------------------------------------------------------------------//
//*******************************************************************//
///////////////////////////////////////////////////////////////////////
//////////////////////////////电机设置/////////////////////////////////
///////////////////////////////////////////////////////////////////////

#define leftA_PIN 5
#define leftB_PIN 6
#define righA_PIN 9
#define righB_PIN 10
void motor_pinint( );     //引脚初始化
void forward( );          //前进
void back( );             //后退
void turnLeftOrigin( );   //原地左
void turnRightOrigin( );  //原地右
void turnRightforword( ); //右前
void turnLeftforword( );  //左前
void turnLeftback( );     //左后
void turnRightback( );    //右后
void _stop();             //停车

//-------------------------------------------------------------------//
//*******************************************************************//
///////////////////////////////////////////////////////////////////////
//////////////////////////////红外遥控/////////////////////////////////
///////////////////////////////////////////////////////////////////////

const int irReceiverPin = 2;  // 红外接收器的 OUTPUT 引脚接在 PIN2 接口 定义irReceiverPin变量为PIN2接口
IRrecv irrecv(irReceiverPin); // 设置irReceiverPin定义的端口为红外信号接收端口
decode_results results;    // 定义results变量为红外结果存放位置
void rev(void);
void scan(void);

//-------------------------------------------------------------------------//

void setup()
{
  Serial.begin(9600); //9600（PC端使用）
  motor_pinint();        //电机引脚初始化
  irrecv.enableIRIn();   // 启动红外解码

}
void loop()
{


  if (choose == 1) scan();
  else if (choose == 2) rev();
}

/*电机引脚初始化*/
void motor_pinint( )
{
  pinMode (leftA_PIN, OUTPUT); //设置引脚为输出引脚
  pinMode (leftB_PIN, OUTPUT); //设置引脚为输出引脚
  pinMode (righA_PIN, OUTPUT); //设置引脚为输出引脚
  pinMode (righB_PIN, OUTPUT); //设置引脚为输出引脚
}
/**************************************************
  forward子函数——前进子函数
  函数功能：控制车前进
**************************************************/
void forward( )
{
  analogWrite(leftA_PIN, 180);
  analogWrite(leftB_PIN, 0);        //左轮前进
  analogWrite(righA_PIN, 180);
  analogWrite(righB_PIN, 0);        //右轮前进
}
/**************************************************
  back子函数——后退子函数
  函数功能：控制车后退
**************************************************/
void back( )
{
  analogWrite(leftA_PIN, 0);
  analogWrite(leftB_PIN, 180);       //左轮后退
  analogWrite(righA_PIN, 0);
  analogWrite(righB_PIN, 180);       //右轮后退
}
/**************************************************
  turnLeftOrigin子函数——原地左转子函数
  函数功能：控制车原地左转
**************************************************/
void turnLeftOrigin( )
{
  analogWrite(leftA_PIN, 0);
  analogWrite(leftB_PIN, 120);       //左轮后退
  analogWrite(righA_PIN, 120);
  analogWrite(righB_PIN, 0);         //右轮前进
}
/**************************************************
  turnRightOrigin子函数——原地右转子函数
  函数功能：控制车原地右转
**************************************************/
void turnRightOrigin( )
{
  analogWrite(leftA_PIN, 120);
  analogWrite(leftB_PIN, 0);       //左轮前进
  analogWrite(righA_PIN, 0);
  analogWrite(righB_PIN, 120);     //右轮后退
}
/**************************************************
  turnRightforword子函数——右前运动子函数
  函数功能：控制车右前
**************************************************/
void turnRightforword( )
{
  analogWrite(leftA_PIN, 200);
  analogWrite(leftB_PIN, 0);       //左轮快前进
  analogWrite(righA_PIN, 120);
  analogWrite(righB_PIN, 0);       //右轮慢前进
}
/**************************************************
  turnLeftforword子函数——左前运动子函数
  函数功能：控制车左前
**************************************************/
void turnLeftforword( )
{
  analogWrite(leftA_PIN, 120);
  analogWrite(leftB_PIN, 0);      //左轮慢前进
  analogWrite(righA_PIN, 200);
  analogWrite(righB_PIN, 0);      //右轮快前进
}
/**************************************************
  turnRightforword子函数——右后运动子函数
  函数功能：控制车右后
**************************************************/
void turnRightback( )
{
  analogWrite(leftA_PIN, 0);
  analogWrite(leftB_PIN, 200);       //左轮快后退
  analogWrite(righA_PIN, 0);
  analogWrite(righB_PIN, 120);       //右轮慢后退
}
/**************************************************
  turnLeftforword子函数——左后运动子函数
  函数功能：控制车左后
**************************************************/
void turnLeftback( )
{
  analogWrite(leftA_PIN, 0);
  analogWrite(leftB_PIN, 120);       //左轮慢后退
  analogWrite(righA_PIN, 0);
  analogWrite(righB_PIN, 200);       //右轮快后退
}
/**************************************************
  stop子函数—停止子函数
  函数功能：控制车停止
**************************************************/
void _stop()
{
  analogWrite(leftA_PIN, 0);
  analogWrite(leftB_PIN, 0);        //左轮静止不动
  analogWrite(righA_PIN, 0);
  analogWrite(righB_PIN, 0);        //右轮静止不动
}

void rev(void)
{
  if   (irrecv.decode(&results)) {   // 解码成功，把数据放入results.value变量中
    if   ((results.value == 16718055) || (results.value == 1033561079))
    {
      forward( )         ;  //2前进
      delay(500);
      _stop();
    }
    else if ((results.value == 465573243) || (results.value == 16730805) || (results.value == 304335233) || (results.value == 891929274) || (results.value == 93040025))
    {
      back( )            ;  //8后退
      delay(500);
      _stop();
    }
    else if ((results.value == 16724175) || (results.value == 814588342) || (results.value == 2534850111) || (results.value == 16724175))
    {
      turnLeftforword( ) ;  //1左前
      delay(500);
      _stop();
    }
    else if ((results.value == 16743045) || (results.value == 1635910171) || (results.value == 16743045))
    {
      turnRightforword( );  //3右前
      delay(500);
      _stop();
    }
    else if ((results.value == 1209942246) || (results.value == 851901943) || (results.value == 16728765))
    {
      turnLeftback( )    ;  //7左后
      delay(500);
      _stop();
    }
    else if ((results.value == 16732845) || (results.value == 1623741183))
    {
      turnRightback( )   ;  //9右后
      delay(500);
      _stop();
    }
    else if ((results.value == 2351064443) || (results.value == 16716015) || (results.value == 3640844469) || (results.value == 3606423579))
    {
      turnLeftOrigin( )   ;  //4原地左转
      delay(250);
      _stop();
    }
    else if ((results.value == 16734885) || (results.value == 71952287))
    {
      turnRightOrigin( )   ;  //6原地右转
      delay(250);
      _stop();
    }
    irrecv.resume();    // 继续等待接收下一组信号
  } if (results.value == 0x16)
    delay(600); //延时600毫秒，做一个简单的消抖
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
    irrecv.resume();    // 继续等待接收下一组信号
  } if (results.value == 0x16)
    digitalWrite(9, HIGH);
  delay(600); //延时600毫秒，做一个简单的消抖
}
