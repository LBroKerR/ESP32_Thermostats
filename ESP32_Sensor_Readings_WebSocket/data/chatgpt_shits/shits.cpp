//ha írok egy html és websocks szervert esp32-re, és egy másik esp32-vel csatlalkozok rá, akkor ez a részlet ugyan az marad: ws://${window.location.hostname}/ws;?

//esp32: const ws = new WebSocket(`ws://esp32_IP/ws`);


//értem, és ha mind kettőt szeretném használni, hogyan kéne eldöntenem, hogy egy windows böngészőből jött a hívás, vagy egy másik esp32-ről?
//1.
void Server_on(){
    //its just one function calling hihi
    server.on("/ws", HTTP_GET, [](AsyncWebServerRequest *request){
    String userAgent = request->header("User-Agent");

    if (userAgent.indexOf("ESP32") != -1) {
        // ESP32-ről érkező kérés
        request->send(200, "text/plain", "ESP32 client connected");
    } else {
        // Böngészőből érkező kérés
        request->send(200, "text/html", "Browser client connected");
    }
});
}

//2. Egyedi URL Paraméter

void Server_on(){
    server.on("/ws", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("client")) {
        String clientType = request->getParam("client")->value();
        
        if (clientType == "esp") {
            // ESP32-ről érkező kérés
            request->send(200, "text/plain", "ESP32 client connected");
        } else if (clientType == "browser") {
            // Böngészőből érkező kérés
            request->send(200, "text/html", "Browser client connected");
        }
    }
});
}

//3. WebSocket Üzenet Protokoll

void websocket_msg(){
    //kliens oldali
    webSocketClient.onEvent([](WStype_t type, uint8_t * payload, size_t length) {
    if (type == WStype_CONNECTED) {
        webSocketClient.sendTXT("Hello from ESP32");
    }
    });

    //server oldali
    webSocket.onEvent([](AsyncWebSocket * server, AsyncWebSocketClient * client, 
                     AwsEventType type, void * arg, uint8_t * data, size_t len) {
    if (type == WS_EVT_DATA) {
        String message = (char*)data;
        
        if (message == "Hello from ESP32") {
            // ESP32-ről érkezett
        } else {
            // Feltételezzük, hogy böngészőből érkezett
        }
    }
    });
}

//és, ha a kliens is egy szerver? 

//Mindkét ESP32 működhet úgy, hogy saját WebSocket szervert futtat, és egy másik WebSocket kapcsolatot nyit a partner ESP32 szerverére. Ebben az esetben így kezelheted az üzeneteket:

//ESP32 #1: Létrehoz egy WebSocket szervert és csatlakozik az ESP32 #2 WebSocket szerveréhez.
//ESP32 #2: Szintén futtat egy WebSocket szervert, és csatlakozik az ESP32 #1 szerveréhez.

//pl
//ESP32 #1 WebSocket Szerver és Kliens inicializálás:
AsyncWebServer server1(80);
AsyncWebSocket ws1("/ws1"); // ESP32 #1 szervere
AsyncWebSocketClient *clientToESP32_2; // Kapcsolat az ESP32 #2 felé

// Kapcsolódás az ESP32 #2 szerveréhez
void connectToESP32_2() {
    clientToESP32_2 = new AsyncWebSocketClient("ws://<ESP32_2_IP>/ws2");
    clientToESP32_2->onEvent(onEvent);
    clientToESP32_2->begin();
}

//ESP32 #2 WebSocket Szerver és Kliens inicializálás:

AsyncWebServer server2(80);
AsyncWebSocket ws2("/ws2"); // ESP32 #2 szervere
AsyncWebSocketClient *clientToESP32_1; // Kapcsolat az ESP32 #1 felé

// Kapcsolódás az ESP32 #1 szerveréhez
void connectToESP32_1() {
    clientToESP32_1 = new AsyncWebSocketClient("ws://<ESP32_1_IP>/ws1");
    clientToESP32_1->onEvent(onEvent);
    clientToESP32_1->begin();
}

//A célom az, hogy a fő szerveren megjelenítsek állandóan változó adatokat. és valamint html kód is dinamikusan változhat. A dinamikus html tag-k url-k a kliens szerverre mutatnak. Erre azért van szükség, hogy a user, könnyedén elérje bármelyik eszközét. és esetleg arra is, hogy az oldal lekérésével adatot olvassak ki a kliens szerverről, amelyek szenzor adatokat mutatnak.

//1. Dinamikus HTML Generálás a Fő Szerveren

void Server_on(){
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><body><h1>Devices</h1>";
    
    // Dinamikusan generált linkek az eszközökhöz
    for (auto& device : devices) {  // devices: egy lista a kliens eszközök IP-címeivel
        html += "<a href='http://" + device.ip + "'>" + device.name + "</a><br>";
    }
    html += "</body></html>";

    request->send(200, "text/html", html);
    });    
}

//2. WebSocket Alapú Valós Idejű Adatfrissítés

//Fő szerver WebSocket kód:

void websocket_receive(){

ws.onEvent([](AsyncWebSocket * server, AsyncWebSocketClient * client, 
              AwsEventType type, void * arg, uint8_t * data, size_t len) {
    if (type == WS_EVT_DATA) {
        // Beérkező adat feldolgozása és megjelenítése
    }
    });

}

//Példa HTTP GET kérés küldése a fő szerverről:

void http_get(){

    HTTPClient http;
    http.begin("http://" + deviceIP + "/sensor");
    int httpCode = http.GET();
    if (httpCode > 0) {
        String payload = http.getString();
        // Az adat megjelenítése a fő szerver felületén
    }
    http.end();

}


//ha megnyitom a fő szerverrel a kliens szervét az url-n keresztül, akkor hogyan vizsgálhatom, hogy elérhető/válaszol, vagy elérhetetlen?

//Példa HTTP GET kérés ellenőrzésre

#include <HTTPClient.h>

bool isClientAvailable(const String& clientUrl) {
    HTTPClient http;
    http.begin(clientUrl);  // pl.: "http://192.168.1.50/some_endpoint"
    int httpCode = http.GET();

    // Ellenőrzi, hogy a válaszkód érvényes-e
    if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
            Serial.println("Client is available and responding.");
            http.end();
            return true;  // Elérhető és válaszol
        } else {
            Serial.println("Client responded with an error code.");
        }
    } else {
        Serial.println("Client is not available or connection failed.");
    }

    http.end();
    return false;  // Elérhetetlen vagy hibás válasz
}

//Alkalmazása
//Elérhető: Ha a kliens szerver elérhető és válaszol, a HTTP_CODE_OK (200-as státuszkód) jelzi a sikeres kapcsolatot.
//Elérhetetlen vagy hibás válasz: Ha a szerver nem válaszol, vagy a válaszkód nem 200, akkor a kapcsolat meghiúsult vagy hiba történt.
//Ezzel a megoldással időnként lekérdezheted a kliens eszközök elérhetőségét a fő szerveren, és jelezheted a felhasználónak, ha valamelyik eszköz nem válaszol.