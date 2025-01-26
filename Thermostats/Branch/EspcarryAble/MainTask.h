#pragma once
#ifndef MAINTASK_H
#define MAINTASK_H

#include "defines.h"
#include "DataHandler.h"
#include <ESP32Time.h>

#define MEASURED_NUMBER 10

class MainTask{
    DataHandler* data;
    float temp[MEASURED_NUMBER];
    unsigned measrued_index;
public:
    MainTask();
    ~MainTask();

    void setData(DataHandler* param);
    void print(Adafruit_SSD1306 *display, ESP32Time *rtc);
    void measure(DHT*sensor);
    void buttonInteraction(Buttons*);
    bool SerialExit(Buttons* button,Adafruit_SSD1306 *display);
    void main(DataHandler* param,ESP32Time* rtc);


};
#endif //MAINTASK_H