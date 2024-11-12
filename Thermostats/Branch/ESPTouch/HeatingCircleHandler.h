#pragma once
#ifndef HEATINGCIRCLEHANDLER_H
#define HEATINGCIRCLEHANDLER_H

#include "TemperatureMeasuring.h"
#include "DeviceComponents.h"
#include <Arduino.h>


class HeatingCircleHandler{

    TemperatureMeasuring* measuring; //only one will be implement
    DeviceComponents* devices; //one needed
    float step;
    bool switch_changed;

public:

    HeatingCircleHandler();
    HeatingCircleHandler(float Step);
    ~HeatingCircleHandler();

    bool addDevices(String const Mac, String const name, float const temp, unsigned const ID, String ip );
    bool addSensor(float offset, unsigned id, String name);
    bool removeDevice(String ip);
    DeviceComponents* getDevices();
    TemperatureMeasuring* getSensor();

    bool get_switch_changed()const;
    void set_switch_changed(bool const param);
    int Heating(float);

};
#endif //HEATINGCIRCLEHANDLER_H