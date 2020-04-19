/*This is my Arduino project on making diffent Siren Sound with their LED scnc/transitions. You can get the this code from my Github
   repository named "Siren", You can watch its working on my Youtube Channel and the complete tutorial is explained in my Aruino Create account
   named coding_killer. Now it's your turn to make some cool tone using my Project and explore all the possibilities.
*/
#include <IRremote.h>  // 使用IRRemote函数库
#include <NewTone.h>

boolean lastbutton = LOW;
boolean currentbutton = LOW;
int input = 0;
int buzz = 4; // Buzzer Pin
int irReceiverPin = 2;
IRrecv irrecv(irReceiverPin); // 设置irReceiverPin定义的端口为红外信号接收端口
decode_results results;    // 定义results变量为红外结果存放位置
int j = 8;
int k = 13;
int ledmode = 0;
void setup() {
  for (int i = 8; i <= 13; i++)
    pinMode(i, OUTPUT);
  //  pinMode(2, INPUT);

  Serial.begin(9600); //9600（PC端使用）
  irrecv.enableIRIn();   // 启动红外解码
}
boolean debounce(boolean last) {                //Function to solve the problem of button debouncing
  boolean current = digitalRead(2);
  if (last != current)
  {
    delay(5);
    current = digitalRead(2);
  }
  return current;
}
void loop() {
  for (int i = 8; i <= 13; i++)
    digitalWrite(i, LOW);

  //  currentbutton = debounce(lastbutton);
  //  if (lastbutton == LOW && currentbutton == HIGH)
  //  {
  //    input++;
  //  }
  //  lastbutton = currentbutton;
  //  settone(input);
  //  settone(ledmode);
  rev();
}

void settone(int input)
{

  if (input == 1)
    one();
  else if (input == 2)
    oneA();
  else if (input == 3)
    two();
  else if (input == 4)
    twoA();
  else if (input == 5)
    three();
  else if (input == 6)
    threeA();
  else if (input == 7)
    four();
}

void one() {         //This function produces the 1st siren sound with ON/OFF led transition.
  // Whoop up
  for (int hz = 440; hz < 1000; hz += 25) {
    NewTone(buzz, hz, 50);
    delay(5);
    for (int i = 8; i <= 10; i++)
      digitalWrite(i, HIGH);
  }
  // Whoop down
  for (int hz = 1000; hz > 440; hz -= 25) {
    NewTone(buzz, hz, 50);
    delay(5);
    for (int i = 8; i <= 10; i++)
    {
      digitalWrite(i, LOW);
      digitalWrite(i + 3, HIGH);
    }
  }
}

