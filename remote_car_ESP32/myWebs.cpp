//Librerías para WiFi:
  #include <WebServer.h>
  #include <WiFi.h>
  #include <ESPmDNS.h>
  #include <WiFiAP.h>

//Ficheros necesarios
  #include "pins.h"
  #include "WiFiAccess.h"
  #include "cached_replies.h"
  #include "myCommands.h"
  #include "master.h"

//constructores WiFi
WebServer server(80);// clase objeto(puerto)

int refresco = 5;

//funciones WiFi:
  String SendHTML (){//String es un tipo de variable que va añadiendo pedacitos de texto
    String message;
   if (isLocalConnection() == true){//web que se pondrá en marcha si nos conectamos al wifi local (fotos etc.)
      message = "<html><head><title>Remote Car</title><meta http-equiv=\"refresh\" content=\""+String(refresco)+"\" /><meta name=\"author\" content=\"Javacasm & ItachiSan25\" /><meta charset=\"utf-8\" /><link rel=\"shortcut icon\" a href=\"https://cdn.iconscout.com/icon/free/png-128/tesla-3521840-2945257.png\">";//fin metadatos//string va con + porque está sumando el refresh al content
      message += "<style>body{background-image:url(https://wallpaperaccess.com/full/851803.jpg); background-size:100% 100%; background-attachment:fixed;color:#ffffff; text-align:center;} table { text-decoration:none; color:#ffffff; font-family:Verdana,Helvetica; text-align:center; font-size:16px; } button {font: courier new, monospace; align=\"center\" valign=\"middle\"; color: #000000; background-color: #FFFFFF; border: 2px solid #7D7675; border-bottom: 4px solid #0F0E0E; border-right: 4px solid #0F0E0E; cursor: pointer;}</style></head>";//fin head
      message += "<body><table border=0 align=\"center\" valign=\"middle\"><tr><td bgcolor=#000000><h1><font face=georgia,monospace><i><b> ESP32 RACE CAR </h1></font></i></b></td></table><br><table border=0 align=\"center\" valign=\"middle\"><tr><td bgcolor=#000000 ><h3><font face= courier new, monospace>Feel the speed via real-time controls.</h3></font></td></table><hr>";//fin cabecera
     
      message += "<div style=\"width: 50%; float:left\">";//división de pantalla
      message += "<table border=0 align=\"center\" ><tr><td width=\"25%\" height=\"100\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\"><img src=\"https://www.pngkit.com/png/full/186-1868320_free-download-flecha-izquierda-curva-png-clipart-computer.png\" width=\"90\" height=\"90\" style=\"vertical-align: middle\"  value=\"LeftPivot\" onclick=\"window.location.href='/LeftPivot'\" ></button></td>";//primera fila primera celda (pivote izquierda)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\"><img src=\"https://upload.wikimedia.org/wikipedia/commons/thumb/e/ea/Flecha_arriba.svg/1200px-Flecha_arriba.svg.png\" width=\"90\" height=\"90\" style=\"vertical-align: middle\"  value=\"Forward\" onclick=\"window.location.href='/Forward'\" ></button></td>";//fin pirmera fila segunda celda (forward)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\"><img src=\"https://images.vexels.com/media/users/3/135771/isolated/preview/773a2d48124e420be0714e10c349348b-flecha-derecha-curva.png\" width=\"90\" height=\"90\" style=\"vertical-align: middle\"  value=\"RightPivot\" onclick=\"window.location.href='/RightPivot'\" ></button></td>";//primera fila tercera celda (pivote derecha)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\"><img src=\"https://image.freepik.com/vector-gratis/medidor-alto-riesgo_97886-3470.jpg\" width=\"90\" height=\"90\" style=\"vertical-align: middle\"  value=\"SetFast\" onclick=\"window.location.href='/SetFast'\" ></button></td>";//primera fila cuarta celda (fast)
  
      
      message += "<tr><td width=\"25%\" height=\"100\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\"><img src=\"https://image.flaticon.com/icons/png/512/32/32418.png\" width=\"90\" height=\"90\" style=\"vertical-align: middle\"  value=\"Left\" onclick=\"window.location.href='/Left'\" ></button></td>";//segunda fila primera celda (left)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\"><img src=\"https://upload.wikimedia.org/wikipedia/commons/thumb/8/8b/Stop_hand.svg/1024px-Stop_hand.svg.png\" width=\"90\" height=\"90\" style=\"vertical-align: middle\"  value=\"Brake\" onclick=\"window.location.href='/Brake'\" ></button></td>";//segunda fila segunda celda (brake)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\"><img src=\"https://image.flaticon.com/icons/png/512/33/33811.png\" width=\"90\" height=\"90\" style=\"vertical-align: middle\"  value=\"Right\" onclick=\"window.location.href='/Right'\" ></button></td>";//segunda fila tercera celda (right)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\"><img src=\"https://static.vecteezy.com/system/resources/previews/002/191/777/original/risk-icon-on-speedometer-medium-risk-meter-isolated-on-white-background-vector.jpg\" width=\"90\" height=\"90\" style=\"vertical-align: middle\"  value=\"SetMedium\" onclick=\"window.location.href='/SetMedium'\" ></button></td>";//segunda fila cuarta celda (medium)
  
  
      message += "<tr><td width=\"25%\" height=\"100\" align=\"center\" valign=\"middle\">&nbsp;</td>";//tercera fila primera celda (vacía)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\"><img src=\"https://i.pinimg.com/originals/0a/bf/ab/0abfab8799e4234e418b0cad4ed1d864.png\" width=\"90\" height=\"90\" style=\"vertical-align: middle\"  value=\"Backward\" onclick=\"window.location.href='/Backward'\" ></button></td>";//fin primera fila de la tabla//hacemos una conversión explicita, pasamos la variable float a cadena//tercera fila segunda celda (backward)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\">&nbsp;</td>";//tercera fila tercera celda (vacía)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\"><img src=\"https://media.istockphoto.com/vectors/gauge-meter-element-with-risk-level-in-a-flat-design-vector-id1216428045?k=6&m=1216428045&s=612x612&w=0&h=1z0Pq1zbs30ozom_HxsdYCteTn6FjHpVkJkyX8WzJCo=\" width=\"90\" height=\"90\" style=\"vertical-align: middle\"  value=\"SetSlow\" onclick=\"window.location.href='/SetSlow'\" ></button></td>";//tercera fila cuarta celda (slow)
      
      message += "</table>";//fin tabla
      message += "</div>";
  
      message += "<div style=\"width: 50%; float:right\">";//siguiente división
      message += "<br>";
      message += "<table border=0 align=\"center\" valign=\"middle\"><tr><td height=\"10\" bgcolor=#000000 ><h2><font face=georgia,monospace>Rightnow weather is:</h2><font></td></table>";//fin título
      message += "<table border=1 align=\"center\"><tr><td width=\"50%\" height=\"25\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>Temperature:</h4><font></td><td width=\"50%\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>"+String(getTemperature ())+ "ºC</h4><font></td>";//fin primera fila de la tabla (temperatura)
      message += "<tr><td height=\"25\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>Humidity:</h4><font></td><td align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>"+String(getHumidity())+"%</h4><font></td></table>";// fin segunda fila (humedad)
  
      message += "<table border=0 align=\"center\" valign=\"middle\"><tr><td height=\"10\" bgcolor=#000000 ><h2><font face=georgia,monospace>Car data:</h2><font></td></table>";//fin título
      message += "<table border=1 align=\"center\"><tr><td width=\"50%\" height=\"50\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" valign=\"middle\" style=\"width:100px;height:50px;\" value=\"RightMeasuring\" onclick=\"window.location.href='/RightMeasuring'\" ><font face = courier new, monospace><h4>&#8625; Right Measuring</h4></font></button></td><td width=\"50%\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>"+String(getRightDistance())+ "cm</h4><font></td>";//fin primera fila de la tabla (distancia derecha)
      message += "<tr><td width=\"50%\" height=\"25\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" valign=\"middle\" style=\"width:100px;height:50px;\" value=\"MiddleMeasuring\" onclick=\"window.location.href='/MiddleMeasuring'\" ><font face = courier new, monospace><h4>&#8593; Middle Measuring</h4></font></button></td><td width=\"50%\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>"+String(getMiddleDistance())+ "cm</h4><font></td>";//fin segunda fila de la tabla (distancia centro)
      message += "<tr><td width=\"50%\" height=\"25\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" valign=\"middle\" style=\"width:100px;height:50px;\" value=\"LeftMeasuring\" onclick=\"window.location.href='/LeftMeasuring'\" ><font face = courier new, monospace><h4>&#8624; Left Measuring</h4></font></button></td><td width=\"50%\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>"+String(getLeftDistance())+ "cm</h4><font></td>";//fin tercera fila de la tabla (distancia izquierda)
      
      message += "</div>";
  
      message += "</body></html>";//fin html
    }
    else{//web simplificada sin conexión a internet
      message = "<html><head><title>Remote Car</title><meta http-equiv=\"refresh\" content=\""+String(refresco)+"\" /><meta name=\"author\" content=\"Javacasm & ItachiSan25\" /><meta charset=\"utf-8\">";//fin metadatos//string va con + porque está sumando el refresh al content
      message += "<style>body{background-color:#000000; background-size:100% 100%; background-attachment:fixed;color:#2ACE00; text-align:center;} table {text-decoration:none; color:#2ACE00; font-family:Verdana,Helvetica; text-align:center; font-size:16px; } button {  vertical-align: \"middle\", font: courier new, monospace; color: #2ACE00; background-color: #000000; border: 2px solid #2ACE00; border-bottom: 4px solid #F8B3F0; border-right: 4px solid #F8B3F0; cursor: pointer;}</style></head>";//fin head
      message += "<body><p><h1><font color:#2ACE00 face=georgia,monospace><i><b> ESP32 RACE CAR </h1></font></i></b></p><p><h3><font color:#2ACE00 face= courier new, monospace>Feel the speed via real-time controls.</h3></font></p><hr>";//fin cabecera
     
      message += "<div style=\"width: 50%; float:left\">";//división de pantalla
      message += "<table border=0 align=\"center\" ><tr><td width=\"25%\" height=\"100\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" style=\"width:145px;height:80px;\" value=\"LeftPivot\" onclick=\"window.location.href='/LeftPivot'\" ><font face=georgia,monospace><h2><b>&#8624; LEFT <br> PIVOT</b></h2></font></button></td>";//primera fila primera celda (pivote izquierda)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" style=\"width:145px;height:80px;\" value=\"Forward\" onclick=\"window.location.href='/Forward'\" ><font face=georgia,monospace><h2><b>&#8593; <br> FORWARD</b></h2></font></button></td>";//fin primera fila segunda celda (forward)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" style=\"width:145px;height:80px;\" value=\"RightPivot\" onclick=\"window.location.href='/RightPivot'\" ><font face=georgia,monospace><h2><b>RIGHT &#8625; <br> PIVOT</b></h2></font></button></td>";//primera fila tercera celda (pivote derecha)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" style=\"width:145px;height:80px;\" value=\"SetFast\" onclick=\"window.location.href='/SetFast'\" ><font face=georgia,monospace><h2><b>FAST</b></h2></font></button></td>";//primera fila cuarta celda (fast)
  
      
      message += "<tr><td width=\"25%\" height=\"100\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" style=\"width:145px;height:80px;\" value=\"Left\" onclick=\"window.location.href='/Left'\" ><font face=georgia,monospace><h2><b>&#8634; LEFT</b></h2></font></button></td>";//segunda fila primera celda (left)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" style=\"width:145px;height:80px;\" value=\"Brake\" onclick=\"window.location.href='/Brake'\" ><font face=georgia,monospace><h2><b>&#215; <br> STOP</b></h2></font></button></td>";//segunda fila segunda celda (brake)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" style=\"width:145px;height:80px;\" value=\"Right\" onclick=\"window.location.href='/Right'\" ><font face=georgia,monospace><h2><b>RIGHT &#8635;</b></h2></font></button></td>";//segunda fila tercera celda (right)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" style=\"width:145px;height:80px;\" value=\"SetMedium\" onclick=\"window.location.href='/SetMedium'\" ><font face=georgia,monospace><h2><b>MEDIUM</b></h2></font></button></td>";//segunda fila cuarta celda (medium)
  
  
      message += "<tr><td width=\"25%\" height=\"100\" align=\"center\" valign=\"middle\">&nbsp;</td>";//tercera fila primera celda (vacía)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" style=\"width:145px;height:80px;\" value=\"Backward\" onclick=\"window.location.href='/Backward'\" ><font face=georgia,monospace><h2><b>BACKWARDS <br> &#8595;</b></h2></font></button></td>";//fin primera fila de la tabla//hacemos una conversión explicita, pasamos la variable float a cadena//tercera fila segunda celda (backward)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\">&nbsp;</td>";//tercera fila tercera celda (vacía)
      message += "<td width=\"25%\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" style=\"width:145px;height:80px;\" value=\"SetSlow\" onclick=\"window.location.href='/SetSlow'\" ><font face=georgia,monospace><h2><b>SLOW</b></h2></font></button></td>";//tercera fila cuarta celda (slow)
      
      message += "</table>";//fin tabla
      message += "</div>";
  
      message += "<div style=\"width: 50%; float:right\">";//siguiente división
      message += "<br>";
      message += "<table border=0 align=\"center\" valign=\"middle\"><tr><td height=\"10\" bgcolor=#000000 ><h2><font face=georgia,monospace>Rightnow weather is:</h2><font></td></table>";//fin título
      message += "<table border=1 align=\"center\"><tr><td width=\"50%\" height=\"25\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>Temperature:</h4><font></td><td width=\"50%\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>"+String(getTemperature ())+ "ºC</h4><font></td>";//fin primera fila de la tabla (temperatura)
      message += "<tr><td height=\"25\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>Humidity:</h4><font></td><td align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>"+String(getHumidity())+"%</h4><font></td></table>";// fin segunda fila (humedad)
  
      message += "<table border=0 align=\"center\" valign=\"middle\"><tr><td height=\"10\" bgcolor=#000000 ><h2><font face=georgia,monospace>Car data:</h2><font></td></table>";//fin título
      message += "<table border=1 align=\"center\"><tr><td width=\"50%\" height=\"60\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" style=\"width:100px;height:50px;\" value=\"RightMeasuring\" onclick=\"window.location.href='/RightMeasuring'\" ><font face = courier new, monospace><h4>&#8625; Right Measuring</h4></font></button></td><td width=\"50%\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>"+String(getRightDistance())+ "cm</h4></font></td>";//fin primera fila de la tabla (distancia derecha)
      message += "<tr><td width=\"50%\" height=\"25\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" style=\"width:100px;height:50px;\" value=\"MiddleMeasuring\" onclick=\"window.location.href='/MiddleMeasuring'\" ><font face = courier new, monospace><h4>&#8593; Middle Measuring</h4></font></button></td><td width=\"50%\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>"+String(getMiddleDistance())+ "cm</h4><font></td>";//fin segunda fila de la tabla (distancia centro)
      message += "<tr><td width=\"50%\" height=\"25\" align=\"center\" valign=\"middle\"><form method=\"GET\"><button type=\"button\" style=\"width:100px;height:50px;\" value=\"LeftMeasuring\" onclick=\"window.location.href='/LeftMeasuring'\" <font face = courier new, monospace><h4>&#8624; Left Measuring</h4></font></button></td><td width=\"50%\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>"+String(getLeftDistance())+ "cm</h4><font></td>";//fin tercera fila de la tabla (distancia izquierda)
      
      message += "</div>";
  
      message += "</body></html>";//fin html
    }
      return message;
  }
  
  
  void handleRoot() {//función para comprobar que la red funciona
    digitalWrite(LED, HIGH);
    server.send(200, "text/plain", "The network is working as planned...");
    digitalWrite(LED, LOW);
  }
  

  void handleControls(){
    digitalWrite(LED, HIGH);
    server.send(200, "text/html", SendHTML());
  }
  
  
  void handleRightMeasuring(){
    sendCommand(RIGHT_MEASURING_COMMAND);
    Serial.println("");
    Serial.print("Right distance is: ");  
    //Serial.println(rightDistance);
    Serial.println("");
    server.send(200, "text/html", SendHTML());
  }

  void handleMiddleMeasuring(){
    sendCommand(MIDDLE_MEASURING_COMMAND);
    Serial.println("");
    Serial.print("Middle distance is: ");  
    //Serial.println(middleDistance);
    Serial.println("");
    server.send(200, "text/html", SendHTML());
  }

  void handleLeftMeasuring(){
    sendCommand(LEFT_MEASURING_COMMAND);
    Serial.println("");
    Serial.print("Left distance is: ");  
    //Serial.println(leftDistance);
    Serial.println("");
    server.send(200, "text/html", SendHTML());
  }
  
  
  void handleForward() {
    Serial.println("Forwards");
    sendCommand(FORWARD_COMMAND);
    server.send(200, "text/html", SendHTML());
  }

  void handleBackward() {
    Serial.println("Backwards");
    sendCommand(BACKWARD_COMMAND);
    server.send(200, "text/html", SendHTML());
  }

  void handleRight() {
    Serial.println("Right");
    sendCommand(RIGHT_COMMAND);
    server.send(200, "text/html", SendHTML());
  }

  void handleRightPivot() {
    Serial.println("RightPivot");
    sendCommand(RIGHT_PIVOT_COMMAND);
    server.send(200, "text/html", SendHTML());
  }

  void handleLeft() {
    Serial.println("Left");
    sendCommand(LEFT_COMMAND);
    server.send(200, "text/html", SendHTML());
  }

  void handleLeftPivot() {
    Serial.println("LeftPivot");
    sendCommand(LEFT_PIVOT_COMMAND);
    server.send(200, "text/html", SendHTML());
  }

  void handleBrake() {
    Serial.println("Brake");
    sendCommand(BRAKE_COMMAND);
    server.send(200, "text/html", SendHTML());
  }

  void handleSetSlow() {
    Serial.println("Slow");
    sendCommand(SET_SLOW_COMMAND);
    server.send(200, "text/html", SendHTML());
  }

  void handleSetMedium() {
    Serial.println("Medium");
    sendCommand(SET_MEDIUM_COMMAND);
    server.send(200, "text/html", SendHTML());
  }

  void handleSetFast() {
    Serial.println("Fast");
    sendCommand(SET_FAST_COMMAND);
    server.send(200, "text/html", SendHTML());
  }

