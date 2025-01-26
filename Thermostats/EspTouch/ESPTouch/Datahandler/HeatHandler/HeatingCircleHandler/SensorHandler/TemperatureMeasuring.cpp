#include "TemperatureMeasuring.h"

TemperatureMeasuring::TemperatureMeasuring(){
SensorOffset=0.0;
HeatingCircleID=0;
nickName="Room";
tempChanged=false;
MeasureHmd.set_variable(0);

}
TemperatureMeasuring::TemperatureMeasuring(float offset, unsigned id, String name){
SensorOffset=offset;
HeatingCircleID=id;
nickName=name;
tempChanged=false;
MeasureHmd.set_variable(0);
MeasuredTemp.set_variable(offset);
}

TemperatureMeasuring::~TemperatureMeasuring(){
    //delete sensor;
}

//setter
bool TemperatureMeasuring::measuring(float temp, unsigned hmd){
    float temp_tmp=0.0;
    unsigned hmd_tmp=0;
    if(!isnan(temp) && !isnan(hmd)){
        MeasuredTemp.get_variable(&temp_tmp);
        if(temp!=temp_tmp){
            MeasuredTemp.set_variable(temp+SensorOffset);
            tempChanged=true;
        }
        MeasureHmd.get_variable(&hmd_tmp);
        if(hmd!=hmd_tmp){
            MeasureHmd.set_variable(hmd);
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
bool TemperatureMeasuring::getMeasuredTemperature(float* param){
    if(MeasuredTemp.get_variable(param)){
        return true;
    }
    return false;
}
bool TemperatureMeasuring::getMeasureHmd(unsigned * param){
        if(MeasureHmd.get_variable(param)){
        return true;
    }
    return false;
}
bool TemperatureMeasuring::get_tempChange()const{
    return tempChanged;
}
bool TemperatureMeasuring::get_hmdchange()const{
    return hmdchanged;
}
