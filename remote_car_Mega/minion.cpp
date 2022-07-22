#include <Arduino.h>

#include "machine.h"
#include "myCommands.h"
#include "myUltrasonic.h"
#include "dht_esp32.h"
#include "MEGA.h"

char *respuesta = "Not requested.";//los char solo almacena un caracter. Cuando queremos un texto (varios) usamos un puntero, que dice donde empieza ese texto. Si queremos modifiar ese texto usamos un String

char minionReceiveCommand(char incomingByte){
  float humidity = -100.0;
  float temperature = -100.0;
  float comSpeed= -100.0;
  
  Serial.print(">MEGA>:");
  Serial.println(incomingByte);
  switch(incomingByte){

    case IS_SERIAL_COMMAND:
      comSpeed = Serial2.parseFloat();//parseo es segmentar datos y entre ellos buscar lo que nos interesa
      Serial2.print(IS_SERIAL_COMMAND);
      Serial2.print(comSpeed);
      Serial2.print(END_NUMBER);  
      Serial.print (comSpeed);
      respuesta = " is the speed of Serial2";
      break;
 
    case FORWARD_COMMAND:
      robotForwardInstant();
      Serial2.print(FORWARD_COMMAND);
      respuesta = " forwards";
      break;   
       
    case RIGHT_COMMAND:
      robotRightInstant();
      Serial2.print(RIGHT_COMMAND);
      respuesta = " right";
      break;
  
    case RIGHT_PIVOT_COMMAND:
      robotRightPivotInstant();
      Serial2.print(RIGHT_PIVOT_COMMAND);
      respuesta = " right pivot";
      break;
  
    case LEFT_COMMAND:
      robotLeftInstant();
      Serial2.print(LEFT_COMMAND);
      respuesta = " left";
      break;
    
    case LEFT_PIVOT_COMMAND:
      robotLeftPivotInstant();
      Serial2.print(LEFT_PIVOT_COMMAND);
      respuesta = " left pivot";
      break;
      
    case BACKWARD_COMMAND:
      robotBackwardInstant();
      Serial2.print(BACKWARD_COMMAND);
      respuesta = " backwards";
      break;

    case BRAKE_COMMAND:
      robotBrakeInstant();
      Serial2.print(BRAKE_COMMAND);
      respuesta = " brake";
      break;
  
    case SMOOTHSTOP_COMMAND:
      robotSmoothStopInstant();
      Serial2.print(SMOOTHSTOP_COMMAND);
      respuesta = " turning machines off";
      break;

    case SET_SLOW_COMMAND:
      robotSetSpeed(SLOW);
      Serial2.print(SET_SLOW_COMMAND);
      respuesta = " speed: slow";
      break;

    case SET_MEDIUM_COMMAND:
      robotSetSpeed(MEDIUM);
      Serial2.print(SET_MEDIUM_COMMAND);
      respuesta = " speed: medium";
      break;

    case SET_FAST_COMMAND:
      robotSetSpeed(FAST);
      Serial2.print(SET_FAST_COMMAND);
      respuesta = " speed: fast";
      break;

    case RIGHT_MEASURING_COMMAND:
      rightMeasuring();
      Serial2.print(RIGHT_MEASURING_COMMAND);
      Serial2.print(rightDistance);
      Serial.print(" ");
      Serial.print(rightDistance);
      respuesta = " cm to the left";
      break;

    case MIDDLE_MEASURING_COMMAND:
      middleMeasuring();
      Serial2.print(MIDDLE_MEASURING_COMMAND);
      Serial2.print(middleDistance);
      Serial.print(" ");
      Serial.print(middleDistance);
      respuesta = " cm in front";
      break;

    case LEFT_MEASURING_COMMAND:
      leftMeasuring();
      Serial2.print(LEFT_MEASURING_COMMAND);
      Serial2.print(leftDistance);
      Serial.print(" ");
      Serial.print(leftDistance);
      respuesta = " cm to the left";
      break; 

    case TEMPERATURE_COMMAND:
      temperature = getTemperature();
      Serial2.print(TEMPERATURE_COMMAND);
      Serial2.print(temperature);
      Serial.print(" ");
      Serial.print(temperature);
      respuesta = " ºC";
      break;
        
    case HUMIDITY_COMMAND:
      humidity = getHumidity();
      Serial2.print(HUMIDITY_COMMAND);
      Serial2.print(humidity);
      Serial.print(" ");
      Serial.print(humidity);
      respuesta = " %";   
      break;
      
    default:
      respuesta = " I don't know...";
      Serial.print("Don't know what to do with ... ");
      Serial.println(incomingByte);
      break;
  }
  Serial2.flush();  // enviamos inmediatamente
  Serial.println(respuesta);
}
