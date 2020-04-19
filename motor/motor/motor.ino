int input1 = 5; // 定义uno的pin 5 向 input1 输出 
int input2 = 6; // 定义uno的pin 6 向 input2 输出
int enA = 10; // 定义uno的pin 10 向 输出A使能端输出

void setup() {   
   pinMode(input1,OUTPUT);
   pinMode(input2,OUTPUT);
   pinMode(enA,OUTPUT);
}

void loop() {
   digitalWrite(input1,HIGH); //给高电平
   digitalWrite(input2,LOW);  //给低电平
   analogWrite(enA,100);
 }
