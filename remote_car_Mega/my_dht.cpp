#include <SimpleDHT.h>

//Ficheros necesarios
#include "pins.h" 

SimpleDHT11 dht11(DHTPIN);

long last_th_time=millis();
long th_intervalo = 2000; //medimos cada 2 segundos

float temperature, humidity;

// Tomado del ejemplo DHT11Default de SimpleDHT
bool getWeather() {//obtiene los valores que los dice el getTemp o getHumid
  long now = millis();
  if(now > last_th_time + th_intervalo){
    byte bTemperature = 0;
    byte bHumidity = 0;
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(&bTemperature, &bHumidity, NULL)) != SimpleDHTErrSuccess) {
      Serial.print("Read DHT11 failed, err="); 
      Serial.print(SimpleDHTErrCode(err));
      Serial.print(","); 
      Serial.println(SimpleDHTErrDuration(err));
      return false;
    } else {
      temperature = float(bTemperature);
      humidity = float(bHumidity);
      last_th_time = now;
      Serial.print(last_th_time);
      Serial.println(" Update temp&hum");
      return true;
    }
  }
  return true;

}

//estas funciones están cacheadas porque en lugar de llamar a la función y volver a medir, te dan el último valor
float getTemperature(){ // la temperatura es un float
    getWeather();
    return temperature;  
}

float getHumidity(){ // la humedad es un float
    getWeather();
    return humidity; 
}
