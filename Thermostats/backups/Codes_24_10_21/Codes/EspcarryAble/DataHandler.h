#pragma once
#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "ClientWifi.h"
#include "TemperatureMeasuring.h"
#include "programs.h"
#include "Clock.h"

class DataHandler{
    ClientWifi *wifi;
    TemperatureMeasuring *measuring;
    Clock*clock;
    programs *prog;
    bool Switch;

public:
    DataHandler();
    ~DataHandler();

    void setWifi(String ip, String username, String pw, unsigned host, bool);
    ClientWifi* getWifi();
    void setSensor(float offset, unsigned id,unsigned heatingid, String name);
    TemperatureMeasuring* getSensor();
    void setTime(unsigned hour, unsigned min);
    Clock*getTime();
    programs *getProg();
    void setSwitch(bool);
    bool getSwitch();

};
#endif //DATAHANDLER_H