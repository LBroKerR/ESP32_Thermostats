#pragma once
#ifndef CLOCK_H
#define CLOCK_H

#include <ESP32Time.h>

#define YEAR    2024
#define MONTH   9
#define DAY     18
#define UTC_MINUS_1 3600

class Clock{
    ESP32Time *rtc;
    unsigned hour;
    unsigned min;
    bool hour_Changed;
    bool min_Changed;

public:
    Clock():hour(0),min(0),hour_Changed(false),min_Changed(false), rtc(nullptr){}
    Clock(unsigned hour, unsigned min);
    ~Clock();

    void updateClock();

    bool gethour(unsigned*);
    bool getmin(unsigned*);


};
#endif //CLOCK_H