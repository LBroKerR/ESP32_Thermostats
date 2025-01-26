#pragma once
#ifndef EXTERNALDEVICEHANDLER_H
#define EXTERNALDEVICEHANDLER_H

//will be a storeg class which is storing espcarryable external device datas
#include <Arduino.h>

class ExternalDeviceHandler{
    String MAC;
    String nickName;
    unsigned HeatingCircleID;
    float MeasuredTemperature;
    bool tempChanged;
    unsigned ID;

public:

    ExternalDeviceHandler();

    ExternalDeviceHandler(String const MACaddress, String const name, unsigned const Heatingid,unsigned const id ): 
    MAC(MACaddress), nickName(name), HeatingCircleID(Heatingid),MeasuredTemperature(0.0),tempChanged(false), ID(id) {}

    ~ExternalDeviceHandler();

    void setTemp(float const temp);
    void set_tempChanged(bool const param);
    void set_ID(unsigned);

    String getMAC_address()const;
    String getNickName()const;
    unsigned getHeatingCircleID()const;
    float getMeasuredTemperature()const;
    bool get_tempChanged()const;
    unsigned get_ID();

};
#endif //EXTERNALDEVICEHANDLER_H