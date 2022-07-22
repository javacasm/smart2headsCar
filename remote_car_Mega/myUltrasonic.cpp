//Ficheros necesarios
#include "pins.h"
#include "myServo.h"

//función para inicializar el sensor de ultrasonidos
void initUltrasonic(){
 pinMode(ECHO, INPUT);    
 pinMode(TRIG, OUTPUT);
}

//funciones de medida del ultrasonidos
int distance;

int Distance_test() {//función que mide distancias
  digitalWrite(TRIG, LOW);   
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);  
  delayMicroseconds(20);
  digitalWrite(TRIG, LOW);   
  float fDistance = pulseIn(ECHO, HIGH);  
  fDistance= fDistance / 58;       
  return (int)fDistance;
}  

#define MEANWHILE 500

//funciones para medir a la derecha, el medio y la izquierda
int rightDistance;
int middleDistance;
int leftDistance;

int rightMeasuring (){
  myservo.write(SERVO_RIGHT);
  delay (MEANWHILE);
  rightDistance = Distance_test();
  return rightDistance;
}

int middleMeasuring(){
  myservo.write(SERVO_CENTRAL);
  delay (MEANWHILE);
  middleDistance = Distance_test();
  return middleDistance;
}

int leftMeasuring (){
  myservo.write(SERVO_LEFT);
  delay (MEANWHILE);              
  leftDistance = Distance_test();
  return leftDistance;
}
