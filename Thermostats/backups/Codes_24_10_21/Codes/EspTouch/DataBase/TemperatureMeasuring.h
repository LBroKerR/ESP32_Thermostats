#pragma once
#ifndef TEMPERATUREmEASURING_H
#define TEMPERATUREmEASURING_H

#include<Arduino.h>
#include<DHT.h>

#define DHTTYPE DHT21
#define DHTPIN  25

class TemperatureMeasuring{

    DHT *sensor;
    float SensorOffset;
    float MeasuredTemp;
    unsigned MeasureHmd;
    unsigned HeatingCircleID;
    String nickName;
    bool tempChanged;
    bool hmdchanged;

public:
    TemperatureMeasuring(): SensorOffset(0.0),MeasuredTemp(0.0), sensor(nullptr), HeatingCircleID(0),nickName("Room name"),tempChanged(false),MeasureHmd(0) {}

    TemperatureMeasuring(float offset, unsigned id, String name): SensorOffset(offset), HeatingCircleID(id), nickName(name), tempChanged(false),MeasureHmd(0) 
                                                                {sensor=new DHT(DHTPIN,DHTTYPE); sensor->begin(); delay(5);}
    ~TemperatureMeasuring();

    bool measuring();
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