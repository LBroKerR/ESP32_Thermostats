#include "MeasuringTask.h"

//private:

void MeasuringTask::DHT_sensor(DHT*sensor){
    if(sensor!=nullptr && data->getHeater()->getHeatingCircleHandler()[location].getSensor()!=nullptr){
        data->getHeater()->getHeatingCircleHandler()[location].getSensor()->measuring(sensor->readTemperature(),(unsigned)sensor->readHumidity());
    }
}
void MeasuringTask::rtc_timer(ESP32Time *rtc){
    if(rtc!=nullptr){
        data->getTime()->setClock(rtc->getHour(true), rtc->getMinute());
    }
}

//public:

MeasuringTask::MeasuringTask(DataHandler* obj){
    data=obj;
    if(data!=nullptr){
        location=-1;
        for(unsigned i=0; i<data->getHeater()->get_number_of_HeatingCircles(); i++){
            if(data->getHeater()->getHeatingCircleHandler()[i].getSensor()!=nullptr){
                location=i;
            }
        }
    }
}
void MeasuringTask::measurning(DHT*sensor,ESP32Time *rtc){
    if(location!=-1 && location<data->getHeater()->get_number_of_HeatingCircles()){
        DHT_sensor(sensor);
    }
    rtc_timer(rtc);
}