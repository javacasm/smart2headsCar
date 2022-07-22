#include <Arduino.h>

#include "master.h"
#include "WiFiAccess.h"
#include "myWebs.h"
#include "myCommands.h"

#define SERIAL_SPEED 115200
int frecuenciaRefresco = 2000;
long ahora;

void initESP32() {
  Serial.begin(SERIAL_SPEED);
  Serial2.begin(SERIAL_SPEED);
  float handshake = sendCommandFloatReturnFloat(IS_SERIAL_COMMAND, (SERIAL_SPEED/100)*1.0);
  bool reintentar = true;
  while (reintentar == true){
    if (handshake == (SERIAL_SPEED/100)*1.0){
      Serial.println ("Serial2 is working as planned");
      reintentar = false;
    }
    else{
      Serial.print("Received datum: ");
      Serial.print (handshake);
      Serial.println (". Serial2 is not working properly...");
      delay (200);
      reintentar = true;
    }
  }

  /*lcd.init();
  lcd.backlight();*/
  getToTheNet();
  }

void loopESP32() {
  server_handleClient();
  delay(2);//le damos tiempo al servidor para que escuche datos y haga lo necesario

//hacer otro millis para pedir temp
  
  if (millis() > ahora+frecuenciaRefresco){//para que la IP se refesque continuamente
   /* lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("IP:");
    lcd.setCursor(3,1);
    lcd.print(whatsIP());*/
  }
  ahora = millis();//volvemos a tomar millis para refrescar tiempo

  cutOut();

  if (Serial.available()>0){//le hemos enviado un comando al master para que lo transmita al minion
    char request = char(Serial.read());
    sendCommand(request);
  }
}
