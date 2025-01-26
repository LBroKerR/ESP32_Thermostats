#include "TemperatureMeasuring.h"

TemperatureMeasuring::TemperatureMeasuring(){
SensorOffset=0.0;
HeatingCircleID=0;
nickName="Room";
tempChanged=false;
MeasureHmd=0;

}
TemperatureMeasuring::TemperatureMeasuring(float offset, unsigned id, String name){
SensorOffset=offset;
HeatingCircleID=id;
nickName=name;
tempChanged=false;
MeasureHmd=0;
MeasuredTemp=offset;
}

TemperatureMeasuring::~TemperatureMeasuring(){
    //delete sensor;
}

//setter
bool TemperatureMeasuring::measuring(float temp, unsigned hmd){
    if(!isnan(temp) && !isnan(hmd)){
        if(temp!=MeasuredTemp ){
            MeasuredTemp=temp+SensorOffset;
            tempChanged=true;
        }
        if(hmd!=MeasureHmd){
            MeasureHmd=hmd;
            hmdchanged=true;
        }
        return true;
    }
    return false;
}
void TemperatureMeasuring::set_tempChange(bool const param){
    tempChanged=param;
}
void TemperatureMeasuring::set_hmdchange(bool const param){
    hmdchanged=param;
}

//getter
String TemperatureMeasuring::getNickName()const{
    return nickName;
}
unsigned TemperatureMeasuring::getHeatingCircleID()const{
    return HeatingCircleID;
}
float TemperatureMeasuring::getMeasuredTemperature()const{
    return MeasuredTemp;
}
unsigned TemperatureMeasuring::getMeasureHmd()const{
    return MeasureHmd;
}
bool TemperatureMeasuring::get_tempChange()const{
    return tempChanged;
}
bool TemperatureMeasuring::get_hmdchange()const{
    return hmdchanged;
}
