#ifndef myDoor_h
#define myDoor.h
#include <Arduino.h>
#include <Servo.h>

void InitDoor(void);
void OpenOrCloseDoor(char);
void CheckDoor(char, char, char);

#endif