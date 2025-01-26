#include "TemperatureMeasuring.h"

TemperatureMeasuring::~TemperatureMeasuring(){
    sensor->end();
    delay(10);
    delete sensor;
}

//setter
bool TemperatureMeasuring::measuring(){
    float tmp1, tmp2;
    tmp1=sensor->readreadTemperature();
    tmp2=sensor->readHumidity();
    if(!isnan(tmp1) && !isnan(tmp2)){
        if(tmp1!=MeasuredTemp ){
            MeasuredTemp=tmp1;
            tempChanged=true;
        }
        if(tmp2!=MeasureHmd){
            MeasureHmd=tmp2;
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
