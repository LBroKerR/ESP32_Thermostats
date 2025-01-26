#include "ClientWifi.h"

//private:

bool ClientWifi::ConnectToWiFi(){
  if(WiFi.status() != WL_CONNECTED) {
    delay(1000);//Serial.println("Connecting to WiFi...");
    return false;
  }
  return true;//Serial.println("Connected to WiFi");
}
bool ClientWifi::ConncetToServer(){
  if (client.connect(IP, HOST)) {
    return true;//Serial.println("Connected to server");
  } 
  //Serial.println("Connection to server failed");
  return false;
}

//public:
  ClientWifi::ClientWifi(){
  HOST=0;
  rawdata=0.0;
  data=0.0;
  ID=0;
  }
  ClientWifi::ClientWifi(String ip, String username, String pw, unsigned host ){
    ip.toCharArray(IP, IP_SIZE);
    username.toCharArray(SSID, U_P_SIZE);
    pw.toCharArray(pass, U_P_SIZE);
    HOST=host;
    rawdata=0.0;
    data=0.0;
    ID=0;
    WiFi.begin(SSID, pass);
    while(!ConnectToWiFi());
  }
  ClientWifi::~ClientWifi(){
    client.stop();
  }

  void ClientWifi::IsconnectedToWifi(){
    if(!WiFi.isConnected()){
      while(!ConnectToWiFi());
    }
  }
  void ClientWifi::IsconnectedToServer(){
     if(!client.connected()){
      client.stop();
      while(!ConncetToServer());
     }
  }

  void ClientWifi::sendData(float data){
    byte byteArray[sizeof(float)];
    memcpy(byteArray, &data, sizeof(float));
    // Send byte array
    client.write(byteArray, sizeof(byteArray));
  }
  void ClientWifi::sendACK(){
    sendData(1.0);
  }
  void ClientWifi::sendMAC(){
    String mac=WiFi.macAddress();
    char MAC[mac.length()+1];
    mac.toCharArray(MAC, mac.length());
    client.write_P(MAC, mac.length());
  }
  bool ClientWifi::ReceiveRawData(){
    byte byteArray[sizeof(float)];
    if(client.available() >= sizeof(float)){
      client.readBytes(byteArray, sizeof(byteArray));
      memcpy(&rawdata, byteArray, sizeof(float));
      setID();
      SetData();
      sendACK();
      return true;
    }
    return false;
  }

  bool ClientWifi::ReceiveRequestedData(){
    for(unsigned i=0;i<3; i++){
      if(ReceiveRawData()){
        return true;
      }
      delay(100);
      esp_task_wdt_reset();
    }
    return false;
  }
  //code 1000-> (1->9 && -9->-1 request) code 100> negativ data
  bool ClientWifi::RequestData(int id){
    float raw=(float)id*CODE*(-1);
    sendData(raw);
    if(ReceiveRequestedData() && rawdata==1.0){
      if(ReceiveRequestedData()){
        return true;
      }
    }
    return false;
  }

  void ClientWifi::SetData(){
    data=rawdata-ID*DECODE;
    if(data>100.0 && data<=130.0){
      data=(data-100.0)*(-1.0);
    }
  }
  float ClientWifi::getData(){
    return data;
  }
  void ClientWifi::setID(){
    ID=(int)rawdata/DECODE;
  }
  int ClientWifi::getID(){
    return ID;
  }