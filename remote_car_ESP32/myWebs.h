#ifdef ESP32
//funciones WiFi de webs
  String SendHTML ();
  
  void handleRoot();
  
  void handleControls();

  void handleRightMeasuring();
  void handleMiddleMeasuring();
  void handleLeftMeasuring();
  
  void handleForward();
  void handleBackward();
  void handleRight();
  void handleRightPivot();  
  void handleLeft();
  void handleLeftPivot();
  void handleBrake();
  void handleSetSlow();
  void handleSetMedium();
  void handleSetFast();
  
  void handleWeather();
  
  void handleNotFound();

// funciones de gestion de server
  void server_begin();
  void server_handleClient();
#endif
