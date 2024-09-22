#include "DataHandler.h"

DataHandler::DataHandler(){
    wifi=nullptr;
    measuring=nullptr;
    clock=nullptr;
    prog=new programs();
}
DataHandler::~DataHandler(){
    delete wifi;
    delete measuring;
    delete clock;
    delete prog;
}
void DataHandler::setWifi(String ip, String username, String pw, unsigned host, bool Switch){
    wifi=new ClientWifi(ip,username,pw,host, Switch);
}
ClientWifi* DataHandler::getWifi(){
    return wifi;
}
void DataHandler::setSensor(float offset, unsigned id, String name){
    measuring=new TemperatureMeasuring(offset, id, name );
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