// Test de Sleep    D0 conectado a RST para Wakeup
#include "Arduino.h"

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Start");
  delay(5000);

  // Deep sleep mode 10 segs
  Serial.println("Inicia Modo Sleep");
  ESP.deepSleep(10e6);
}
 
void loop() {
}
