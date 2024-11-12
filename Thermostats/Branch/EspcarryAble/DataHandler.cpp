#include "DataHandler.h"

DataHandler::DataHandler(){
    measuring=nullptr;
    clock=nullptr;
    wifi=nullptr;
    Switch=false;
    prog=new programs();
}
DataHandler::~DataHandler(){
    delete measuring;
    delete clock;
    delete prog;
    delete wifi;
}

void DataHandler::setWifi(String ip, String ssid, String pass, unsigned host, bool Switch){
    wifi=new wifi_data();
    wifi->setWifi_datas( ip,ssid,pass,host,Switch);
}
wifi_data* DataHandler::get_wifi_data(){
    return wifi;
}

void DataHandler::setSensor(float offset, unsigned id,unsigned heatingid, String name){
    measuring=new TemperatureMeasuring(offset, id, heatingid,name );
}
TemperatureMeasuring* DataHandler::getSensor(){
    return measuring;
}
void DataHandler::setTime(unsigned hour, unsigned min){
    clock=new Clock(hour, min);
}

Clock*DataHandler::getTime(){
    return clock;
}
programs* DataHandler::getProg(){
    return prog;
}
void DataHandler::setSwitch(bool param){
    Switch=param;
}
bool DataHandler::getSwitch(){
    return Switch;
}