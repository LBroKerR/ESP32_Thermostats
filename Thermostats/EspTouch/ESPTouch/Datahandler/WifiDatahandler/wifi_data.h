#pragma once
#ifndef WIFI_DATA_H
#define WIFI_DATA_H

#include <Arduino.h>

class wifi_data{
    String ssid;
    String pass;
    unsigned host;
    bool Switch;
    String ip;

public:
    wifi_data(/* args */);
    void setWifi_datas(String ssid, String pass, unsigned host, bool Switch);
    String get_ssid()const;
    String get_pass()const;
    unsigned get_host()const;
    bool get_switch()const;
    void set_ip(String);
    String get_ip();
};



#endif