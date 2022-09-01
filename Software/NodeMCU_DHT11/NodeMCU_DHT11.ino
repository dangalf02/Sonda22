// Medicion de Temp y Humedad con DHT11
#include <SPI.h>
#include <Wire.h>
#include "DHT.h"
#include <OneWire.h>
String vers = "Puerta18 DHT11  Ver 1.1 2022 Sept02 By BrosCom.net";
#define DHTPIN 0  // Pin del Arduino al cual esta conectado el pin 2 del sensor DHT1122
#define DHTTYPE DHT11  // DHT 22  ó DHT 11 
float temp=999; 
float humedaddht;         

void setup(){
  Serial.begin(9600);
  Serial.println(""); Serial.println("INICIO");
  Serial.println(vers);
  }//setup
void loop(){
    DHT dht(DHTPIN, DHTTYPE);
    dht.begin();
    humedaddht = dht.readHumidity();
    temp = dht.readTemperature();
    Serial.println("******** DHT Temp & Humedad **********" );    
    Serial.println(humedaddht);
    Serial.println(temp);
    Serial.println("" );Serial.println("" ); 
    delay(2000);         
  }//loop
