#include <Arduino.h>
#include "myDoor.h"
#include "myRFID.h"
#include "myKEYPAD.h"
#include "myLCD.h"
#include "myWireless.h"

void setup() {
  Serial.begin(9600);
  InitRFID();
  InitKEYPAD();
  InitmyLCD();
  InitDoor();
}

char StateDoorForUID = 'C';
char StateDoorForPassWord = 'C';
char StateDoorForWireless = 'C';
void loop() {
  UID_State_Update();
  // OpenOrCloseDoor(StateDoorForUID);
  PassWord_State_Update();
  // OpenOrCloseDoor(StateDoorForPassWord);
  Wireless_State_Update();
  // OpenOrCloseDoor(StateDoorForWireless);
  CheckDoor(StateDoorForPassWord, StateDoorForUID, StateDoorForWireless);
}
