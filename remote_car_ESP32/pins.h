//librería imprescindible para saber cuales son los pines. NUNCA OLVIDAR
#include <Arduino.h>

//Ficheros necesarios
#include "config.h"

#ifdef SHIELD//placa escudo
//pin del led de la placa
#define LED LED_BUILTIN//Macro que significa el led que viene de serie en la placa

//pines del ultrasonidos
#define ECHO 5
#define TRIG 26

//pin del infrarrojos (siguelíneas)
#define LTM !digitalRead(17)

//pin al que se conecta el servo
#define SERVO 25

//pines a los que se conectan los cables de los motores CC y sus respectivos cables de velocidad
#ifdef JAVACASM//adaptados a JAVACASM (Elegoo Smart Robot Car Kit V2.0)
#define ENA 16
#define IN1 12
#define IN2 14

#define ENB 27
#define IN3 23
#define IN4 13

#else//adaptados a ITACHISAN25 (Elegoo Smart Robot Car Kit V3.0)
#define ENA 16
#define IN1 14
#define IN2 12

#define ENB 27
#define IN3 13
#define IN4 23

#endif

//pin del dht
#define DHTPIN 18

#else// sin placa escudo, los pines originales
//pin del led de la placa
#define LED LED_BUILTIN//Macro que significa el led que viene de serie en la placa

//pines del ultrasonidos
#define ECHO 10
#define TRIG 2

//pin del infrarrojos (siguelíneas)
#define LTM !digitalRead(4)

//pin al que se conecta el servo
#define SERVO 3

//pines a los que se conectan los cables de los motores CC y sus respectivos cables de velocidad
#ifdef JAVACASM//adaptados a JAVACASM (Elegoo Smart Robot Car Kit V2.0)
#define ENA 5
#define IN1 8
#define IN2 7

#define ENB 6
#define IN3 11
#define IN4 9

#else//adaptados a ITACHISAN25 (Elegoo Smart Robot Car Kit V3.0)
#define ENA 5
#define IN1 7
#define IN2 8

#define ENB 6
#define IN3 9
#define IN4 11

#endif

//pin del infrarrojos para recibir señales
#define RECV_PIN  12

//pin del dht
#define DHTPIN 13

#endif
