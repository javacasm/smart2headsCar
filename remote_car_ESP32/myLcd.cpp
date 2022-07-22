//Librerías para pantalla LCD:
  #include <Wire.h> 
  #include <LiquidCrystal_I2C.h>

#include "config.h"
#include "WiFiAccess.h"

//propiedades del LCD usado
#ifdef JAVACASM
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 20
#define LCD_ROWS 4

#else
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2
#endif 



// constructores LCD
  LiquidCrystal_I2C lcd(LCD_ADDRESS,LCD_COLUMNS,LCD_ROWS);//asignamos al LCD la dirección 0x27, usual, y especificamos que tiene 16 espacios y 2 filaS

void initLcd (){
#ifdef JAVACASM 
  lcd.begin(); 
#else
  lcd.init();
#endif
  lcd.backlight();
}

char addressLcd(){
  return LCD_ADDRESS;
}

int columnsLcd(){
  return LCD_COLUMNS;
}

int rowsLcd(){
  return LCD_ROWS;
}


void eraseLcd(){
  lcd.clear();
#ifdef DEBUG
  Serial.println("eraseLcd");
#endif   
}


void intLcd (int x, int y, int message){
  lcd.setCursor(x,y);
  lcd.print(message);
#ifdef DEBUG
  Serial.println(String("[")+String(message)+"@"+String(x)+","+String(y)+String("]"));
#endif   
}

void floatLcd(int x, int y, float message){
  lcd.setCursor(x,y);
  lcd.print(message);
}

void pointerLcd (int x, int y, char* message){
  lcd.setCursor(x,y);
  lcd.print(message);
#ifdef DEBUG
  Serial.println(String("[")+String(message)+"@"+String(x)+","+String(y)+String("]"));
#endif  
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
  pointerLcd(0,0,"Test LCD:");
  pointerLcd(0,1,"Succeeded.");
}
