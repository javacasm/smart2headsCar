#include <Arduino.h>

#include "dcMotor.h"
#include "myUltrasonic.h"

//funciones que inicializan todos los motores (E1 y E2)
  void initMachine(){
   initM1();
   initM2();
  }
    
  void robotSetSpeed (int percent){
    M1SetSpeed(percent);
    M2SetSpeed(percent);
  }

//funciones de movimiento del robot (con motores CC, a partir movimientos del fichero "engines.h")
  void robotBrakeInstant (){
    M1Brake ();
    M2Brake ();
  }

  #define LIMIT_DISTANCE 20//distancia mínima que se permite para evitar choques
  
  void robotForwardInstant(){
    middleMeasuring();
    //Serial.println(middleDistance);
    while (middleDistance >LIMIT_DISTANCE){
      M1Forward();
      M2Forward();
      middleMeasuring();
      //Serial.println(middleDistance);
    }
    robotBrakeInstant();
  }

  void robotForward(int duracion){
    M1Forward();
    M2Forward();
    for (int times = 0; times < duracion/500; times++){
    middleMeasuring();
    //Serial.println(middleDistance);
    if (middleDistance <LIMIT_DISTANCE){
      robotBrakeInstant();
    }
    delay (400);
    }
    robotBrakeInstant();
  }
  
  void robotRightInstant (){
    rightMeasuring();
    //Serial.println(rightDistance);
    while (rightDistance >LIMIT_DISTANCE){
    M1Forward();
    M2Backward();
    rightMeasuring();
    //Serial.println(rightDistance);
    }
    robotBrakeInstant();
  }
  
  void robotRight(int duracion){
    M1Forward();
    M2Backward();
    for (int times = 0; times < duracion/500; times++){
    rightMeasuring();
   // Serial.println(rightDistance);
    if (rightDistance <LIMIT_DISTANCE){
      robotBrakeInstant();
    }
    delay (400);
    }
    robotBrakeInstant();
  }
  
  void robotRightPivotInstant (){
    rightMeasuring();
   // Serial.println(rightDistance);
    while (rightDistance >LIMIT_DISTANCE){
    M1Forward();
    M2Brake();
    rightMeasuring();
   // Serial.println(rightDistance);
    }
    robotBrakeInstant();
  }
  
  void robotRightPivot (int duracion){
    M1Forward();
    M2Brake();
    for (int times = 0; times < duracion/500; times++){
    rightMeasuring();
    //Serial.println(rightDistance);
    if (rightDistance <= LIMIT_DISTANCE){
      robotBrakeInstant();
    }
    delay (400);
    }
    robotBrakeInstant();
  }
  
  void robotLeftInstant (){
    leftMeasuring();
    //Serial.println(leftDistance);
    while (leftDistance >LIMIT_DISTANCE){
    M1Backward();
    M2Forward();
    leftMeasuring();
   // Serial.println(leftDistance);
    }
    robotBrakeInstant();
  }
  
  void robotLeft(int duracion){
    M1Backward();
    M2Forward();
    for (int times = 0; times < duracion/500; times++){
    leftMeasuring();
    //Serial.println(leftDistance);
    if (leftDistance <LIMIT_DISTANCE){
      robotBrakeInstant();
    }
    delay (400);
    }
    robotBrakeInstant();
  }
  
  void robotLeftPivotInstant (){
    leftMeasuring();
    //Serial.println(leftDistance);
    while (leftDistance >LIMIT_DISTANCE){
    M1Brake();
    M2Forward();
    leftMeasuring();
    //Serial.println(leftDistance);
    }
    robotBrakeInstant();
  }
  
  void robotLeftPivot (int duracion){
    M1Brake();
    M2Forward();
    for (int times = 0; times < duracion/500; times++){
    leftMeasuring();
    //Serial.println(leftDistance);
    if (leftDistance <LIMIT_DISTANCE){
      robotBrakeInstant();
    }
    delay (400);
    }
    robotBrakeInstant();
  }
  
  void robotBackwardInstant (){
    M1Backward();
    M2Backward();
  }
  void robotBackward(int duracion){
    robotBackwardInstant();
    delay (duracion);
  }
  
  void robotSmoothStopInstant(){
    M1SmoothStop();
    M2SmoothStop();
  }
  void robotSmoothStop(int duracion){
     robotSmoothStopInstant();
    delay (duracion);
  }
   
