//Librerías para pantalla LCD:
  #include <Wire.h> 
  #include <LiquidCrystal_I2C.h>

  #include "config.h"
  
// constructores LCD
// constantes definidas en config.h
  LiquidCrystal_I2C lcd(LCD_ADDRESS,LCD_COLUMNS,LCD_ROWS);//asignamos al LCD la dirección 0x27, usual, y especificamos que tiene 16 espacios y 2 filaS

#include "WiFiAccess.h"

void initLcd (){
  lcd.begin(); // No es init, es begin
  lcd.backlight();
}

void eraseLcd(){
  lcd.clear();
}

void intLcd (int x, int y, int message){
  lcd.setCursor(x,y);
  lcd.print(message);
}

void floatLcd(int x, int y, float message){
  lcd.setCursor(x,y);
  lcd.print(message);
}

void pointerLcd (int x, int y, char* message){
  lcd.setCursor(x,y);
  lcd.print(message);
}

void charLcd (int x, int y, char message){
  lcd.setCursor(x,y);
  lcd.print(message);
}

void ipLcd (int x, int y){
  lcd.setCursor(x,y);
  lcd.print(whatsIP());
}

void testLcd(){
  eraseLcd();
  pointerLcd(0,0,"Test LCD");
}
