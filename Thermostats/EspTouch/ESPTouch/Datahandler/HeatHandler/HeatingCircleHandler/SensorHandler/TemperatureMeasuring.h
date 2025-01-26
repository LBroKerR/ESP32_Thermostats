#pragma once
#ifndef TEMPERATUREmEASURING_H
#define TEMPERATUREmEASURING_H

#include <Arduino.h>

#include "float_mutex.h"
#include "uint_mutex.h"

class TemperatureMeasuring{

    float SensorOffset;
    float_mutex MeasuredTemp;
    uint_mutex MeasureHmd;
    unsigned HeatingCircleID;
    String nickName;
    bool tempChanged;
    bool hmdchanged;

public:
    TemperatureMeasuring();

    TemperatureMeasuring(float offset, unsigned id, String name);
    ~TemperatureMeasuring();

    bool measuring(float, unsigned);
    void set_tempChange(bool const);
    void set_hmdchange(bool const);

    String getNickName()const;
    unsigned getHeatingCircleID()const;
    bool getMeasuredTemperature(float*);
    bool getMeasureHmd(unsigned*);
    bool get_tempChange()const;
    bool get_hmdchange()const;


};
#endif //TEMPERATUREmEASURING_H