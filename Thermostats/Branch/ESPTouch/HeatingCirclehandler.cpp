#include "HeatingCircleHandler.h"

HeatingCircleHandler::HeatingCircleHandler(){
    measuring=nullptr; //only one will be implement
    devices=nullptr; // as many as connected to server via wifi
    switch_changed=false;
    step=0.2;

}
HeatingCircleHandler::HeatingCircleHandler(float Step){
    measuring=nullptr; //only one will be implement
    devices=nullptr; // as many as connected to server via wifi
    switch_changed=false;
    step=Step;
}
HeatingCircleHandler::~HeatingCircleHandler(){
    if(devices!=nullptr){
        delete devices;
    }
    if(measuring!=nullptr){
        delete measuring;
    }
}
//add new element to the end of the array
bool HeatingCircleHandler::addDevices(String const MACaddress, String const name, float temp  ,unsigned const id, String ip){
    if(devices==nullptr){
        devices=new DeviceComponents();
    }
    devices->add_Component(MACaddress,name,temp,id, ip);
    return true;
}
DeviceComponents* HeatingCircleHandler::getDevices(){
  return devices;
}
//create sensor object
bool HeatingCircleHandler::addSensor(float offset, unsigned id, String name){
    if(measuring!=nullptr){
        delete measuring;
    }
    measuring=new TemperatureMeasuring(offset,id,name);
    if(measuring!=nullptr){
        return true;
    }
    return false;
}

TemperatureMeasuring* HeatingCircleHandler::getSensor(){
  return measuring;
}
bool HeatingCircleHandler::get_switch_changed()const{
    return switch_changed;
}
void  HeatingCircleHandler::set_switch_changed(bool const param){
    switch_changed=param;
}
// make choise to heat or not in this heating circle, use the devices and the own sensor for it.
int HeatingCircleHandler::Heating(float wanted_temperature){
    float temp=0.0;
    unsigned size=0;
    if(getDevices()!=nullptr){
        if(getDevices()->getDevices()!=nullptr){
            for(unsigned i=0; i<getDevices()->getSize(); i++){
                temp+=getDevices()->getDevices()[i].getTemp();
                size++;
            }
        }
    }
    if(measuring!=nullptr){
        temp+=measuring->getMeasuredTemperature();
        size++;
    }
    if(size!=0){
        temp=temp/size;
        if(temp<=(wanted_temperature-step)){
            return 1;
        }
        else if(temp>=(wanted_temperature+step)){
            return 0;
        }
        return 2;
    }
    return 3;
}