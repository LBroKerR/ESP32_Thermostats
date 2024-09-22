#pragma once
#ifndef HEATINGCIRCLEHANDLER_H
#define HEATINGCIRCLEHANDLER_H

#include "ExternalDeviceHandler.h"
#include "TemperatureMeasuring.h"


class HeatingCircleHandler{

    TemperatureMeasuring* measuring; //only one will be implement
    ExternalDeviceHandler* devices; // as many as connected to server via wifi
    unsigned number_of_devices;
    float step;

public:

    HeatingCircleHandler();
    HeatingCircleHandler(float Step);
    ~HeatingCircleHandler();

    bool addDevice(String const MACaddress, String const name, unsigned const Heatingid,unsigned const id);
    bool removeDevice(unsigned const id);

    bool addSensor(float offset, unsigned id, String name);

    bool Heating(float);

};
#endif //HEATINGCIRCLEHANDLER_H