void handleWeather(){
  
  if (isnan(getTemperature()) == true || isnan(getHumidity()) == true){//Comprobamos que los valores caheados del sensor son posibles
    String message = "<p>ERROR_DHT</p>";
    server.send(200, "text/html",message);
  }
  else {
    String message;
    if (isLocalConnection() == true){//web que se pondrá en marcha si nos conectamos al wifi local (fotos etc.)
    message = "<html><head><title>Weather Station</title><meta http-equiv=\"refresh\" content=\""+String(refresco)+"\" /><meta name=\"author\" content=\"Javacasm & ItachiSan25\" /><meta charset=\"utf-8\" /><link rel=\"shortcut icon\" a href=\"https://freepngimg.com/download/earth/33030-2-earth-image.png\" type=\"image/x-icon\">";//fin metadatos//string va con + porque está sumando el refresh al content
    message += "<style>body{background-image:url(https://s1.1zoom.me/big0/323/346465-admin.jpg); background-size:100% 100%; background-attachment:fixed;color:white; text-align:center;} table { text-decoration:none; color:#ffffff; font-family:Verdana,Helvetica; text-align:center; font-size:16px; }</style></head>";//fin head
    message += "<body><h1><font face=georgia,monospace><b>Weather Station</h1></font></b><p><h3><font face= courier new, monospace>Real forecast brought to you in real time.</h3></font><hr>";//fin cabecera
    message += "<p><h2><font face=georgia,monospace>Rightnow weather is:</h2><font>";//fin título//String es un tipo de variable que va añadiendo pedacitos de texto
    message += "<table border=1 align=\"center\"><tr><td width=\"50%\" height=\"25\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>Temperature:</h4><font></td><td width=\"50%\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>"+String(getTemperature ())+ "ºC</h4><font></td>";//fin primera fila de la tabla//hacemos una conversión explicita, pasamos la variable float a cadena
    message += "<tr><td height=\"5\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>Humidity:</h4><font></td><td align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>"+String(getHumidity())+"%</h4><font></td></table>";// fin segunda fila
    message += "</body></html>";//fin html
    server.send(200, "text/html",message);//todos los mensajes de los navegadores tienen 3 datos: número que dice si la respuesta es correcta (OK=200, BASE DE DATOS ROTA=503, & ERROR=404), el formato de datos y el contenido
    }
    else{//versión sin conexión a internet
    message = "<html><head><title>Weather Station</title><meta http-equiv=\"refresh\" content=\""+String(refresco)+"\" /><meta name=\"author\" content=\"Javacasm & ItachiSan25\" /><meta charset=\"utf-8\" />";//fin metadatos//string va con + porque está sumando el refresh al content
    message += "<style>body{background-color:#000000; background-size:100% 100%; background-attachment:fixed;color:#2ACE00; text-align:center;} table { text-decoration:none; color:#2ACE00; font-family:Verdana,Helvetica; text-align:center; font-size:16px; }</style></head>";//fin head
    message += "<body><h1><font face=georgia,monospace><b>Weather Station</h1></font></b><p><h3><font face= courier new, monospace>Real forecast brought to you in real time.</h3></font><hr>";//fin cabecera
    message += "<p><h2><font face=georgia,monospace>Rightnow weather is:</h2><font>";//fin título//String es un tipo de variable que va añadiendo pedacitos de texto
    message += "<table border=1 align=\"center\"><tr><td width=\"50%\" height=\"25\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>Temperature:</h4><font></td><td width=\"50%\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>"+String(getTemperature ())+ "ºC</h4><font></td>";//fin primera fila de la tabla//hacemos una conversión explicita, pasamos la variable float a cadena
    message += "<tr><td height=\"5\" align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>Humidity:</h4><font></td><td align=\"center\" valign=\"middle\"><h4><font face = courier new, monospace>"+String(getHumidity())+"%</h4><font></td></table>";// fin segunda fila
    message += "</body></html>";//fin html
    server.send(200, "text/html",message);//todos los mensajes de los navegadores tienen 3 datos: número que dice si la respuesta es correcta (OK=200, BASE DE DATOS ROTA=503, & ERROR=404), el formato de datos y el contenido
    }
  }
  digitalWrite(LED, LOW);
}

