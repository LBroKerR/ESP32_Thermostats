#include "ExternalDeviceHandler.h"
//default constructure
ExternalDeviceHandler::ExternalDeviceHandler(){
    MAC="Address";
    nickName="Room name";
    HeatingCircleID=0;
    MeasuredTemperature=0.0;
    tempChanged=false;
}
// destructure
ExternalDeviceHandler::~ExternalDeviceHandler(){
}


//setter func
void ExternalDeviceHandler::setTemp(float const temp){
    MeasuredTemperature=temp;
}
void ExternalDeviceHandler::set_tempChanged(bool const param){
    tempChanged=param;
}
void ExternalDeviceHandler::set_ID(unsigned param){
    ID=param;
}

//getter funcs
String ExternalDeviceHandler::getMAC_address()const{
    return MAC;
}
String ExternalDeviceHandler::getNickName()const{
    return nickName;
}
unsigned ExternalDeviceHandler::getHeatingCircleID()const{
    return HeatingCircleID;
}
float ExternalDeviceHandler::getMeasuredTemperature()const{
    return MeasuredTemperature;
}
bool ExternalDeviceHandler::get_tempChanged()const{
    return tempChanged;
}
unsigned ExternalDeviceHandler::get_ID(){
    return ID;
}