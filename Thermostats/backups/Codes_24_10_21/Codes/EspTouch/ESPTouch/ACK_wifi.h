#pragma once
#ifndef ACK_WIFI_H
#define ACK_WIFI_H

#include "Arduino.h"


class ACK_wifi{
private:
    String device_MAC;
    unsigned heating_circle;
    int data_id;
    float Fdata;
    String Sdata;
    bool ack, data;

    //private setters
    void set_Fdata(float const);
    void set_Sdata(String const);

    //private getters
    float get_Fdata();
    String get_Sdata();

public:
    //
    ACK_wifi();

    //setters
    void set_device_MAC(String const);
    void set_heating_circle(unsigned const);
    void set_data_id(int const);
    void set_data(void* param, bool Data);
    void set_ack(bool const);

    //getters
    String get_device_MAC() const;
    unsigned get_heating_circle()const;
    int get_data_id()const;
    bool get_data(void*);
    bool get_ack()const;

};
#endif // ACK_WIFI_H