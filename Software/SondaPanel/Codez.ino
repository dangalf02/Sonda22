//   Procesos de datos 
void LeoSensores(){
// Leer voltaje del pin Analogico (panel solar)
// voltaje  global  un decimal
// Leer temperatura de un Dallas (18ds20) 
// temperatura global un decimal
  
temperatura=x;  //30.8;  
voltaje=3.2;
  
}
void PosServo(int NuevaPosicion){
  Serial.print("Nueva Pos: ");
  Serial.println(NuevaPosicion);

// PosAnt: int gloobal ,  valor guardado del ultimo movimiento
// pos:  int global , para movimiento suave  (for )
// ServoDelay  int global,  retardo entre pasos del servo
// La funcion termina guardano la posicion nueva en PosAnt
  
}//PosServo

//******************************************
// Funciones de conectividad y envio de datos
void RevisoWiFi_TB_RPC(){
  
  if (WiFi.status() != WL_CONNECTED) {
    reconnect();
    return;
  }
  if (!tb.connected()) {  // Reconnect to ThingsBoard
    subscribed = false;
    // Connect to the ThingsBoard
    Serial.print("Conectando a: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print("  token:  ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Falla conexion a Thingsboard");
      return;
    }
  } // !tb.connected
  if (!subscribed) {// Subscribe for RPC
    Serial.println("Subscribiendo RPC...");
    // Perform a subscription. All consequent data processing will happen in
    // callbacks as denoted by callbacks[] array.
    if (!tb.RPC_Subscribe(callbacks, COUNT_OF(callbacks))) {
      Serial.println("Falla subscribe de RPC");
      return;    }
    Serial.println("Subscribe done");
    subscribed = true;
  }// !subscribed (RPC)
  
}
void EnvioData(){

  if (send_passed > DataDelay) {// Veo de enviar data segun delay
    Serial.println("Envio data...");
    // Uploads telemetria a ThingsBoard usando MQTT. 
    // https://thingsboard.io/docs/reference/mqtt-api/#telemetry-upload-api 
      tb.sendTelemetryFloat("temperatura", temperatura);
      tb.sendTelemetryFloat("voltaje", voltaje);
      send_passed = 0;
      x++;  if(x==35){x=20;}
  } // Envio Data
  
}
void InitWiFi() {
  Serial.println("Conectando a AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("AP Conectado");
} // InitWiFi
void reconnect() {
  // Loop until we're reconnected
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Connected to AP");
  }
} // reconnect WiFi
