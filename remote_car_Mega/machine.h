//velocidad de los 4 motores
  #define SLOW 25
  #define MEDIUM 50
  #define FAST 100

//funciones que inicializan los componentes
  void initMachine();
  void robotSetSpeed(int speed);
  void setControlDistance(bool valor);
  bool areCrashesControled();

  
//funciones de movimiento del robot (con motores CC, a partir movimientos del fichero "dcMotor.h")
  void robotForwardInstant ();
  void robotForward(int duracion);

  void robotRightInstant ();
  void robotRight(int duracion);
  void robotRightPivotInstant ();
  void robotRightPivot (int duracion);
  
  void robotLeftInstant ();
  void robotLeft(int duracion);
  void robotLeftPivotInstant ();
  void robotLeftPivot (int duracion);
  
  void robotBackwardInstant ();
  void robotBackward(int duracion);
  
  void robotBrakeInstant ();
  
  void robotSmoothStopInstant ();
  void robotSmoothStop(int duracion);
