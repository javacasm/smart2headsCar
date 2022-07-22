//Librerías para WiFi:
  #include <WiFi.h>
  #include <ESPmDNS.h>
  #include <WiFiAP.h>
  
#include "config.h"
#include "myWebs.h"
#include "myLcd.h"
#include "master.h"
#include "myCommands.h"


#ifdef JAVACASM
#define LOCAL_WIFI_SSID "OpenWrt"
#define LOCAL_WIFI_PASS "qazxcvbgtrewsdf"

#else
#define LOCAL_WIFI_SSID "Paravisa Digital D5C8"
#define LOCAL_WIFI_PASS "d5c8a3x4h7w9"
#endif

//Datos de las redes (primero probamos a conectarnos a la red local existente):
const char* localSsid = LOCAL_WIFI_SSID;
const char* localPassword = LOCAL_WIFI_PASS;

const char* softSsid = "Ars longa";//como tras intentarlo no nos hemos podido conectar, creamos nuestra propia red
const char* softPassword = "VitaBrevis";

//en primer lugar intentamos entrar a la red local
char* accessSsid = (char *) localSsid;
char* accessPassword = (char *) localPassword;


//¿Cuáles son los datos de la red a la que nos conectamos?
char* whatsSsid(){
  return accessSsid;
}
char* whatsPassword(){
  return accessPassword;
}


bool localConnection = false;//buleano que nos permitirá saber si estamos o no conectados a una red local

bool isLocalConnection(){//función para saber si estamos conectados a la red local
  return localConnection;
}

IPAddress myIP;

IPAddress whatsIP (){//para saber cuál es mi IP vigente
  return myIP;
}

void localConnecting(){//para conectarnos a red local
  accessSsid = (char *) localSsid;
  accessPassword = (char *) localPassword;
  localConnection = true;
  WiFi.mode(WIFI_STA);//station, significa que nos conectamos a otro wifi
  WiFi.begin(localSsid, localPassword);
  myIP = WiFi.localIP();
}

void softConnecting(){//para crear red propia
  accessSsid = (char *) softSsid;
  accessPassword = (char *) softPassword;
  localConnection = false;
  WiFi.softAP(softSsid, softPassword);
  myIP = WiFi.softAPIP();//creamos variable igual a la ip generada automáticamente por arduino
}

#define IP_TIME 10000//tiempo en que se mostrará la IP en el lcd
#define MESSAGE_TIME 3000//tiempo que se muestra un mensaje en el lcd
  
void getToTheNet (){
  Serial.print ("Connecting to local WiFi network: ");
  Serial.println (whatsSsid());
  WiFi.mode(WIFI_STA);//station, significa que nos conectamos a otro wifi
  WiFi.begin(whatsSsid(), whatsPassword());
  
  if (WiFi.status() != WL_CONNECTED) {//si no hemos logrado conectarnos 
    for (int counter = 30; counter > 0; counter = counter-1){//hasta 50 intentos para conectarse
        delay(500);
        Serial.print("Trying to connect... attempt ");
        Serial.println(30-counter);
        pointerLcd(0,0,"KEEP CALM & STAY");
        pointerLcd(0,1,"TUNNED UNTIL ");
        intLcd(13,1,counter);
        if (counter < 10){
          pointerLcd(13,1," ");
        }
        if (WiFi.status() == WL_CONNECTED){//si en alguno de los intentos logramos conectarnos nos saca del for
          break;
        }
    }
    if (WiFi.status() == WL_CONNECTED){//comprobamos si hemos salido del for, bien por haber excedido el número de intentos, bien por habernos logrado conectar; de ser esto último:
      localConnecting();
      }
    else{//en caso de haber salido del for por exceso de intentos
      softConnecting();
    }
  }
 else{//en caso de lograr conectarnos inmediátamente
    localConnecting();

  }
  if (MDNS.begin("esp32")) Serial.println("MDNS responder started");
  server_begin();   

  if (isLocalConnection() == true){//no hace falta poner la variable, la función en sí es un booleano
    Serial.println("");
    Serial.println("Local connection succeeded");
    Serial.print("Connected to ");
    Serial.println(whatsSsid());
    Serial.print("Local IP address: ");
    Serial.println(whatsIP());//local ip es la que me da el wifi al que nos conectamos
  
    eraseLcd();
    pointerLcd(0,0,"Local connection");
    pointerLcd(4,1,"succeeded");
    delay (MESSAGE_TIME);
    eraseLcd();
    pointerLcd(0,0,"LOCAL IP address");
    ipLcd(2,1);
    delay (IP_TIME);
    eraseLcd();
  }
 else {
    Serial.println("Connection to local WiFi network failed");
    Serial.println("Creating a brand new WiFi network...");
    Serial.println("Configuring access point...");
    Serial.print("SOFT IP address: ");
    Serial.println(whatsIP());
  
    eraseLcd();
    pointerLcd(0,0,"Local connection");
    pointerLcd(5,1,"failed");
    delay (MESSAGE_TIME);
    eraseLcd();
    pointerLcd(0,0,"SOFT IP address:");
    ipLcd(3,1);
    delay (IP_TIME);
    eraseLcd();
  }
}

void cutOut (){//función para crear una red si nos desconectamos de la red local 
  Serial.println("Local Wife has been cut down!");
  eraseLcd();
  pointerLcd(0,0,"Local connection");
  pointerLcd(0,1,"was interrupted");
  sendCommand(BRAKE_COMMAND);
  softConnecting();//creamos nuestra propia red

  Serial.println("Connection to the local WiFi network was interrupted");
  Serial.println("Creating a brand new WiFi network...");
  Serial.println("Configuring access point...");
  Serial.print("SOFT IP address: ");
  Serial.println(whatsIP());

  eraseLcd();
  pointerLcd(0,0,"SOFT IP address:");
  ipLcd(3,1);
  delay (IP_TIME);
  eraseLcd();
}