void oneA() {                //This function produces differnt transition on 1st siren.

  // Whoop up
  for (int hz = 440; hz < 1000; hz += 25) {
    NewTone(buzz, hz, 50);
    delay(5);
  }
  if (j >= 8) {
    digitalWrite(j, HIGH);
    j = j + 1;
    digitalWrite(k, HIGH);
    k = k - 1;
    if (j == 11)
      j = 8;
    if (k == 10)
      k = 13;
  }
  // Whoop down
  for (int hz = 1000; hz > 440; hz -= 25) {
    NewTone(buzz, hz, 50);
    delay(5);
  }
}
void two() {                   //This function produces the 2nd siren sound with progressive led transition.
  // Whoop up
  for (int hz = 440; hz < 1000; hz += 25) {
    NewTone(buzz, hz, 50);
    delay(5);
  }
  loopF(8, 13, 20);
  loopR(13, 8, 20);
  // Whoop down
  for (int hz = 1000; hz > 440; hz -= 25) {
    NewTone(buzz, hz, 50);
    delay(5);
  }
}
void twoA() {                  //This function produces differnt transition on 2nd siren.
  // Whoop up
  for (int hz = 440; hz < 1000; hz += 25) {
    NewTone(buzz, hz, 50);
    delay(5);
  }
  loopF(8, k, 20);
  loopR(13, j, 20);
  k--;
  if (k == 3)
    k = 12;
  j++;
  if (j == 12)
    j = 3;
  // Whoop down
  for (int hz = 1000; hz > 440; hz -= 25) {
    NewTone(buzz, hz, 50);
    delay(5);
  }
}
void three() {              //This function produces the 3rd siren(AMBULANCE) sound with led transition.
  NewTone(buzz, 440, 200);
  delay(300);
  for (int i = 8; i <= 9; i++)
    digitalWrite(i, HIGH);
  noNewTone(buzz);
  NewTone(buzz, 494, 500);
  delay(300);
  for (int i = 8; i <= 9; i++) {
    digitalWrite(i, LOW);
    digitalWrite(i + 4, HIGH);
  }
  noNewTone(buzz);
  NewTone(buzz, 523, 300);
  delay(200);
  digitalWrite(10, HIGH);
  delay(50);
  digitalWrite(11, HIGH);
  delay(50);
  noNewTone(buzz);
}
void threeA() {              //This function produces differnt transition on 3rd siren.
  NewTone(buzz, 440, 200);
  delay(100);
  loopF(5, 10, 20);
  loopR(10, 5, 20);
  noNewTone(buzz);
  for (int i = 3; i <= 4; i++) {
    digitalWrite(i, HIGH);
    digitalWrite(i + 8, HIGH);
  }
  NewTone(buzz, 494, 500);
  delay(300);
  noNewTone(buzz);
  for (int i = 3; i <= 4; i++) {
    digitalWrite(i, LOW);
    digitalWrite(i + 8, LOW);
  }
  NewTone(buzz, 523, 300);
  delay(300);
  noNewTone(buzz);
}
void four() {                             //This function produces the 4th siren(POLICE) sound with led transition.
  for (int i = 8; i <= 12; i += 2)
    digitalWrite(i, HIGH);
  for (int hz = 440; hz < 1000; hz++) {
    NewTone(buzz, hz, 50);
    delay(5);
  }
  for (int i = 8; i <= 12; i += 2)
    digitalWrite(i, LOW);
  for (int i = 9; i <= 13; i += 2)
    digitalWrite(i, HIGH);
  for (int hz = 1000; hz > 440; hz--) {
    NewTone(buzz, hz, 50);
    delay(5);
  }
}
// SOME EXTRA FUNCTIONS OTHER THAN THE SIREN TONES
void loopF(int spin, int epin, int dela) { //loopF can blink the led in forward direction so spin must be lower than epin.
  for (int i = spin; i <= epin; i++) {
    digitalWrite(i, HIGH);
    delay(dela);
    low();
    if (spin == epin) {
      spin = 3;
      epin = 12;
    }
  }
}
void loopR(int epin, int spin, int dela) {   //loopR can blink the led in reverse/backward direction so epin must be lower than spin.
  for (int i = epin; i >= spin; i--) {
    digitalWrite(i, HIGH);
    delay(dela);
    low();
    if (spin == epin) {
      spin = 3;
      epin = 12;
    }
  }
}
void low() {                                 //Used by loopF and loopR
  for (int i = 3; i <= 12; i++)
    digitalWrite(i, LOW);
}

void scan(void)
{
  if (irrecv.decode(&results)) {   // 解码成功，把数据放入results变量中
    // 把数据输入到串口
    Serial.print("irCode: ");
    Serial.print(results.value, DEC); // 显示红外编码
    Serial.print(",  bits: ");
    Serial.println(results.bits); // 显示红外编码位数
    irrecv.resume();    // 继续等待接收下一组信号
  } if (results.value == 0x16)
    digitalWrite(9, HIGH);
  delay(600); //延时600毫秒，做一个简单的消抖
}

void rev(void)
{
  if   (irrecv.decode(&results)) {   // 解码成功，把数据放入results.value变量中
    if   ((results.value == 16718055) || (results.value == 1033561079))
    {
      ledmode = 1;
    }
    else if ((results.value == 465573243) || (results.value == 16730805) || (results.value == 304335233) || (results.value == 891929274) || (results.value == 93040025))
    {
      ledmode = 7;
    }
    else if ((results.value == 2351064443) || (results.value == 16716015) || (results.value == 3640844469) || (results.value == 3606423579))
    {
      ledmode = 3;
    }
    else if ((results.value == 16734885) || (results.value == 71952287))
    {
      ledmode = 4;
    } else if ((results.value == 1217346747) || (results.value == 16726215)) {
      ledmode = 0;
    }

    //    // 把数据输入到串口
    //    Serial.print("irCode: ");
    //    Serial.print(results.value, DEC); // 显示红外编码
    //    Serial.print(",  bits: ");
    //    Serial.println(results.bits); // 显示红外编码位数

    irrecv.resume();    // 继续等待接收下一组信号
  } if (results.value == 0x16)
    delay(200); //延时600毫秒，做一个简单的消抖

  settone(ledmode);
}
