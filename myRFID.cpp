#include "myRFID.h"

extern char StateDoorForUID;
int UID[4], i;
int UID1[4] = {129,88,223,28};
int UID2[4] = {129,30,26,28};
MFRC522 mfrc522(SS_PIN, RST_PIN);

void InitRFID(void)
{
  SPI.begin();
  mfrc522.PCD_Init();
}

byte UID_Compare(int ID1[4], int ID2[4])
{
  for (byte i=0; i< 4; i++) {
    if (ID1[i] != ID2[i]) return 0; 
  }
  return 1;
}

char UID_Check()
{
  if ( !mfrc522.PICC_IsNewCardPresent() )
  {
    return 0;
  }
  if ( !mfrc522.PICC_ReadCardSerial() )
  {
    return 0;
  }
  
  Serial.print("UID cua the: ");

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {

    UID[i] = mfrc522.uid.uidByte[i];
    Serial.print(UID[i]);
    Serial.print(mfrc522.uid.uidByte[i] < 100 ? "  " : " ");
  }
  Serial.println();
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  if (UID_Compare(UID, UID1) || UID_Compare(UID, UID2) ) {UID[4] = (0,0,0,0);return 'Y';}
  else {UID[4] = (0,0,0,0);return 'N';}
}

typedef enum{ S_CHECK=0, S_OPEN, S_ERROR} UIDState_t;
static UIDState_t UIDState = S_CHECK;
void UID_State_Update(void)
{
  //chuyen trang thai
  switch (UIDState) {
  case S_CHECK:
    switch(UID_Check())
    {
    case 'Y':
      UIDState = S_OPEN;
      break;
    case 'N':
      UIDState = S_ERROR;
      break;
    }
    break;
  case S_OPEN:
    UIDState = S_CHECK;
    break;
  case S_ERROR:
    UIDState = S_CHECK;
    break;
  }
    //chuc nang
  switch (UIDState) {
  case S_ERROR:
    myLCD_setCursor(0,1);
    myLCD_printString("   TRY AGAIN!    ");
    break;
  case S_OPEN:
    myLCD_setCursor(0,1);
    myLCD_printString("   WELCOME!     ");
    StateDoorForUID = 'O';
    break;
  case S_CHECK:
    StateDoorForUID = 'C';
    break;
  }
}
