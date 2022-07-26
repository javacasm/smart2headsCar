#include <Arduino.h>

#include "machine.h"
#include "myCommands.h"
#include "myUltrasonic.h"
#include "my_dht.h"
#include "MEGA.h"
#include "pins.h"
#include "My_MPU.h"

char *respuesta = "Not requested.";//los char solo almacena un caracter. Cuando queremos un texto (varios) usamos un puntero, que dice donde empieza ese texto. Si queremos modifiar ese texto usamos un String

char minionReceiveCommand(char incomingByte){
  float humidity = -100.0;
  float temperature = -100.0;
  float comSpeed= -100.0;
  float accelModule = -100;
  float magDirection = -100;
  int rightDistance = -100;
  int middleDistance = -100;
  int leftDistance = -100;
  
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

    case CONTROL_CRASHES_COMMAND:
      Serial2.print(CONTROL_CRASHES_COMMAND);
      if ( areCrashesControled() == true){
        setControlDistance(false);
        Serial2.print(0.0);//para que el ESP32 sepa que está encendido.
        respuesta = "No crashes are being prevented.";
      }
      else{
        setControlDistance(true);
        Serial2.print(1.0);
        respuesta = "Crashes are being prevented.";
      }
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
      rightDistance = rightMeasuring();
      Serial2.print(RIGHT_MEASURING_COMMAND);
      Serial2.print(rightDistance);
      Serial.print(" ");
      Serial.print(rightDistance);
      respuesta = " cm to the left";
      break;

    case MIDDLE_MEASURING_COMMAND:
      middleDistance = middleMeasuring();
      Serial2.print(MIDDLE_MEASURING_COMMAND);
      Serial2.print(middleDistance);
      Serial.print(" ");
      Serial.print(middleDistance);
      respuesta = " cm in front";
      break;

    case LEFT_MEASURING_COMMAND:
      leftDistance = leftMeasuring();
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

    case HEART_BEAT_LOW:
      digitalWrite(LED,LOW);
      Serial2.print(HEART_BEAT_LOW);
      respuesta = " heartbeat Low";
      break;

    case HEART_BEAT_HIGH:
      digitalWrite(LED,HIGH);
      Serial2.print(HEART_BEAT_HIGH);
      respuesta = " heartbeat High";
      break;

    case MPU_ACCELL:
      accelModule = getAccelModule();
      Serial.println();
      Serial2.print(MPU_ACCELL);
      Serial2.print(accelModule);
      Serial.print(" ");
      Serial.print(accelModule);
      respuesta = " m/s2";
      break;
      
    case MPU_MAG:
      magDirection = getMagDirection();
      Serial.println();
      Serial2.print(MPU_MAG);
      Serial2.print(magDirection);
      Serial.print(" ");
      Serial.print(magDirection);
      respuesta = " grados ";
      break;      

    case TEST_ALL:
      respuesta = " just testing ...";
      // Test DHT
      Serial.print("Test DHT ");
      temperature = getTemperature();
      humidity = getHumidity();
      Serial.print(temperature);
      Serial.print(" C ");
      Serial.print(humidity);      
      Serial.println("%");
      
      // Prueba del MPU
      Serial.print("Test MPU Accel:");
      getAc();
      Serial.print("\nTest MPU Gyro:");      
      getGy();
      Serial.print("\nTest MPU Compass:");      
      getMag();
      Serial.print("\nTest MPU Temp:");      
      getTemp();      
      Serial.println();

      // Prueba Ultrasonidos
      Serial.print("Test ultrasonidos:");
      leftDistance = leftMeasuring();
      Serial.print(" left:");
      Serial.print(leftDistance);
      middleDistance = middleMeasuring();
      Serial.print(" cm - med:");
      Serial.print(middleDistance);
      Serial.print(" cm - right:");
      rightDistance = rightMeasuring();
      Serial.print(rightDistance);      
      Serial.println(" cm");

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
