

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Varix";
const char* password = "wonder01";

#define TOKEN "dj4CkDAnyLDgtVcgcBtI" 
char ThingsboardHost[] = "demo.thingsboard.io";

WiFiClient wifiClient;
PubSubClient client(wifiClient);
int status = WL_IDLE_STATUS;
float V;
void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("connected to");
  Serial.println(ssid);
  client.setServer( ThingsboardHost, 1883 );
}

void loop()
{
if ( !client.connected() ) 
{
    reconnect();
}
 V= random(14);
float Voltaje =0.0;
int valor = analogRead(A0);
Voltaje = (valor*5)/1024;
//V=Voltaje;
ProcesoDataHttp();
  delay(60000);
}// loop

void ProcesoDataHttp()
{
  

  // Prepare a JSON payload string
  String payload = "{";
 payload += "\"Voltaje\":";
 payload += V; 
// payload += "\"Temperature\":";payload += 25; 
  payload += "}";

  char attributes[1000];
  payload.toCharArray( attributes, 1000 );
  client.publish( "v1/devices/me/telemetry",attributes);
  Serial.println( attributes );
   
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    status = WiFi.status();
    if ( status != WL_CONNECTED) {
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("Connected to AP");
    }
    Serial.print("Connecting to ThingsBoard node ...");
    // Attempt to connect (clientId, username, password)
    if ( client.connect("Esp8266", TOKEN, NULL) ) {
      Serial.println( "[DONE]" );
    } else {
      Serial.print( "[FAILED] [ rc = " );
      Serial.println( " : retrying in 5 seconds]" );
      delay( 500 );
    }
  }
}
