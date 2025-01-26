#include "ClientWifi.h"

//private:

bool ClientWifi::ConnectToWiFi(){
  if(WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println("Connecting to WiFi...");
    return false;
  }
  Serial.println("Connected to WiFi");
  return true;
}
bool ClientWifi::ConncetToServer(){
  while(client.connect(Ip, Host)){
    delay(1000);
    Serial.println("Connection to server failed");
  }
  Serial.println("Connected to server");
  //timeoutTime = millis() + 15000;
  return true;
}
bool ClientWifi::connection_check(){
  /*if(timeoutTime < millis()){
    client.stop();
    ConncetToServer();
  }*/
  if(!client.connected()){
    client.stop();
    ConncetToServer();
    return true;
  }
  return false;
  /*else if(ReceiveRawData() && getRawData()==1.0){
    setRawDAta(0.0);
    sendData(1.0);
    timeoutTime = millis() + 15000;
  }*/
}

//public:
  ClientWifi::ClientWifi(){
  timeoutTime=0;
  Host=0;
  rawdata=0.0;
  data=0.0;
  Id=0;
  initDone=false;
  }
  ClientWifi::ClientWifi(String ip, String username, String pw, unsigned host, bool enable ){
    Serial.begin(115200);
    ip.toCharArray(Ip, IPSIZE);
    username.toCharArray(SSID, UPSIZE);
    pw.toCharArray(pass, UPSIZE);
    Host=(uint16_t)host;
    Switch=enable;
    rawdata=0.0;
    data=0.0;
    Id=0;
    timeoutTime=0;
    initDone=false;
    if(Switch){
      WiFi.begin(SSID, pass);
      while(!ConnectToWiFi());
      ConncetToServer();
    }
  }
  ClientWifi::~ClientWifi(){
    client.stop();
    Serial.end();
  }

  void ClientWifi::IsconnectedToWifi(){
    if(!WiFi.isConnected()){
      while(!ConnectToWiFi());
    }
  }

  void ClientWifi::sendData(float data){

      byte byteArray[sizeof(float)];
      memcpy(byteArray, &data, sizeof(float));
    // Send byte array
      client.write(byteArray, sizeof(byteArray));
  }
  void ClientWifi::sendACK(){
    float ack=((heatingid*100)+deviceid)*100000+1.0;
    sendData(ack);
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
  String ClientWifi::getMAC(){
    return WiFi.macAddress();
  }
  void ClientWifi::sendString(String str){
    if(client.connected()){
      client.println(str+"\n");
    }
  }
  bool  ClientWifi::receiveString(String*str){
    if(client.connected() && client.available()){
      *str=client.readStringUntil('\n');
      return true;
    }
    return false;
  }
  bool ClientWifi::ReceiveRawData(){
    byte byteArray[sizeof(float)];
    if(client.available() >= sizeof(float)){
      client.readBytes(byteArray, sizeof(byteArray));
      memcpy(&rawdata, byteArray, sizeof(float));
      set_heating_id();
      set_device_id();
      setID();
      SetData();
      sendACK();
      Serial.println(rawdata);
      return true;
    }
    return false;
  }
    float ClientWifi::getRawData(){
    return rawdata;
  }
    void  ClientWifi::setRawDAta(float param){
      rawdata=param;
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
    float raw=rawdata;
    if(rawdata<0){
      raw=raw*(-1);
    }
    float tmp1=raw/1000;
    int tmp2=raw/10000;
    tmp2*=10;
    tmp1=tmp1-(float)tmp2;
    if(tmp1>1.0){
      tmp1=tmp1-1;
      tmp1=tmp1*(-1);
    }
    data=tmp1*1000;
  }
  float ClientWifi::getData(){
    return data;
  }
  void ClientWifi::setID(){
    Id=(rawdata/10000)-(((heatingid*100)+(deviceid))*10);
  }
  int ClientWifi::getID(){
    return Id;
  }

  void ClientWifi::set_device_id(){
    deviceid=(rawdata/100000)-(heatingid*100);
  }
  void ClientWifi::set_heating_id(){
    heatingid=rawdata/10000000;
  }

  bool ClientWifi::getSwitch(){
    return Switch;
  }

  int ClientWifi::get_device_id(){
    return deviceid;
  }
  int ClientWifi::get_heating_id(){
    return heatingid;
  }
  void ClientWifi::setInitDone(bool const param){
    initDone=param;
  }
  bool ClientWifi::getInitDone(){
    return initDone;
  }
