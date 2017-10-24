#include <Servo.h>

int servopin=2;
int command;

void GetCommand(void);

Servo myservo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(servopin);
  myservo.write(0);
  delay(1000);
  myservo.write(180);
  delay(1000);
  myservo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  GetCommand();
  //Serial.print("11");
  delay(500);
}


void GetCommand(void)
{
  while(Serial.read()!='A'){}
  command=Serial.parseInt();
  switch(command)
  {
    case 0:myservo.write(0);;break;
    case 1:myservo.write(90);;break;
    case 2:myservo.write(180);;break; 
  }
  Serial.println(command);
  Serial.println("working!!!");
}

