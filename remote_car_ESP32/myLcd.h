void initLcd ();
void testLcd();
char addressLcd();
int columnsLcd();
int rowsLcd();

void eraseLcd();

void intLcd (int x, int y, int message);
void floatLcd (int x, int y, float message);
void pointerLcd (int x, int y, char* message);
void charLcd (int x, int y, char message);
void ipLcd (int x, int y);
