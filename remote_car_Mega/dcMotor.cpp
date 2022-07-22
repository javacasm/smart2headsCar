//Ficheros necesarios
#include "pins.h"
#include "config.h"

//funciones que inicializan las parejas de motores (IN1 e IN2, M1;e IN3 e IN4, M2) 
    void initM1(){
      pinMode(IN1, OUTPUT); 
      pinMode(IN2, OUTPUT);
      pinMode(ENA, OUTPUT);
    }
    
    void initM2(){
      pinMode(IN3, OUTPUT);
      pinMode(IN4, OUTPUT);
      pinMode(ENB, OUTPUT);
    }
    
    void M1SetSpeed(int percent){
      float speed = SPEED_FACTOR * percent / 100;
      analogWrite(ENA, int(speed));
    }

    
    void M2SetSpeed(int percent){
      float speed = SPEED_FACTOR*percent/100;
      analogWrite(ENB, int(speed));
    }

//funciones con los movimientos de cada pareja de motores (M1 y M2)
    void M1Forward(){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
    
    void M2Forward(){
      digitalWrite(IN3, LOW); 
      digitalWrite(IN4, HIGH); 
    }
    
    void M1Backward(){
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
    
    void M2Backward(){
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    
    void M1Brake(){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
    }
    
    void M2Brake(){
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
    }
    
    void M1SmoothStop(){
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
    }
    
    void M2SmoothStop(){
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
