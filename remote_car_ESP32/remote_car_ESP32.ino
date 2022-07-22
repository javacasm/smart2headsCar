//Librerías para WiFi:
  #include <WiFi.h>
  #include <ESPmDNS.h>
  #include <WiFiAP.h>

  #include "WiFiAccess.h"
  #include "myWebs.h"
  #include "ESP32.h"
  
//ficheros necesarios:
  #include "pins.h"

void setup(){
    initESP32();
}

void loop(){
    loopESP32();  
}
