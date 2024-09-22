#include <WiFi.h>
#include <WebServer.h>
#include "ClientWifi.h"
#include "ServerWifi.h"

const char* ssid = "Eszti 2.4";
const char* password = "Three300";

WebServer server(80);  // Webszerver inicializálása port 80-on

const int ledPin = 2;  // A beépített LED (ESP32 esetén GPIO2)

void handleRoot() {
  server.send(200, "text/html", "<h1>ESP32 Webszerver</h1><p><a href=\"/LED_ON\"><button>LED bekapcsolása</button></a></p><p><a href=\"/LED_OFF\"><button>LED kikapcsolása</button></a></p>");
}

void handleLEDon() {
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/html", "<h1>LED BEKAPCSOLVA</h1><p><a href=\"/\"><button>Vissza</button></a></p>");
}

void handleLEDoff() {
  digitalWrite(ledPin, LOW);
  server.send(200, "text/html", "<h1>LED KIKAPCSOLVA</h1><p><a href=\"/\"><button>Vissza</button></a></p>");
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);

  WiFi.begin(ssid, password);  // Csatlakozás a WiFi-hez
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Csatlakozás a WiFi-hez...");
  }

  Serial.println("WiFi kapcsolódva!");
  Serial.print("IP cím: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/LED_ON", handleLEDon);
  server.on("/LED_OFF", handleLEDoff);

  server.begin();  // Webszerver indítása
}

void loop() {
  server.handleClient();  // Kezeli a bejövő kéréseket
}
