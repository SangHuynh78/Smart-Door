#ifndef myKEYPAD_h
#define myKEYPAD.h

#include <Arduino.h>
#include <Wire.h> 
#include <Keypad_I2C.h>
#include <Keypad.h>
#include "myDoor.h"
#include "myLCD.h"

#define I2CADDR   0x20

void InitKEYPAD(void);
char PW_Check(void);
void PassWord_State_Update(void);

#endif