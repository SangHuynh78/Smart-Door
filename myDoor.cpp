#include "myDoor.h"
Servo myServo;

void InitDoor(void)
{
  myServo.attach(5);
  delay(10);
  myServo.write(0); 
  delay(10);
}

void OpenOrCloseDoor(char StateDoor)
{
  switch(StateDoor)
  {
    case 'O':
      myServo.write(180);
      delay(7000);
      break;
    case 'C':
      myServo.write(0);
      break;
    case 'S':
      myServo.write(180);
      while (Serial.read() != 'C'); ///// take lowpower for Arduino
      break;
  }
}

void CheckDoor(char State1, char State2, char State3)
{
  if (State1 == 'S' || State2 == 'S' || State3 == 'S') 
  {
    myServo.write(180);
    while (Serial.read() != 'C'); ///// take lowpower for Arduino
  }
  else if (State1 == 'O' || State2 == 'O' || State3 == 'O')
  {
    myServo.write(180);
    delay(7000);
  }
  else myServo.write(0);   
}