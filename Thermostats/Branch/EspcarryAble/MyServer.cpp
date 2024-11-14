#include "MyServer.h"

// Konstruktor
MyServer::MyServer(String user, String pw, unsigned host) :  server(host) {  // WebSocketsServer példányosítás portszámmal
    ssid = user;
    pass = pw;
    Host=host;
    msg="null";
    index=nullptr;
    clients=new Clients();
    Data=new JSON_message();
}
MyServer::~MyServer(){
  if(index!=nullptr){
    delete index;
  }
  if(clients!=nullptr){
    delete clients;
  }
  if(Data!=nullptr){
    delete Data;
  }
}

// WiFi kapcsolat
void MyServer::Wifi_connection() {
    WiFi.begin(ssid.c_str(), pass.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print("Connecting...");
        delay(500);
    }
    Serial.print("Connected");
    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());
}

// Szerver indítása
void MyServer::Server_turning_on() {

  //websocket intit
  ws.onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    this->onEvent(server, client, type, arg, data, len);
  });
webSocket.onEvent([this]( WStype_t type, uint8_t* payload, size_t length) {
    this->onEvent1( type, payload, length);
});
  server.addHandler(&ws);
  Serial.println("WebSocket initialized");
  //html server initi
  server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
    request->send(200, "text/html", html_page());
  });
  server.on("/script.js", HTTP_GET, [this](AsyncWebServerRequest *request) {
    String js=get_Page()->get_java_script();
    request->send(200, "application/javascript", js); // JavaScript küldése
});

  server.begin(); 
}

void MyServer::connect_to_server(String ip){
  server_ip=ip;
  webSocket.begin(server_ip, Host, "/ws");
}
void MyServer::reconnect(){

  if (!webSocket.isConnected()) { // Ha nincs kapcsolat, próbálkozunk újracsatlakozással
    webSocket.begin(server_ip, Host, "/ws");
  }
}

// HTML oldal generálása
String MyServer::html_page() {
    if(index!=nullptr){
    return index->get_page();  
    }
    else{
      return "<html><head><head><body><h1>Index was nullptr!</h1></body></html>";
    }// HTML tartalom lekérése*/
}
void MyServer::create_html_page(String title){
    index=new HTML_page(title);
}

HTML_page* MyServer::get_Page(){
    return index;
}



 bool MyServer::check_ip_host(IPAddress clientIP) {
    WiFiClient client;
    if (client.connect(clientIP, Host)) {  // HOST-as port a HTTP kapcsolat
        client.print("GET / HTTP/1.1\r\nHost: ");
        client.print(clientIP.toString());
        client.print("\r\nConnection: close\r\n\r\n");

        // Várakozás a válaszra
        unsigned long timeout = millis();
        while (client.connected() && !client.available()) {
            if (millis() - timeout > DELAY) {  // 5 másodperces időkorlát
                client.stop();
                return false;
            }
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
        // Ellenőrizzük, hogy van-e válasz
        bool hasResponse = client.available();
        client.stop();
        return hasResponse;
    }
    return false;
}



// Weblap kiszolgálása

// WebSocket események kezelése
void MyServer::handleWebSocketMessage(void *arg, uint8_t *data, size_t len, String ip) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    String message = (char*)data;
     //Check if the message is "getReadings"
    String sensorReadings;
    if (strcmp((char*)data, "getReadings") == 0) {
     // if it is, send current sensor readings
      sensorReadings = get_JS_msg();
      notifyClients(sensorReadings);
    }
    else {
      sensorReadings=String((char*)data);
      Data->add_msg(sensorReadings, ip);
    }
    Serial.println("event"+sensorReadings);
  }
}

void MyServer::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:{
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      if(check_ip_host(client->remoteIP())){
        if(clients->add(client->remoteIP().toString(),client->id())){
          get_Page()->add_list_elem(client->remoteIP().toString().c_str(),+client->remoteIP().toString().c_str());
        }
      }
    }
      break;
    case WS_EVT_DISCONNECT:{
    //gondold át újra, hogy a jót törölje!
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      int afk=clients->Del(client->remoteIP().toString());
        if(-1!=afk){
          get_Page()->remove_list_elem(afk);
        }
    }
      break;
    case WS_EVT_DATA:
      this->handleWebSocketMessage(arg, data, len,client->remoteIP().toString());
      break;
    case WS_EVT_PONG:
      Serial.println("Received PONG from client");
      break;
    case WS_EVT_ERROR:
      Serial.println("WebSocket error occurred.");
      break;
  }
}
void  MyServer::onEvent1(WStype_t type, unsigned char* payload, size_t length) {
        switch (type) {
            case WStype_DISCONNECTED:
                Serial.println("Disconnected from server");
                break;
            case WStype_CONNECTED:
                Serial.println("Connected to server");
                break;
            case WStype_TEXT:{
                Serial.printf("Message received: %s\n", payload);
                String payloadString = String((char*)payload);
                Data->add_msg(payloadString, "ip_null");
                }
                break;
        }
}
void MyServer::notifyClients(String sensorReadings) {
  ws.textAll(sensorReadings);
}

// Szerver futtatása
void MyServer::run_server() {
    webSocket.loop();
    ws.cleanupClients();
}

void MyServer::updata(){
  notifyClients(get_JS_msg());
}
void MyServer::Client_update(){
  String str=get_JS_msg();
  webSocket.sendTXT(str);
}

void MyServer::sendMessage(){
    for(unsigned i=0; i< clients->getSize(); i++){
      ws.text(clients->get_ids()[i], get_JS_msg());
    }
}

void MyServer::set_JS_msg(String param){
 msg = param;
}
String MyServer::get_JS_msg(){
  String tmp=msg;
  msg="null";
  return tmp;
}

String MyServer::get_Mac()const{
  return String(WiFi.macAddress());
}

JSON_message *MyServer::get_received_data(){
  return Data;
}