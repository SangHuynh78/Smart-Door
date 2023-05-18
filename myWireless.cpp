#include "myWireless.h"

extern char StateDoorForWireless;
typedef enum{ S_CHECK=0, S_OPEN, S_OPENLONG} WLState_t;
static WLState_t WLState = S_CHECK;

void Wireless_State_Update(void)
{
  //chuyen trang thai
  switch (WLState) {
  case S_CHECK:
    switch (WL_Check()) {
    case 'O':
      WLState = S_OPEN;
      break;
    case 'S':
      WLState = S_OPENLONG;
      break;
    }
    break;
  case S_OPEN:
    WLState = S_CHECK;
    break;
  case S_OPENLONG:
  WLState = S_CHECK;
    // if (WL_Check() == 'C') WLState = S_CHECK;
    break;
  }
    //chuc nang
  switch (WLState) {
  case S_CHECK:
    StateDoorForWireless = 'C';
    break;
  case S_OPEN:
    myLCD_setCursor(0,1);
    myLCD_printString("   WELCOME!     ");
    StateDoorForWireless = 'O';
    break;
  case S_OPENLONG:
    myLCD_setCursor(0,1);
    myLCD_printString("   WELCOME!     ");
    StateDoorForWireless = 'S';
    break;
  }
}

char WL_Check(void)
{
  if (Serial.available())
  {
    return Serial.read();
  }
  else return 0;
}