void handleNotFound() {
  digitalWrite(LED, HIGH);
  String message = "File Not Found\n\n";  // De esta manera podemos hacer más fácilmente las webs
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(LED, LOW);
}

//funciones que pone en marcha todas las webs anteriores
void server_handleClient(){
  server.handleClient();
}

void server_begin(){
 //Webs que deberían funcionar
  server.on("/", handleRoot);//sirve para saber a qué sitios debería conectarse
  
  server.on("/Controls", handleControls);

  server.on("/RightMeasuring", handleRightMeasuring);
  server.on("/MiddleMeasuring", handleMiddleMeasuring);
  server.on("/LeftMeasuring", handleLeftMeasuring);
  
  server.on("/Forward", handleForward);
  server.on("/Backward", handleBackward);
  server.on("/Right", handleRight);
  server.on("/RightPivot", handleRightPivot);
  server.on("/Left", handleLeft);
  server.on("/LeftPivot", handleLeftPivot );
  server.on("/Brake", handleBrake);
  server.on("/SetSlow", handleSetSlow);
  server.on("/SetMedium", handleSetMedium);
  server.on("/SetFast", handleSetFast);
  
  server.on("/Weather", handleWeather);
  
  server.onNotFound(handleNotFound);

 //Arrancamos motores...
  server.begin();
  Serial.println("HTTP server started");
}
