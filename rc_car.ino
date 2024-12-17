#include "animation.h"
#include "shape.h"
#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  


void setup(){
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
   // Create new characters:
  lcd.createChar(1, eye);
  lcd.createChar(2, LE1);
  lcd.createChar(3, LE2);
  lcd.createChar(4, LE3);
  lcd.createChar(5, LE4);
  
  lcd.clear();

}


void loop(){
  // set cursor to first column, first row
 right_eye();
 left_eye();
 delay(2000);
 left_eyeS();
 delay(2000);
 right_eye();
 left_eye();
 delay(1000);
 lcd.clear();
 delay(500);
}




void right_eye(){
  lcd.setCursor(5, 0);
  lcd.write(byte(1));
  lcd.setCursor(6, 0);
   lcd.write(byte(1));
   lcd.setCursor(5,1);
   lcd.write(byte(1));
   lcd.setCursor(6,1);
   lcd.write(byte(1));
}

void left_eye(){
  lcd.setCursor(9, 0);
  lcd.write(byte(1));
  lcd.setCursor(10, 0);
   lcd.write(byte(1));
   lcd.setCursor(9,1);
   lcd.write(byte(1));
   lcd.setCursor(10,1);
   lcd.write(byte(1));
}

void left_eyeS(){
  lcd.setCursor(9, 0);
  lcd.write(byte(2));
  lcd.setCursor(10, 0);
   lcd.write(byte(3));
   lcd.setCursor(9,1);
   lcd.write(byte(4));
   lcd.setCursor(10,1);
   lcd.write(byte(5));
}



