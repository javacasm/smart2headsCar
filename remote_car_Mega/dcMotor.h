//funciones que inicializan las parejas de motores (M1, IN1 e IN2;y M2, IN3 e IN4) 
void initM1();
void initM2();
void M1SetSpeed(int percent);
void M2SetSpeed(int percent);

//funciones con los movimientos de cada pareja de motores (M1 y M2)
void M1Forward();
void M2Forward();

void M1Backward();
void M2Backward();

void M1SmoothStop();
void M2SmoothStop();

void M1Brake();
void M2Brake();
