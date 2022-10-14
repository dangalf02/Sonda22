//  SondaPanel  modulo con paneles solares desplegables por servo
//  mide temperatura y voltaje entregado por los paneles
// Envia datos a ThingsBoard Panel Sonda22 (sector rojo)
//    Dispositivo Servo01 con alias ServoSolar
// Board: Lolin (Wemos) D1 R1
// Librerias:  ArduinoJson 6.9.1    Thingsboard 0.2.0

String vers = "Sonda22 Panel v1.0 2022Oct13";
#include <Servo.h>            // Libreria servo       
#include <ESP8266WiFi.h>     // WiFi control for ESP32
#include <ThingsBoard.h>    // ThingsBoard SDK

// Helper macro to calculate array size
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#define WIFI_AP_NAME "Varix"
#define WIFI_PASSWORD "wonder01"
#define TOKEN               "eOYUh7lDt2kMDZnE8Wuy"
#define THINGSBOARD_SERVER  "demo.thingsboard.io"
#define VelocSerial    115200

WiFiClient espClient;
ThingsBoard tb(espClient);
int status = WL_IDLE_STATUS;

int pos,PosAnt = 0;  int ServoPos=0;
static const int ServoGPIO = 14;
int ServoDelay=20;
Servo servo;  
int DataDelay=50;
// Periodo de envio
int send_delay = 4000;  int send_passed=0;
bool subscribed = false;
float temperatura; float voltaje;
int x=20;

// Processes function for RPC call "setValue"
// RPC_Data is a JSON variant, that can be queried using operator[]
// https://arduinojson.org/v5/api/jsonvariant/subscript/ for more details
RPC_Response processDelayChange(const RPC_Data &data){
  Serial.println("Recibí set Posicion Servo RPC method");
  ServoPos = data;
  PosServo(ServoPos);
  return RPC_Response(NULL, ServoPos);
}

RPC_Response processGetDelay(const RPC_Data &data){
  Serial.println("Recibí  get value method");
  return RPC_Response(NULL, ServoPos);
}

// Sin USO Processes function for RPC call "setGpioStatus"
RPC_Response processSetGpioState(const RPC_Data &data){
  Serial.println("set GPIO RPC method");
  int pin = data["pin"];
  bool enabled = data["enabled"];
  return RPC_Response(data["pin"], (bool)data["enabled"]);
}

// RPC handlers
RPC_Callback callbacks[] = {
  { "setValue",         processDelayChange },
  { "getValue",         processGetDelay },
  { "setGpioStatus",    processSetGpioState },
};

void setup() {
  servo.attach(ServoGPIO,500,2250);
  Serial.begin(VelocSerial);
  Serial.println("Start");
  Serial.print("Version: "); Serial.println(vers);
  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  InitWiFi();
}// setup

//****************************************
void loop() {
  delay(10);
  send_passed++;
  
  RevisoWiFi_TB_RPC();// Conn WiFi ThingsBoard y RPC
  LeoSensores();  
  EnvioData(); // Si corresponde envio dato de sensores

  tb.loop();  // Process messages
}// loop

//**************************EoF
