#include "ServerWifi.h"

//private:


void ServerWifi::SendACK(){
 float ack=(rawdata-rawdata/100000)+1.0;
  SendRawData(ack);
}
// if one removed return true-> while not returning false check client!


//public

ServerWifi::ServerWifi(){
  rawdata=0.0;
  timeoutTime = millis() + 5000;
}
ServerWifi::ServerWifi(String username, String pw, unsigned host){
  Serial.begin(115200);
  username.toCharArray(SSID, U_P_SIZE);
  pw.toCharArray(pass, U_P_SIZE);
  HOST=(uint16_t)host;
  server=host;
  rawdata=0.0;
  timeoutTime = millis() + 5000;
}
ServerWifi::~ServerWifi(){
}
void ServerWifi::systembegin(){
    Serial.println("Connecting to WiFi...");
    WiFi.begin(SSID, pass);
    int i = 0;
    while (WiFi.status() != WL_CONNECTED){
       if (i > 2){
            esp_task_wdt_reset(); // Reset the watchdog timer to prevent a reset
            break;
           // i = 0;
        }
        delay(1000);
        i++;
        Serial.println("Connecting...");
    }
   
   if(WiFi.status() == WL_CONNECTED){
    Serial.println("Connected to WiFi");
    server.begin();
   }
}
bool ServerWifi::isConnected(){
  if(WiFi.status() != WL_CONNECTED){
    return false;
  }
  return true;
}
void ServerWifi::reconnect(){
    systembegin();
    server.end();
}
bool ServerWifi::Available(){
    if(client.connected() && client.available()) {
      /*if ( millis() > timeoutTime) {
        SendRawData(1.0);
        for(unsigned i=0; i<300; i++){
          if(!ReceiveRawData() && rawdata!=1.0){
            return false; 
          } // server disconnecting client because client didn't responed in time.
          delay(10);
        }
        rawdata=0.0;
        timeoutTime = millis() + 5000;
      }
        Serial.println("active client");*/
        return true;  // client connected
    }
    return false;
}

void ServerWifi::serverBeAvailable(){
  if(!client.connected()){
    Serial.println("no client");
    client.stop();
    //timeoutTime = millis() + 5000; 
    client = server.available();
  }
}

bool ServerWifi::ReceiveRawData(){

  bool output=false;
  if (client.connected() && client.available() >= sizeof(float)) {
    // Read byte array from client
    byte byteArray[sizeof(float)];
    client.readBytes(byteArray, sizeof(byteArray));
    // Convert byte array to float
    memcpy(&rawdata, byteArray, sizeof(float));
    Serial.println(rawdata);
    output=true;
  }
  return output;
}
float ServerWifi::getRawData(){
  return rawdata;
}

void ServerWifi::SendRawData( float param){
  // Convert float to byte array
  byte byteArray[sizeof(float)];
  memcpy(byteArray, &param, sizeof(float));
  // Send byte array
  client.write(byteArray, sizeof(byteArray));
}

bool ServerWifi::receiveString(String*str){
  if (client.available()){
    *str= client.readStringUntil('\n');
    return true;
  }
  return false;
}
bool ServerWifi::sendString(String param){
  if(client.connected()){
    client.println(param+"\n");
    return true;
  }
  return false;
}
void ServerWifi::setSwitch(bool const param){
  Switch=param;
}
bool ServerWifi::getSwitch()const{
  return Switch;
}

WiFiClient ServerWifi::getClient(){
  return client;
}
bool ServerWifi::setClient(WiFiClient param){
  param=server.available();
  int i=0;
  while(i<3){
    if(param.connected()){
      client=param;
      return true;
    }
    delay(200);
    i++;
  }
  return false;
}