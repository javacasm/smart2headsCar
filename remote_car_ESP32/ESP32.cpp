#include <Arduino.h>

#include "master.h"
#include "WiFiAccess.h"
#include "myWebs.h"
#include "myCommands.h"
#include "myLcd.h"
#include "config.h"
#include "pins.h"
#include "cached_replies.h"

#define SERIAL_SPEED 115200

int frecuenciaRefresco = 1000;
long ultimoUpdateLCD;
bool last_beat = HIGH; // Lo usamos para comprobrar que hay conexion y sincronizacion

void initESP32() {
  Serial.begin(SERIAL_SPEED);
  Serial2.begin(SERIAL_SPEED);

  Serial.print("Version:");
  Serial.println(VERSION);

  pinMode(LED,OUTPUT);

  // Cambio de orden para tener depuracion por el LCD
  Serial.println("initLCD");
  initLcd();
  testLcd();
  
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
  getToTheNet();

  // Lo hacemos en el refresco del lCD
  /*updateTemperature();
  updateHumidity();
  float temperature = getTemperature();
  float humidity = getHumidity();
  Serial.print ("T: ");
  Serial.print(temperature);
  Serial.print("ºC & H: ");
  Serial.print(humidity);
  Serial.println("%."); */
  }

void loopESP32() {
  server_handleClient();
  delay(2);//le damos tiempo al servidor para que escuche datos y haga lo necesario
  
//hacer otro millis para pedir temp
  if (millis() > ultimoUpdateLCD+frecuenciaRefresco){//para que la IP se refesque continuamente
    // eraseLcd(); // Repintamos encima
    pointerLcd(0,rowsLcd()-1,"IP:");
    ipLcd(3,rowsLcd()-1);
    pointerLcd(columnsLcd()-7,0,VERSION);
    pointerLcd(1,0,"T:");
    pointerLcd(6,0,"H:");
 
    updateTemperature();
    float temperature = getTemperature();
    intLcd(3,0,(int)temperature);
    
    updateHumidity();    
    float humidity = getHumidity();
    intLcd(8,0,(int)humidity);     
    Serial.print ("T: ");
    Serial.print(temperature);
    Serial.print("ºC & H: ");
    Serial.print(humidity);
    Serial.println("%.");

    // HEARTBEAT
    if (last_beat == HIGH) {
       charLcd(0,0,'|');
       digitalWrite(LED,HIGH);
       sendCommand(HEART_BEAT_HIGH);
       last_beat = LOW;
    } else {
       charLcd(0,0,'-');
       digitalWrite(LED,LOW);
       sendCommand(HEART_BEAT_LOW);  
       last_beat = HIGH;  
    }     
    ultimoUpdateLCD = millis(); // anotamos el tiempo de la actualizacion       
  }
  
// Lo he comentado porque corta sin motivo ¿Hay otro estado por defecto?
  if (isLocalConnection() == true){
    if (WiFi.status() != WL_CONNECTED){//Si estamos conectados al WiFi local y de pronto perdemos conexión
      cutOut();
    }
  }

  if (Serial.available()>0){//le hemos enviado un comando al master para que lo transmita al minion
    char request = char(Serial.read());
    sendCommand(request);
  }
}
