#include "DataHandler.h"

DataHandler::DataHandler(){
    time=nullptr;
    heater=new HeatHandler();
    prog=new programs();
    wifi=nullptr;
    ProgSave=false;
}
DataHandler::~DataHandler(){
    delete time;
    delete heater;
    delete prog;
    delete wifi;
}

void DataHandler::set_wifi(String ssid, String pass, unsigned host, bool Switch){
    wifi=new wifi_data();
    wifi->setWifi_datas(ssid, pass, host, Switch );
}
wifi_data* DataHandler::get_wifi_data(){
    return wifi;
}
    
void DataHandler::setTime(unsigned hour, unsigned min){
    time=new Clock(hour,min);
}

Clock* DataHandler::getTime(){
    return time;
}
HeatHandler* DataHandler::getHeater(){
    return heater;
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

