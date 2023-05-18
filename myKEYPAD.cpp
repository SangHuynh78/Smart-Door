#include "myKEYPAD.h"

extern char StateDoorForPassWord;
int PW[6], PW0[6] = {'1','2','3','4','5','6'};
const byte ROWS=4;
const byte COLS=4;
char keys [ROWS][COLS] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
byte rowPins[ROWS] = {0,1,2,3};
byte colPins[COLS] = {4,5,6,7};
Keypad_I2C keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574);

void InitKEYPAD(void)
{
  Wire.begin();
  keypad.begin(makeKeymap(keys));
}

typedef enum{ S_CHECK=0, S_OPEN, S_ERROR} PWState_t;
static PWState_t PWState = S_CHECK;
void PassWord_State_Update(void)
{
  //chuyen trang thai
  switch (PWState) {
  case S_CHECK:
    switch (PW_Check()) 
    {
    case 'Y':
      PWState = S_OPEN;
      break;
    case 'N':
      PWState = S_ERROR;
      break;
    }
    break;
  case S_OPEN:
    PWState = S_CHECK;
    break;
  case S_ERROR:
    PWState = S_CHECK;
    break;
  }
    //chuc nang
  switch (PWState) {
  case S_ERROR:
    myLCD_setCursor(0,1);
    myLCD_printString("   TRY AGAIN!   ");
    Serial.println("Sai");                            //
    break;
  case S_OPEN:
    myLCD_setCursor(0,1);
    myLCD_printString("   WELCOME!     ");
    Serial.println("Dung");                           //
    StateDoorForPassWord = 'O';
    break;
  case S_CHECK:
    StateDoorForPassWord = 'C';
    break;
  }
}

int j=0;
char PW_Check(void)
{
  myLCD_setCursor(3,0);
  myLCD_printString("HAPPY HOME");
  char k = keypad.getKey();
  if (!k) return 0;
  else if (k == '*' && j != 0) {j = j -1; myLCD_setCursor(5+j,1); myLCD_printChar(' ');}
  else if (k == '#') {myLCD_clear(); j = 0;}
  else
  {
    if (!j) myLCD_clear();
    PW[j] = k;
    Serial.print((char)PW[j]);
    myLCD_setCursor(5+j,1);
    myLCD_printChar('*');
    j=j+1;
  }
  if (j >= 6)
  {
    j = 0;
    if (PW[0] != PW0[0] || PW[1] != PW0[1] || PW[2] != PW0[2] || PW[3] != PW0[3] || PW[4] != PW0[4] || PW[5] != PW0[5]) return 'N';
    else return 'Y';
  }
}