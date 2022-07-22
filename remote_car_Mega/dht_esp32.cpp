//Librerías para dht con esp32:
#include <DHTesp.h> 

//Ficheros necesarios
#include "pins.h" 

DHTesp dht;//complejo
TempAndHumidity newValues;

void initTemp(){dht.setup(DHTPIN, DHTesp::DHT11);}

bool getWeather() {//obtiene los valores que los dice el getTemp o getHumid
  if (dht.getStatus() != 0) {
  Serial.println("DHT11 error status: " + String(dht.getStatusString()));
  return false;
}
  newValues = dht.getTempAndHumidity(); // actualizamos el valor
  Serial.println(" T:" + String(newValues.temperature) + " H:" + String(newValues.humidity));
    return true;
}

//estas funciones están cacheadas porque en lugar de llamar a la función y volver a medir, te dan el último valor
float getTemperature(){ // la temperatura es un float
    return newValues.temperature;  
}

float getHumidity(){ // la humedad es un float
    return newValues.humidity; 
    }
