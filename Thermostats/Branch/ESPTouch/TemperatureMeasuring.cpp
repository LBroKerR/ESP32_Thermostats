#include "TemperatureMeasuring.h"

TemperatureMeasuring::TemperatureMeasuring(){
SensorOffset=0.0;
HeatingCircleID=0;
nickName="Room";
tempChanged.set_variable(false);
hmdchanged.set_variable(false);
MeasureHmd.set_variable(0);

}
TemperatureMeasuring::TemperatureMeasuring(float offset, unsigned id, String name){
SensorOffset=offset;
HeatingCircleID=id;
nickName=name;
tempChanged.set_variable(false);
hmdchanged.set_variable(false);
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
            tempChanged.set_variable(true);
        }
        MeasureHmd.get_variable(&hmd_tmp);
        if(hmd!=hmd_tmp){
            MeasureHmd.set_variable(hmd);
            hmdchanged.set_variable(true);
        }
        return true;
    }
    return false;
}
void TemperatureMeasuring::set_tempChange(bool const param){
    tempChanged.set_variable(param);
}
void TemperatureMeasuring::set_hmdchange(bool const param){
    hmdchanged.set_variable(param);
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
bool TemperatureMeasuring::get_tempChange(bool* param){
    return tempChanged.get_variable(param);
}
bool TemperatureMeasuring::get_hmdchange(bool* param){
    return hmdchanged.get_variable(param);
}
