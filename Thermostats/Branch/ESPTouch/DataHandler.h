#pragma once
#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "Clock.h"
#include "HeatHandler.h"
#include "programs.h"
#include "wifi_data.h"


class DataHandler{

    Clock* time;
    HeatHandler* heater;
    programs *prog;
    wifi_data* wifi;
    bool ProgSave;

public:
    DataHandler();
    ~DataHandler();

    void set_wifi(String ssid, String pass, unsigned host, bool);
    wifi_data* get_wifi_data();
    void setTime(unsigned hour, unsigned min);
    Clock* getTime();
    HeatHandler* getHeater();
    programs* getProg();
    void setProgSave(bool);
    bool getProgSave()const;
};
#endif //DATAHANDLER_H