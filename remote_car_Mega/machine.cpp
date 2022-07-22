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
    //Serial.println(percent);
  }

//funciones de movimiento del robot (con motores CC, a partir movimientos del fichero "engines.h")
  void robotBrakeInstant (){
    M1Brake ();
    M2Brake ();
  }

// booleano decide si se hacen movimientos en bruto o se detecta la distancia
bool bControlDistance = false;

// funcion para cambiar el comportamiento
void setControlDistance(bool valor){
  bControlDistance = valor;
}

int limit_distance = 20;  //distancia mínima que se permite para evitar choques

void setLimitDistance(int valor){
  limit_distance = valor;
}
// FORWARD

// movimiento en bruto
  void bareForward(){
      M1Forward();
      M2Forward();    
  }
  
  void robotForwardInstant(){
    if (bControlDistance == true){
       int middleDistance = middleMeasuring();
      //Serial.println(middleDistance);
      while (middleDistance >limit_distance){
        bareForward();
        middleMeasuring();
        //Serial.println(middleDistance);
      }
      robotBrakeInstant();     
    } else {
      bareForward();
    }

  }

  
  void robotForward(int duracion){
    if (bControlDistance == true){
      for (int times = 0; times < duracion/500; times++){
        bareForward();
        int middleDistance = middleMeasuring();
        //Serial.println(middleDistance);
        if (middleDistance <limit_distance){
          robotBrakeInstant();
        }
        delay (400);
      }
      robotBrakeInstant();      
    } else {
      bareForward();
    }    
  }

// RIGHT

  void bareRight(){
    M1Forward();
    M2Backward();    
  }
  
  void robotRightInstant (){
    if (bControlDistance == true){
      int rightDistance = rightMeasuring();
      //Serial.println(rightDistance);
      while (rightDistance >limit_distance){
        bareRight();
        rightMeasuring();
      //Serial.println(rightDistance);
      }
      robotBrakeInstant();      
    } else {
      bareRight();
    }    

  }

  void robotRight(int duracion){
    if (bControlDistance == true){
      bareRight();
      for (int times = 0; times < duracion/500; times++){
        int rightDistance = rightMeasuring();
       // Serial.println(rightDistance);
        if (rightDistance <limit_distance){
          robotBrakeInstant();
        }
        delay (400);
      }
      robotBrakeInstant();      
    } else {
      bareRight();
    }    

  }

// RightPivot

  void bareRightPivot(){
    M1Forward();
    M2Brake();    
  }
  
  void robotRightPivotInstant (){
    if (bControlDistance == true){
      int rightDistance = rightMeasuring();
   // Serial.println(rightDistance);
      while (rightDistance >limit_distance){
        bareRightPivot();
        rightMeasuring();
     // Serial.println(rightDistance);
      }
      robotBrakeInstant();     
    } else {
      bareRightPivot();
    }    

  }


  
  void robotRightPivot (int duracion){
    if (bControlDistance == true){
      bareRightPivot();
      for (int times = 0; times < duracion/500; times++){
        int rightDistance = rightMeasuring();
        //Serial.println(rightDistance);
        if (rightDistance <= limit_distance){
          robotBrakeInstant();
        }
        delay (400);
      }
      robotBrakeInstant();      
    } else {
      bareRightPivot();
    }    
 
  }

// LEFT 

  void bareLeft(){
    M1Backward();
    M2Forward();
  }
  
  void robotLeftInstant (){
    if (bControlDistance == true){
      int leftDistance = leftMeasuring();
      //Serial.println(leftDistance);
      while (leftDistance >limit_distance){
        bareLeft();
        leftMeasuring();
     // Serial.println(leftDistance);
      }      
      robotBrakeInstant();
    } else {
      bareLeft();
    }

  }
  
  void robotLeft(int duracion){
    if (bControlDistance == true){
      bareLeft();
      for (int times = 0; times < duracion/500; times++){
        int leftDistance = leftMeasuring();
        //Serial.println(leftDistance);
        if (leftDistance <limit_distance){
          robotBrakeInstant();
        }
        delay (400);
      }
      robotBrakeInstant();      
    } else {
      bareLeft();
    }    

  }

// LeftPivot

  void bareLeftPivot(){
    M1Brake();
    M2Forward();    
  }
  
  void robotLeftPivotInstant (){
    if (bControlDistance == true){
      int leftDistance = leftMeasuring();
      //Serial.println(leftDistance);
      while (leftDistance >limit_distance){
        bareLeftPivot();
        leftMeasuring();
        //Serial.println(leftDistance);
      }
      robotBrakeInstant();      
    } else {
      bareLeftPivot();
    }    

  }
  
  void robotLeftPivot (int duracion){
    if (bControlDistance == true){
      bareLeftPivot();
      for (int times = 0; times < duracion/500; times++){
        int leftDistance = leftMeasuring();
        //Serial.println(leftDistance);
        if (leftDistance <limit_distance){
          robotBrakeInstant();
        }
        delay (400);
      }
      robotBrakeInstant();      
    } else {
      bareLeftPivot();
    }    

  }

// BACKWARD

  void robotBackwardInstant (){
    M1Backward();
    M2Backward();
  }
  
  void robotBackward(int duracion){
    robotBackwardInstant();
    delay (duracion);
  }

// STOP
  
  void robotSmoothStopInstant(){
    M1SmoothStop();
    M2SmoothStop();
  }
  
  void robotSmoothStop(int duracion){
    robotSmoothStopInstant();
    delay (duracion);
  }
   
