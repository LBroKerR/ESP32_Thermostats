#include "MeasuringTask.h"

//private:

void MeasuringTask::DHT_sensor(dht* sensor){
    float temp=0.0;
    float hmd=0.0;
    if(sensor!=nullptr && data->getHeater()->getHeatingCircleHandler()[location].getSensor()!=nullptr){
      //temp=sensor->readTemperature();
      //hmd=sensor->readHumidity();
      chk=sensor->read21(DHTPIN);
      delay(500);
      if(chk==OK){
      temp=sensor->temperature;
      hmd=sensor->humidity;
      temperature[measrued_index]=temp;
      measrued_index++;
      temp=0.0;
      for(unsigned i=0; i<MEASURING_NUMBER; i++){
        temp+=temperature[i];
      }
      temp=temp/MEASURING_NUMBER;
      data->getHeater()->getHeatingCircleHandler()[location].getSensor()->measuring(temp,(unsigned)hmd);//??
      }
    }
    if(measrued_index>=MEASURING_NUMBER){
        measrued_index=0;
        check_heater=true;
    }
}
void MeasuringTask::rtc_timer(ESP32Time *rtc){
    unsigned hour=0, min=0;
    if(rtc!=nullptr){
        hour=rtc->getHour(true);
        min=rtc->getMinute();
        data->getTime()->setClock(hour, min);
    }
}

//public:

MeasuringTask::MeasuringTask(DataHandler* obj){
    data=obj;
    chk=0;
    measrued_index=0;
    check_heater=false;
    for(unsigned i=0; i<MEASURING_NUMBER; i++){
        temperature[i]=0.0;
    }
    if(data!=nullptr){
        location=-1;
        for(unsigned i=0; i<data->getHeater()->get_number_of_HeatingCircles(); i++){
            if(data->getHeater()->getHeatingCircleHandler()[i].getSensor()!=nullptr){
                location=i;
            }
        }
    }
}
 bool MeasuringTask::get_sensor_ready(){
    return check_heater;
 }
void MeasuringTask::measurning(dht* sensor,ESP32Time *rtc){
    if(location!=-1 && location<data->getHeater()->get_number_of_HeatingCircles()){
        DHT_sensor(&sensor1);
    }
    rtc_timer(rtc);
}