#include <Servo.h>

//left-->0    right-->180   前伸


#define LEFT_0 8
#define RIGHT_0 9
#define FRONT_1 10
#define FRONT_2 11
#define FRONT_3 12

#define appraoch_command  0x00        //接近物品
#define open_command      0x10        //张开夹子
#define catch_command     0x20        //夹住物品 
#define raise_command1    0x20        //抬起前臂
#define raise_command2    0x30        //抬起后臂 

Servo myservo_left0;
Servo myservo_right0;
Servo myservo_front1;
Servo myservo_front2;
Servo myservo_front3;

int angle_left0=90;
int angle_right0=90;
int angle_front1=90;
int angle_front2=90;
int angle_front3=90;

byte comdata=0;
int command_char=0;
int command_angle=90;

void GPIO_Init();
void Angle_Init();
void Raise_front();
void Approach();
void bluetoothControl();
void Command_Crotrol();

void setup() {
  GPIO_Init();
  Angle_Init();
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()>=0)
  {
    Serial.println("Get Command");
    delay(100);
    command_char=Serial.read();
    switch(command_char)
    {
      case '@':bluetoothControl();
    }
  }
}



void GPIO_Init()
{
  myservo_left0.attach(LEFT_0);
  myservo_right0.attach(RIGHT_0);
  myservo_front1.attach(FRONT_1);
  myservo_front2.attach(FRONT_2);
  myservo_front3.attach(FRONT_3);
}

void Angle_Init()
{
  int i=2;
  myservo_left0.write(90);
  myservo_right0.write(90);
  myservo_front1.write(180);
  myservo_front2.write(90);
  myservo_front3.write(90);
  while(i--)
    delay(1000);
  }

void Raise_front(){
  int i=2;
  myservo_front1.write(180);
  while(i--)
    delay(1000);
  }

void Approach()
{
  int i=2;
  myservo_left0.write(29);
  myservo_right0.write(151);
  myservo_front1.write(52);
  myservo_front2.write(10);
  while(i--)
    delay(1000);
}

void Catch()
{
  int i=2;
  myservo_front3.write(160);
  while(i--)
    delay(1000);
}

void Raise()
{
  int i=2,j=2,k=2;

  myservo_front2.write(180);
  while(i--)
    delay(1000);

  myservo_left0.write(90);
  myservo_right0.write(90);
  while(j--)
    delay(1000);

  myservo_front3.write(90);
  while(k--)
    delay(1000);
}

void Command_Crotrol()
{
  if(Serial.available()>=0){     //判断串口缓冲器的状态函数，用以判断数据是否送达串口
    Serial.println("Get Big Command");
    delay(100);
    comdata=Serial.read();
    switch(comdata)
    {
      case appraoch_command: Approach(); Serial.println("11111111111");break;


      case raise_command1: Raise_front();Serial.println("22222222222");break;
      case raise_command2: Angle_Init();break;

    }
  }
  else
    Serial.println("nothing");
}

void bluetoothControl()
{
  while(Serial.read()!='@'){}
  delay(100);
  if(Serial.available()>=0)
  {
    Serial.println("get command");
    delay(100);
    command_char=Serial.read();
    if(command_char=='A'||'B'||'C'||'D')
    {
      command_angle=Serial.parseInt();
      switch(command_char)
      {
        case 'A':
          myservo_left0.write(command_angle);
          myservo_right0.write(180-command_angle);
          break;
        case 'B':
          myservo_front1.write(command_angle);
          break;
        case 'C':
          myservo_front2.write(command_angle);
          break;
        case 'D':
          myservo_front3.write(command_angle);
          break;
      }
      while(Serial.read()>0){}           //清空缓存区
    } 
  }
  else
    Serial.println("nothing");
}
/*void GetCommand(void)
{
  
  while(Serial.read()!='A'){}
  command=Serial.parseInt();
  switch(command)
  {
    case 0:myservo.write(0);break;
    case 1:myservo.write(90);break;
    case 2:myservo.write(180);break; 
  }
  Serial.println(command);

}
*/
