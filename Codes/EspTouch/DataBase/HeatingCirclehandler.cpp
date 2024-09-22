#include "HeatingCircleHandler.h"

HeatingCircleHandler::HeatingCircleHandler(){
    measuring=nullptr; //only one will be implement
    devices=nullptr; // as many as connected to server via wifi
    unsigned number_of_devices=0;
    float step=0.5;

}
HeatingCircleHandler::~HeatingCircleHandler(){
    if(devices!=nullptr){
        delete[] devices;
    }
    if(measuring!=nullptr){
        delete measuring;
    }
}
//copy exist ones to a tmp array, then delete the old one. 
//add new element to the end of the array
//give new array to devices pointer
bool HeatingCircleHandler::addDevice(String const MACaddress, String const name,  unsigned const Heatingid,unsigned const id){
    ExternalDeviceHandler*tmp=nullptr;
    ExternalDeviceHandler next(MACaddress,name,Heatingid,id);
    if(devices==nullptr){
        number_of_devices=1;
        tmp=new ExternalDeviceHandler[number_of_devices];
    }
    else{
        number_of_devices++;
        tmp=new ExternalDeviceHandler[number_of_devices];
        for(unsigned i=0; i<number_of_devices-1; i++){
            tmp[i]=devices[i];
        }
        delete[] devices;
    }
    tmp[number_of_devices-1]=next;
    devices=tmp;
    return true;
}
//search existing device in the array. 
//create a new array, copy every devices to it, except the one which waiting to be deleted.
// delete old array, and point with it to the new one.
bool HeatingCircleHandler::removeDevice(unsigned const id){
    if(devices==nullptr){
        return false;
    }
    ExternalDeviceHandler*tmp=nullptr;
    int Foundindex=-1;
    for(unsigned i=0; i<number_of_devices; i++){
        if(devices[i].get_ID()==id){
            Foundindex=i;
            break;
        }
    }
    if(Foundindex>-1){
        tmp=new ExternalDeviceHandler[number_of_devices-1];
        for(unsigned i=0; i<number_of_devices-1; i++){
            if(i<Foundindex){
                tmp[i]=devices[i];
            }
            else{
                tmp[i]=devices[i+1];
            }
        }
        devices--;
        delete[] devices;
        devices=tmp;
        return true;
    }
    return false;
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

// make choise to heat or not in this heating circle, use the devices and the own sensor for it.
bool HeatingCircleHandler::Heating(float wanted_temperature){
    bool heatingSwitch=false;
    if(measuring==nullptr){
        return heatingSwitch;
    }
    if(measuring->getMeasuredTemperature()<=wanted_temperature-step){
        heatingSwitch=true;
    }
    if (devices!=nullptr)
    {
        for (unsigned i = 0; i < number_of_devices; i++)
        {
            if(devices[i].getMeasuredTemperature()<=wanted_temperature-step){
                heatingSwitch=true;
                break;
            }
        }
    }
    return heatingSwitch;
}