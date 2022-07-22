//Librerías para WiFi:
  #include <WiFi.h>
  #include <ESPmDNS.h>
  #include <WiFiAP.h>

//funciones para saber a qué red estamos conectados
  char* whatsSsid();
  char* whatsPassword();
  bool isLocalConnection();
  IPAddress whatsIP();

//funciones para conectarse o crear red
  void localConnecting();
  void softConnecting();

//función que finalmente decide si conectar o crear (usa todas las anteriores)
  void getToTheNet();

//función de emergencia que crea una red propia si nos salimos accidentalmente de la local
  void cutOut();
