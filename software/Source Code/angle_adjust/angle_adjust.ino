#include <Servo.h>

/*
  left-->0    right-->180   前伸
  #A-->接近物体   #B-->夹紧夹子    #C-->抬起手臂
  @ABCD+角度 分别控制5个舵机
*/

//引脚定义
#define LEFT_WHEEL 6
#define RIGHT_WHEEL 7
#define LEFT_0 8
#define RIGHT_0 9
#define FRONT_1 10
#define FRONT_2 11
#define FRONT_3 12

//初始化角度舵机定义
#define LEFT0_INIT 145
#define RIGHT0_INIT 32
#define FRONT1_INIT 0
#define FRONT2_INIT 180
#define FRONT3_INIT 60

//准备抓取时角度舵机定义
#define LEFT0_APPRAOCH 29
#define RIGHT0_APPROACH 151
#define FRONT1_APPROACH 52
#define FRONT2_APPROACH 120
#define FRONT3_APPROACH 60

//抓住瞬间角度舵机的定义
#define FRONT3_CATCH 150

//抓住后举起手臂角度舵机定义
#define LEFT0_RAISE 145
#define RIGHT0_RAISE 32
#define FRONT1_RAISE 0
#define FRONT2_RAISE 180
#define FRONT3_RAISE 150

//每次给角度舵机指令后延时
#define DELAY_TIME 500

Servo myservo_leftwheel;
Servo myservo_rightwheel;
Servo myservo_left0;
Servo myservo_right0;
Servo myservo_front1;
Servo myservo_front2;
Servo myservo_front3;


int angle_left0 = 90;
int angle_right0 = 90;
int angle_front1 = 90;
int angle_front2 = 90;
int angle_front3 = 90;
int command_char = 0;
int command_angle = 90;

void GPIO_Init();
void Angle_Init();
void Raise_front();
void Approach();
void Move_Crotrol();
void bluetoothControl();
void Command_Crotrol();
void Go_straight();
void Stop();
void Go_back();
void Turn_Left();
void Turn_Right();
void Adjust_Left();
void Adjust_Right();


void setup()
{
  GPIO_Init();
  Angle_Init();
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0)
  {
    Serial.println("Get Command");
    delay(100);
    command_char = Serial.read();
    switch (command_char)
    {
      case '@':
        bluetoothControl();
        break;
      case '#':
        Command_Crotrol();
        break;
      case '!':
        Move_Crotrol();
    }
    while (Serial.read() >= 0) {}       //清空缓存区
    command_char = 0;
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
  myservo_left0.write(LEFT0_INIT);
  myservo_right0.write(RIGHT0_INIT);
  myservo_front1.write(FRONT1_INIT);
  myservo_front2.write(FRONT2_INIT);
  myservo_front3.write(FRONT3_INIT);
  myservo_leftwheel.writeMicroseconds(1500);
  myservo_rightwheel.writeMicroseconds(1500);
  delay(DELAY_TIME);
}

void Approach()
{
  myservo_front2.write(FRONT2_APPROACH);
  delay(DELAY_TIME);
  myservo_front1.write(FRONT1_APPROACH);
  delay(DELAY_TIME);
  myservo_left0.write(LEFT0_APPRAOCH);
  myservo_right0.write(RIGHT0_APPROACH);
  delay(DELAY_TIME);
  myservo_front3.write(FRONT3_APPROACH);
}

void Catch()
{
  myservo_front3.write(FRONT3_CATCH);
  delay(DELAY_TIME);
}

void Raise()
{
  myservo_left0.write(LEFT0_RAISE);
  myservo_right0.write(RIGHT0_RAISE);
  delay(DELAY_TIME);

  myservo_front1.write(FRONT1_RAISE);
  delay(DELAY_TIME);

  myservo_front2.write(FRONT2_RAISE);
  delay(DELAY_TIME);
}

void Move_Crotrol()
{
  Serial.println("Move_Crotrol");
  command_char = Serial.read();
  switch (command_char)
  {
    case 'W':
      Go_straight();
      break;
    case 'S':
      Stop();
      break;
    case 'A':
      Adjust_Left();
      break;
    case 'D':
      Adjust_Right();
      break;
    case 'Q':
      Turn_Left();
      break;
    case 'E':
      Turn_Right();
      break;
    case 'X':
      Go_back();
      break;
    default:
      Serial.println("nothing");
  }
}

void Command_Crotrol()
{
  Serial.println("Command_Crotrol");
  command_char = Serial.read();
  switch (command_char)
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
  command_char = Serial.read();
  if (command_char == 'A' || 'B' || 'C' || 'D')
  {
    command_angle = Serial.parseInt();
    switch (command_char)
    {
      case 'A':
        myservo_left0.write(command_angle);
        myservo_right0.write(180 - command_angle);
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
      case 'L':
        myservo_leftwheel.writeMicroseconds(command_angle);
        break;
      case 'R':
        myservo_rightwheel.writeMicroseconds(command_angle);
        break;
    }
  }
  else
    Serial.println("nothing");
}

void Go_straight()
{
  myservo_leftwheel.writeMicroseconds(2000);
  myservo_rightwheel.writeMicroseconds(1000);
}
void Stop()
{
  myservo_leftwheel.writeMicroseconds(1500);
  myservo_rightwheel.writeMicroseconds(1500);
}
void Go_back()
{
  myservo_leftwheel.writeMicroseconds(1000);
  myservo_rightwheel.writeMicroseconds(2000);
  delay(500);
  myservo_leftwheel.writeMicroseconds(1500);
  myservo_rightwheel.writeMicroseconds(1500);
}
void Turn_Left()
{
  myservo_leftwheel.writeMicroseconds(1550);
  myservo_rightwheel.writeMicroseconds(1300);
}
void Turn_Right()
{
  myservo_leftwheel.writeMicroseconds(1700);
  myservo_rightwheel.writeMicroseconds(1450);
}
void Adjust_Left()
{
  myservo_leftwheel.writeMicroseconds(1500);
  myservo_rightwheel.writeMicroseconds(1300);
  delay(400);
  myservo_leftwheel.writeMicroseconds(1500);
  myservo_rightwheel.writeMicroseconds(1500);
}
void Adjust_Right()
{
  myservo_leftwheel.writeMicroseconds(1700);
  myservo_rightwheel.writeMicroseconds(1500);
  delay(400);
  myservo_leftwheel.writeMicroseconds(1500);
  myservo_rightwheel.writeMicroseconds(1500);
}
