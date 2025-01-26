#include "DataHandler.h"

DataHandler::DataHandler(){
    time=nullptr;
    heater=new HeatHandler();
    wifi=nullptr;
    prog=new programs();
    ProgSave=false;
}
DataHandler::~DataHandler(){
    delete time;
    delete heater;
    delete wifi;
    delete prog;
}
    
void DataHandler::setTime(unsigned hour, unsigned min){
    time=new Clock(hour,min);
}
void DataHandler::setServer(String username, String pw, unsigned host){
    wifi=new ServerWifi(username,pw,host);
}

Clock* DataHandler::getTime(){
    return time;
}
HeatHandler* DataHandler::getHeater(){
    return heater;
}
ServerWifi* DataHandler::getWifi(){
    return wifi;
}
programs* DataHandler::getProg(){
    return prog;
}
void  DataHandler::setProgSave(bool param){
  ProgSave=param;
}
bool  DataHandler::getProgSave()const{
  return ProgSave;
}

