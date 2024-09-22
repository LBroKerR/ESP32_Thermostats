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
void DataHandler::setSensor(float offset, unsigned id, String name){
    measuring=new TemperatureMeasuring(offset, id, name );
}
void DataHandler::setTime(unsigned hour, unsigned min){
    clock=new Clock(hour, min);
}

ClientWifi* DataHandler::getWifi(){
    return wifi;
}
TemperatureMeasuring* DataHandler::getSensor(){
    return measuring;
}
Clock*DataHandler::getTime(){
    return clock;
}
programs* DataHandler::getProg(){
    return prog;
}