#ifndef myLCD_h
#define myLCD.h
#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

void InitmyLCD(void);
void myLCD_clear(void);
void myLCD_setCursor(uint8_t, uint8_t);
void myLCD_printChar(char c);
void myLCD_printString(char[]);

#endif