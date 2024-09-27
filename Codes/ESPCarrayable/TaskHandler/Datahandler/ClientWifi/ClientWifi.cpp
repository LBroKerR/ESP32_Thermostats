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
  if (client.connect(Ip, Host)) {
    return true;//Serial.println("Connected to server");
  } 
  //Serial.println("Connection to server failed");
  return false;
}

//public:
  ClientWifi::ClientWifi(){
  Host=0;
  rawdata=0.0;
  data=0.0;
  Id=0;
  initDone=false;
  }
  ClientWifi::ClientWifi(String ip, String username, String pw, unsigned host, bool enable ){
    ip.toCharArray(Ip, IPSIZE);
    username.toCharArray(SSID, UPSIZE);
    pw.toCharArray(pass, UPSIZE);
    Host=host;
    Switch=enable;
    rawdata=0.0;
    data=0.0;
    Id=0;
    initDone=false;
    if(Switch){
      WiFi.begin(SSID, pass);
      while(!ConnectToWiFi());
    }
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
  bool ClientWifi::ReceiveACK()
  {
    byte byteArray[sizeof(float)];
    float ack=0.0;
    for(int i=0; i<10000; i++){
      if(client.available() >= sizeof(float)){
        memcpy(&ack, byteArray, sizeof(float));
        if(ack==1.0){
          return true;
        }
      }
    }
    return false;
  }
  void ClientWifi::sendMAC(){
    String mac=WiFi.macAddress();
    sendString("mac "+mac);
  }
  void ClientWifi::sendString(String str){
    char data[str.length()+1];
    str.toCharArray(data, str.length()+1);
    client.write_P(data, str.length()+1);
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
    data=rawdata-Id*DECODE;
    if(data>100.0 && data<=130.0){
      data=(data-100.0)*(-1.0);
    }
  }
  float ClientWifi::getData(){
    return data;
  }
  void ClientWifi::setID(){
    Id=(int)rawdata/DECODE;
  }
  int ClientWifi::getID(){
    return Id;
  }
  bool ClientWifi::getSwitch(){
    return Switch;
  }
  void ClientWifi::setInitDone(bool const param){
    initDone=param;
  }
  bool ClientWifi::getInitDone(){
    return initDone;
  }