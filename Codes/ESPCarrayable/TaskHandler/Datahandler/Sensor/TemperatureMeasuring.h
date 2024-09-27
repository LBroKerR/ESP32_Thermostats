#pragma once
#ifndef TEMPERATUREmEASURING_H
#define TEMPERATUREmEASURING_H

#include "defines.h"

class TemperatureMeasuring{

    float SensorOffset;
    float MeasuredTemp;
    unsigned MeasureHmd;
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
    float getMeasuredTemperature()const;
    unsigned getMeasureHmd()const;
    bool get_tempChange()const;
    bool get_hmdchange()const;


};
#endif //TEMPERATUREmEASURING_H