#include <Servo.h>//Librerías para servo sin ESP32

#include "pins.h"

Servo myservo;//asociamos un nombre a nuestro servo

void initServo (){
  myservo.attach(SERVO);
}

void setServo(int angle){
  myservo.write(angle);
}
