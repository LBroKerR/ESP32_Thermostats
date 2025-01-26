#include "ServerWifi.h"

//private:
void ServerWifi::setData(){
    data=rawdata-ID*DECODE;
    if(data>100.0 && data<=130.0){
      data=(data-100.0)*(-1.0);
    }
}
void ServerWifi::setID(){
   ID=(int)rawdata/DECODE;
}
void ServerWifi::setMAC(String param){
  Client_MAC_ADDRESS=param;
}

void ServerWifi::SendACK(){
  SendData(0,1.0);
}
// if one removed return true-> while not returning false check client!
bool ServerWifi::remove_lost_client(){
  WiFiClient *tmp;
  unsigned index=-1;
  for(unsigned i=0; i<number_of_client; i++){
    if(!clients[i].connected()){
      index=i;
    }
  }
  if(index!=-1){
    WiFiClient *tmp=new  WiFiClient[number_of_client-1];
    for(unsigned i=0; i<number_of_client-1; i++){
      if(index>i){
        tmp[i]=clients[i];
      }
      else{
        tmp[i]=clients[i+1];
      }
    }
    delete[] clients;
    clients=tmp;
    number_of_client--;
    return true;
  }
  return false;
}
bool ServerWifi::add_client(WiFiClient newClient){
  for(unsigned i=0; i<number_of_client; i++){
    if(clients[i]==newClient){
      return false;
    }
  }
  WiFiClient* newClientsArray = new WiFiClient[number_of_client + 1];
  if(clients!=nullptr && number_of_client!=0){
    for(unsigned i=0; i<number_of_client; i++){
      newClientsArray[i]=clients[i];
    }
    delete[] clients;
  }
  newClientsArray[number_of_client]=newClient;
  number_of_client++;
  return true;
}

//public

ServerWifi::ServerWifi(){
  HOST=0;
  clients=nullptr;
  number_of_client=0;
  rawdata=0.0;
  data=0.0;
  ID=0.0;
  Client_MAC_ADDRESS="";

}
ServerWifi::ServerWifi(String username, String pw, unsigned host){
  username.toCharArray(SSID, U_P_SIZE);
  pw.toCharArray(pass, U_P_SIZE);
  HOST=host;
  clients=nullptr;
  number_of_client=0;
  rawdata=0.0;
  data=0.0;
  ID=0.0;
  Client_MAC_ADDRESS="";
}
ServerWifi::~ServerWifi(){
  if(clients!=nullptr){
    for(unsigned i=0; i< number_of_client; i++){
      clients[i].stop();
    }
    delete[] clients;
  }
}

float ServerWifi::getData(){
  return data;
}
int ServerWifi::getID(){
  return ID;
}
String ServerWifi::getMAC(unsigned index){
  return Client_MAC_ADDRESS;
}

bool ServerWifi::ReceiveRawData(){
  for(unsigned i=0; i<number_of_client; i++){
    if(clients[i].available() >= sizeof(float)){
      Current_Client=i;
      break;
    }
  }
  if(clients[Current_Client].connected() && clients[Current_Client].available() >= sizeof(float)){
    // Read byte array from client
    byte byteArray[sizeof(float)];
    clients[Current_Client].readBytes(byteArray, sizeof(byteArray));
    SendACK();
    memcpy(&rawdata, byteArray, sizeof(float));
    setID();
    setData();
    return true;
  }
  return false;
}
bool ServerWifi::RequestData(){//MAC address only!
  String mac;
  SendData(MAC_ID,0.0);
  for(unsigned i=0; i<3; i++){
    delay(1000);
    if(clients[Current_Client].connected() && clients[Current_Client].available() >= sizeof(String)){
      byte byteArray[sizeof(String)];
      clients[Current_Client].readBytes(byteArray, sizeof(byteArray));
      SendACK();
      memcpy(&mac, byteArray, sizeof(String));
      setMAC(mac);
      return true;
    }
  }
  return false;
}
void ServerWifi::SendData(unsigned id, float param){
  //send to every nodes!
  param+=id*CODE;
  // Convert float to byte array
  byte byteArray[sizeof(float)];
  memcpy(byteArray, &param, sizeof(float));
  // Send byte array
  clients[Current_Client].write(byteArray, sizeof(byteArray));
}

void ServerWifi::Device_try_to_Connect(){
  WiFiClient newClient = server.available();
  if (newClient){
    add_client(newClient);
  }
}
void ServerWifi::Check_active_clients(){
  while(!remove_lost_client());
}