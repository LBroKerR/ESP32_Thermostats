#pragma once
#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "Clock.h"
#include "HeatHandler.h"
#include "ServerWifi.h"
#include "programs.h"


class DataHandler{

    Clock* time;
    HeatHandler* heater;
    ServerWifi* wifi;
    programs *prog;
    bool ProgSave;

public:
    DataHandler();
    ~DataHandler();

    void setTime(unsigned hour, unsigned min);
    void setServer(String username, String pw, unsigned host);

    Clock* getTime();
    HeatHandler* getHeater();
    ServerWifi* getWifi();
    programs* getProg();
    void setProgSave(bool);
    bool getProgSave()const;
};
#endif //DATAHANDLER_H