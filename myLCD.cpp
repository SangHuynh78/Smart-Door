#include "myLCD.h"

LiquidCrystal_I2C LCD(0x27,16,2);

void InitmyLCD(void)
{
  LCD.init();                    
  LCD.backlight();
}

void myLCD_clear(void)
{
  LCD.clear();
}

void myLCD_setCursor(uint8_t col, uint8_t  row)
{
  LCD.setCursor(col,row);
}

void myLCD_printChar(char c)
{
  LCD.print(c);
}

void myLCD_printString(char str[])
{
  LCD.print(str);
}