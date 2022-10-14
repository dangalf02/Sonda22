#include<Wire.h>
#include <math.h>
const int MPU=0x68;
float AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;  //int16_t
double pitch,roll;
int LedAz = 10;
int LedRj = 8;
int LedVr= 9;
int AcXoff,AcYoff,AcZoff,GyXoff,GyYoff,GyZoff;
void setup(){
Wire.begin();
Wire.beginTransmission(MPU);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(9600);
pinMode(LedAz, OUTPUT);
pinMode(LedRj, OUTPUT);
pinMode(LedVr, OUTPUT);

}
void loop(){
Wire.beginTransmission(MPU);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU,14,true);


int temp,toff;
double t,tx,tf;



//Temp
toff = -1600;

//Gyro 
GyXoff = 480;
GyYoff = 170;
GyZoff = 210;

//Accel correc
AcXoff = -300;  //-950;
AcYoff = 900; //-300;
AcZoff = 320;
//read accel data
AcX=(Wire.read()<<8|Wire.read()) + AcXoff;
AcY=(Wire.read()<<8|Wire.read()) + AcYoff;
AcZ=(Wire.read()<<8|Wire.read()) + AcZoff;
AcX=AcX/16384;
AcY=AcY/16384;
AcZ=AcZ/16384;

temp=(Wire.read()<<8|Wire.read()) + toff;
tx=temp;
t = tx/340 + 36.53;
tf = (t * 9/5) + 32;

readGyroData();

Serial.print("X= "); Serial.print(AcX,2);
Serial.print(" Y= "); Serial.print(AcY,2);
Serial.print(" Z= "); Serial.print(AcZ,2);

double g = sqrt(AcX * AcX + AcY * AcY + AcZ * AcZ);
Serial.print(" g= "); Serial.println(g,2);
//float vector = sqrt ( AcX + AcY +AcZ*AcZ );
//Serial.print(" | G = "); Serial.println(vector); 
delay(100);
// inicio nuevo
  if((AcX < -7000) or (AcX > 7000)){
  Serial.println ("");
  digitalWrite(LedVr, HIGH);
  }
  if((AcX < -10000) or (AcX > 10000)){
  Serial.println ("");
  digitalWrite(LedAz, HIGH);
  }
   if((AcX < -15000) or (AcX > 15000)){
  Serial.println ("");
  digitalWrite(LedRj, HIGH); 
   }
  
  }//termina loop
//convert the accel data to pitch/roll
void getAngle(int Vx,int Vy,int Vz) {
double x = Vx;
double y = Vy;
double z = Vz;

pitch = atan(x/sqrt((y*y) + (z*z)));
roll = atan(y/sqrt((x*x) + (z*z)));
//convert radians into degrees
pitch = pitch * (180.0/3.14);
roll = roll * (180.0/3.14) ;
}

void readGyroData(){
GyX=(Wire.read()<<8|Wire.read()) + GyXoff;
GyY=(Wire.read()<<8|Wire.read()) + GyYoff;
GyZ=(Wire.read()<<8|Wire.read()) + GyZoff;

}
