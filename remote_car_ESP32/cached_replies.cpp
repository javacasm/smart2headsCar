#include "myCommands.h"
#include "master.h"

float temperature;
float humidity;

int rightDistance;
int middleDistance;
int leftDistance;

void updateTemperature(){//está función actualiza el valor de la temperatura para que quede guardado en la memoria
  temperature = sendCommandReturnFloat(TEMPERATURE_COMMAND);
}

float getTemperature(){//esta es la que el resto de ficheros utilizan para aceder al valor de la temperatura y está cacheada (coge el último valor en vez de volver a actualizar)
  return temperature;
}

void updateHumidity(){
  humidity = sendCommandReturnFloat(HUMIDITY_COMMAND);
}

float getHumidity(){//es función de tipo float porque nos devuelve un float
  return humidity;
}

void updateRightDistance(){
  rightDistance = sendCommandReturnFloat(RIGHT_MEASURING_COMMAND);
}

int getRightDistance(){
  return rightDistance;
}

void updateMiddleDistance(){
  middleDistance = sendCommandReturnFloat(MIDDLE_MEASURING_COMMAND);
}

int getMiddleDistance(){
  return middleDistance;
}

void updateLeftDistance(){
  leftDistance = sendCommandReturnFloat(LEFT_MEASURING_COMMAND);
}

int getLeftDistance(){
  return leftDistance;
}
