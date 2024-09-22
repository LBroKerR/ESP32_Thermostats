#pragma once
#ifndef DATAHANDLER_H
#define DATAHANDLER_H

//Carryable
#include "ClientWifi.h"
#include "TemperatureMeasuring.h"
#include "programs.h"
#include "Clock.h"

class DataHandler{
    ClientWifi *wifi;
    TemperatureMeasuring *measuring;
    Clock*clock;
    programs *prog;

public:
    DataHandler();
    ~DataHandler();

    void setWifi(String ip, String username, String pw, unsigned host, bool);
    void setSensor(float offset, unsigned id, String name);
    void setTime(unsigned hour, unsigned min);

    ClientWifi* getWifi();
    TemperatureMeasuring* getSensor();
    Clock*getTime();
    programs *getProg();

};
#endif //DATAHANDLER_H