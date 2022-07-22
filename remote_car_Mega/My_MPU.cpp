#include<Wire.h>//librería para el i2c
#include <Arduino.h>
#include <MPU9250_asukiaaa.h>
// Codigo del ejemplo GetData de MPU9250_asukiaaa

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t aSqrt,AcX,AcY,AcZ,GyX,GyY,GyZ,mDirection, mX, mY, mZ;

MPU9250_asukiaaa mySensor;

void initMPU (){
  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();

  // You can set your own offset for mag values
  mySensor.magXOffset = 6;
  mySensor.magYOffset = -42;
  mySensor.magZOffset = 13;
  
}

void getSensorID(){
  uint8_t sensorId;
  if (mySensor.readId(&sensorId) == 0) {
    Serial.println("sensorId: " + String(sensorId));
  } else {
    Serial.println("Cannot read sensorId");
  }  
}

void getGy (){
 
 if (mySensor.gyroUpdate() == 0) {
    GyX = mySensor.gyroX();
    GyY = mySensor.gyroY();
    GyZ = mySensor.gyroZ();
    Serial.print(" GyX = "); Serial.print(GyX);
    Serial.print(" | GyY = "); Serial.print(GyY);
    Serial.print(" | GyZ = "); Serial.print(GyZ);
  } else {
    Serial.println("Cannot read gyro values");
  }
 
}

void getAc (){
  if (mySensor.accelUpdate() == 0) {
    AcX = mySensor.accelX();
    AcY = mySensor.accelY();
    AcZ = mySensor.accelZ();
    aSqrt = mySensor.accelSqrt();
    Serial.print("AcX = "); Serial.print(AcX);
    Serial.print(" | AcY = "); Serial.print(AcY);
    Serial.print(" | AcZ = "); Serial.print(AcZ);
    Serial.println(" | accelSqrt: " + String(aSqrt));
  } else {
    Serial.println("Cannod read accel values");
  }
}

float getAccelModule(){
  getAc ();
  return aSqrt;
}

void getMag(){
   if (mySensor.magUpdate() == 0) {
    mX = mySensor.magX();
    mY = mySensor.magY();
    mZ = mySensor.magZ();
    mDirection = mySensor.magHorizDirection();
    Serial.print("magX: " + String(mX));
    Serial.print("| maxY: " + String(mY));
    Serial.print("| magZ: " + String(mZ));
    Serial.print("| horizontal direction: " + String(mDirection));
  } else {
    Serial.println("Cannot read mag values");
  }
}

float getMagDirection(){
  getMag();
  return mDirection;
}

float Tempt;

void getTemp (){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x41);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,2,true);  // request a total of 14 registers

  int16_t Tmp =Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  Tempt = Tmp/340.00+36.53;
  Serial.print(" | Tmp = "); Serial.print(Tempt);  //equation for temperature in degrees C from datasheet

}
