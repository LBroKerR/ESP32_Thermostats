#pragma once
#ifndef MAINTASK_H
#define MAINTASK_H

#include <ESP32Time.h>
#include <DHT.h>
#include "DataHandler.h"
#include "ui.h"
#include <Arduino.h>

#define SIZE 24

class MainTask{
    unsigned number_of_screens;//only 4 screen declared
    unsigned activeScreen;
    unsigned sensor_location;

    void upgrade_Screen1(DataHandler*data);
    void upgrade_Screen2(DataHandler*data,lv_chart_series_t * ui_TmpChart_series_1);
    void upgrade_Screen3(DataHandler*data);
    void upgrade_Screen4(DataHandler*data);
public:
    MainTask(unsigned param): number_of_screens(param), sensor_location(0) {}
    void init_screens_datas(DataHandler*data,lv_chart_series_t * ui_TmpChart_series_1);
    void set_Active(unsigned param);
    unsigned get_Active()const;
    void Screen_Upgrading(DataHandler*data,lv_chart_series_t * ui_TmpChart_series_1);
    void setSensor_Location(DataHandler*data);
    unsigned getSensorLocation();
    void measuring(DataHandler*data, DHT*sensor,ESP32Time *rtc);
};
#endif //MAINTASK_H