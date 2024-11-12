#pragma once
#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "TemperatureMeasuring.h"
#include "programs.h"
#include "Clock.h"
#include "wifi_data.h"

class DataHandler{
    TemperatureMeasuring *measuring;
    Clock*clock;
    programs *prog;
    wifi_data* wifi;
    bool Switch;

public:
    DataHandler();
    ~DataHandler();

    void setWifi(String ip, String ssid, String pass, unsigned host, bool Switch);
    wifi_data* get_wifi_data();

    void setSensor(float offset, unsigned id,unsigned heatingid, String name);
    TemperatureMeasuring* getSensor();
    void setTime(unsigned hour, unsigned min);
    Clock*getTime();
    programs *getProg();
    void setSwitch(bool);
    bool getSwitch();

};
#endif //DATAHANDLER_H