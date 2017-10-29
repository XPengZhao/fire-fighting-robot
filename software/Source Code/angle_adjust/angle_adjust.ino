#include <Servo.h>

//left-->0    right-->180   前伸
//#A-->接近物体   #B-->夹紧夹子    #C-->抬起手臂
//@ABCD+角度 分别控制5个舵机
#define LEFT_WHEEL 6
#define RIGHT_WHEEL 7

#define LEFT_0 8
#define RIGHT_0 9
#define FRONT_1 10
#define FRONT_2 11
#define FRONT_3 12


Servo myservo_left0;
Servo myservo_right0;
Servo myservo_front1;
Servo myservo_front2;
Servo myservo_front3;

Servo myservo_leftwheel;
Servo myservo_rightwheel;

int angle_left0=90;
int angle_right0=90;
int angle_front1=90;
int angle_front2=90;
int angle_front3=90;
int command_char=0;
int command_angle=90;

void GPIO_Init();
void Angle_Init();
void Raise_front();
void Approach();
void bluetoothControl();
void Command_Crotrol();
void Go_straight();
void Stop();
void Go_back();
void Turn_Left();
void Turn_Right();
void Adjust_Left();
void Adjust_right();


void setup() 
{
  GPIO_Init();
  Angle_Init();
  Serial.begin(9600);
}

void loop() 
{
  if(Serial.available()>0)
  {
    Serial.println("Get Command");
    delay(100);
    command_char=Serial.read();
    switch(command_char)
    {
      case '@':
        bluetoothControl();
        break;
      case '#':
        Command_Crotrol();
        break;
    }
    while(Serial.read()>=0){}           //清空缓存区
    command_char=0;
  }
}



void GPIO_Init()
{
  myservo_left0.attach(LEFT_0);
  myservo_right0.attach(RIGHT_0);
  myservo_front1.attach(FRONT_1);
  myservo_front2.attach(FRONT_2);
  myservo_front3.attach(FRONT_3);
  myservo_leftwheel.attach(LEFT_WHEEL);
  myservo_rightwheel.attach(RIGHT_WHEEL);
}

void Angle_Init()
{
  int i=2;
  myservo_left0.write(90);
  myservo_right0.write(90);
  myservo_front1.write(180);
  myservo_front2.write(90);
  myservo_front3.write(90);
  myservo_leftwheel.write(180);
  myservo_rightwheel.write(0);
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

  myservo_front1.write(180);
  while(i--)
    delay(1000);

  myservo_left0.write(90);
  myservo_right0.write(90);
  while(j--)
    delay(1000);

  myservo_front2.write(90);
  while(k--)
    delay(1000);
}

void Command_Crotrol()
{
  Serial.println("Command_Crotrol");
  command_char=Serial.read();
    switch(command_char)
    {
      case 'A': 
        Approach();
        break;
      case 'B': 
        Catch();
        break;
      case 'C':
        Raise();
        break;
      default:
        Serial.println("nothing");
    }
}

void bluetoothControl()
{
    Serial.println("bluetoothControl");
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
    } 
  else
    Serial.println("nothing");
}

void Go_straight()
{;}
void Stop()
{;}
void Go_back()
{;}
void Turn_Left()
{;}
void Turn_Right()
{;}
void Adjust_Left()
{;}
void Adjust_right()
{;}
