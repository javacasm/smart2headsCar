void initUltrasonic();//inicializar

//variables
extern int rightDistance;//se pone extern para que el compilador no diga que la variable se ha definido múltiples veces (cuando la variable se necesita en el .cpp pero otros ficheros también la necesitan)
extern int middleDistance;
extern int leftDistance;

//medir distancia
int Distance_test();

int rightMeasuring ();
int middleMeasuring();
int leftMeasuring();
