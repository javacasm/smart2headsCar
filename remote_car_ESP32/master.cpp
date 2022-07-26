#include <Arduino.h>
#include "myCommands.h"
#include "myLcd.h"
#include "config.h"

int time2waitResponse = 2000;
int contadorErrores=0; // consideramos error si no hay respuesta

int numero_errores(){
  return contadorErrores;
}


// funcion para enviar comando por Serial2, mostrandolo por Serial
// Devuelve un valor: RESULT_ERROR o RESULT_OK
int sendCommand(char command){  
  Serial2.print(command);
  Serial.print(">ESP32>: ");
  Serial.println(command);
  pointerLcd(columnsLcd()-2, rowsLcd()-1, ">");
  charLcd(columnsLcd()-1, rowsLcd()-1, command);
  int returnValue = RESULT_ERROR;//al final, dice si todo va bien o no
  long timeout = millis()+time2waitResponse;
  while (millis()<timeout){ // miramos si hay datos durante un tiempo
    if (Serial2.available()>0){//Hay respuesta
      char charResponse = char(Serial2.read());
      Serial.print("<ESP32<: ");// Mostramos por Serial para depuracion
      Serial.println(charResponse);
      if (charResponse == command){ 
        returnValue == RESULT_OK;
      }
      else {
        contadorErrores ++;
        Serial.print("Wrong response: (");
        Serial.print(charResponse);
        Serial.print(") errors: ");
        Serial.println(contadorErrores);
      }
      pointerLcd(columnsLcd()-2, rowsLcd()-1, "<");
      charLcd(columnsLcd()-1, rowsLcd()-1, charResponse);      
      break; // salimos del while
    } else {
      delay(time2waitResponse/100);//esperamos un poquito
    }
  }
  String strExceso;
  while(Serial2.available()>0){  // leemos si hay exceso de datos
    char charDeMas = char(Serial2.read());   
    strExceso += charDeMas;
  }
  if (strExceso.length()>0){
    Serial.print("Exceso de datos:");
    Serial.println(strExceso);
  }
  return returnValue;
}


// funcion para enviar comando con argumento entero por Serial2, mostrandolo por Serial
// Devuelve un valor: RESULT_ERROR o RESULT_OK
int sendCommandInt(char command,int valor){  
  Serial2.print(command);
  Serial2.print(valor);
  Serial2.print(END_NUMBER);
  Serial.print(">ESP32>: ");
  Serial.print(command);
  Serial.print(" ");
  Serial.print(valor);
  Serial.println(END_NUMBER);  
  
  pointerLcd(columnsLcd()-2, rowsLcd()-1, ">");
  charLcd(columnsLcd()-1, rowsLcd()-1, command);
  
  int returnValue = RESULT_ERROR;
  delay(time2waitResponse);//esperamos la respuesta
  if (Serial2.available()>0){//Hay respuesta
    char charResponse = char(Serial2.read());
    Serial.print("<ESP32<: ");      // Mostramos por Serial para depuracion
    Serial.println(charResponse);
    if (charResponse == command){ 
      returnValue == RESULT_OK;
    }
    else{
      contadorErrores ++;
      Serial.print("Wrong response: ");
      Serial.print(charResponse);
      Serial.print(" errors: ");
      Serial.println(contadorErrores);
    }
    pointerLcd(columnsLcd()-2, rowsLcd()-1, "<");
    charLcd(columnsLcd()-1, rowsLcd()-1, charResponse);      
  }
  else {
    contadorErrores ++;
    Serial.print("No responses. Errors: ");
    Serial.println(contadorErrores);
  }
  return returnValue;
}

int sendCommandFloatReturnFloat (char command, float valor){
  Serial2.print(command);
  Serial2.print(valor);
  Serial2.print(END_NUMBER);
  Serial.print(">ESP32>: ");
  Serial.print(command);
  Serial.print(" ");
  Serial.print(valor);
  Serial.println(END_NUMBER);  
  pointerLcd(columnsLcd()-2, rowsLcd()-1, ">");
  charLcd(columnsLcd()-1, rowsLcd()-1, command);
  
  float floatResponse = RESULT_ERROR;
  delay(time2waitResponse);//esperamos la respuesta
  if (Serial2.available()>0){//Hay respuesta
    Serial.print("<ESP32<: ");// Mostramos por Serial para depuracion
    char firstCharResponse = char(Serial2.read());
    Serial.println(firstCharResponse);
    if (firstCharResponse == command){
      floatResponse = Serial2.parseFloat();//parseo es segmentar datos y entre ellos buscar lo que nos interesa, en este caso busca un float
#ifdef DEBUG       
      Serial.print("The value has been received: ");
      Serial.println(floatResponse);
#endif      
      if (Serial2.available()>0){//si el minion padece incontinencia verbal, los datos sobrantes quedarán impresos pero no se usarán 
        Serial.print("Too many data: [");
        while (Serial2.available()>0){
          Serial.print(char(Serial2.read()));
        }
            Serial.println("]");
      } 
#ifdef DEBUG 
      else Serial.println("No more data.");
#endif      
    } 
    else {
      contadorErrores ++;
      Serial.print("Wrong response: ");
      Serial.print(firstCharResponse);
      Serial.print(" errors: ");
      Serial.println(contadorErrores);
    }
  }
  else {
    contadorErrores ++;
    Serial.print("No responses. Errors: ");
    Serial.println(contadorErrores);
  }
  return floatResponse;
  
}


// funcion para enviar un comando y que el MEGA nos devuelva un valor de tipo float
// Devuelve un valor: RESULT_ERROR o RESULT_OK
float sendCommandReturnFloat(char command){
  Serial2.print(command);
  Serial.print(">ESP32>: ");
  Serial.println(command);
  pointerLcd(columnsLcd()-2, rowsLcd()-1, ">");
  charLcd(columnsLcd()-1, rowsLcd()-1, command);
  
  float floatResponse = RESULT_ERROR;
  long timeout = millis()+time2waitResponse;
  while (millis()<timeout){ // miramos si hay datos durante un tiempo
   if (Serial2.available()>0){ // Hay respuesta
      char firstCharResponse = char(Serial2.read());
      Serial.print("<ESP32<: ");// Mostramos por Serial para depuracion      
      Serial.println(firstCharResponse);
      if (firstCharResponse == command){
            floatResponse = Serial2.parseFloat();//parseo es segmentar datos y entre ellos buscar lo que nos interesa, en este caso busca un float
  #ifdef DEBUG          
            Serial.print("The value has been received: ");
            Serial.println(floatResponse);
  #endif          
            if (Serial2.available()>0){//si el minion padece incontinencia verbal, los datos sobrantes quedarán impresos pero no se usarán 
              Serial.print("Too many data: [");
              while (Serial2.available()>0){
                Serial.print(char(Serial2.read()));
              }
              Serial.println("]");
            } 
  #ifdef DEBUG 
            else Serial.println("No more data.");
  #endif          
      } 
      else {
        contadorErrores ++;
        Serial.print("Wrong response: ");
        Serial.print(firstCharResponse);
        Serial.print(" errors: ");
        Serial.println(contadorErrores);
      }
      pointerLcd(columnsLcd()-2, rowsLcd()-1, "<");
      charLcd(columnsLcd()-1, rowsLcd()-1, firstCharResponse);      
      break; // salimos del while      
    }
    else {/*
      contadorErrores ++;
      Serial.print("No responses. Errors: ");
      Serial.println(contadorErrores);*/
      delay(time2waitResponse/100);
    }
  }
  return floatResponse;
}
