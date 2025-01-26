#pragma once
#ifndef MEASURINGTASK_H
#define MEASURINGTASK_H

#include <Arduino.h>

#include <ESP32Time.h>
//#include <DHT.h>
#include "esp_task_wdt.h"
#define DHTPIN 27
#define OK 0
#define MEASURING_NUMBER 10
#include "DataHandler.h"
#include "dht.h"

class MeasuringTask
{
    DataHandler* data;
    int location;
    dht sensor1;
    int chk;
    float temperature[MEASURING_NUMBER];
    unsigned measrued_index;

    bool check_heater;

    void DHT_sensor(dht*sensor);
    void rtc_timer(ESP32Time *rtc);

public:
    MeasuringTask(DataHandler*);
    void measurning(dht*sensor,ESP32Time *rtc);
    bool get_sensor_ready();

};



#endif //MEASURINGTASK_H