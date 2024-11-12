#pragma once
#ifndef WIFI_DATA_H
#define WIFI_DATA_H

#include <Arduino.h>

class wifi_data{
    String ip;
    String ssid;
    String pass;
    unsigned host;
    bool Switch;

public:
    wifi_data(/* args */);
    void setWifi_datas(String ip, String ssid, String pass, unsigned host, bool Switch);
    String get_ip()const;
    String get_ssid()const;
    String get_pass()const;
    unsigned get_host()const;
    bool get_switch()const;
};



#endif