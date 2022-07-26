//ficheros necesarios:
  #include "myServo.h"
  #include "myUltrasonic.h"
  #include "pins.h"
  #include "My_MPU.h"
  #include "machine.h"
  #include "minion.h"
  #include "my_dht.h"
  #include "myCommands.h"
  #include "config.h"

#define SERIAL_SPEED 115200

void initMEGA(){
  Serial.begin(SERIAL_SPEED);
  Serial2.begin(SERIAL_SPEED);  

  Serial.print("Version:");
  Serial.println(VERSION);

  pinMode(LED,OUTPUT);
  
  initMachine();
  Serial.println("Inicializado initMachine");
  robotSetSpeed (MEDIUM);
  initServo();
  Serial.println("Inicializado initServo");
  initUltrasonic();
  Serial.println("Inicializado initUltrasonic");
  initMPU();
  Serial.println("Inicializado MPU");
  Serial.println("Waiting for commands...");
}

int valor;//valor numérico que manda el ESP32 junto al comando en ocasiones
int whatValor(){//para saber que valor ha mandado el ESP32
  return valor;
}

void loopMEGA(){
  if (Serial2.available() > 0) {// ¿hay algun comando enviado?
    Serial.print("<MEGA<: "); 
    char command = char(Serial2.read());// leemos el comando
    Serial.println(command);//depuracion
    minionReceiveCommand(command);
  }
  if (Serial.available() > 0) {// ¿hay algun comando enviado por el teclado del ordenador?
    Serial.print("<MEGA(local)<: "); 
    char command = char(Serial.read());// leemos el comando
    Serial.println(command);//depuracion
    minionReceiveCommand(command);
  }
}
