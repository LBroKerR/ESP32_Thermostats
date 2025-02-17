#pragma once
#ifndef MEASURINGTASK_H
#define MEASURINGTASK_H

#include <ESP32Time.h>
#include <DHT.h>

#include "DataHandler.h"

class MeasuringTask
{
    DataHandler* data;
    int location;

    void DHT_sensor(DHT*sensor);
    void rtc_timer(ESP32Time *rtc);

public:
    MeasuringTask(DataHandler*);
    void measurning(DHT*sensor,ESP32Time *rtc);

};



#endif //MEASURINGTASK_H