#pragma once
#ifndef CLOCK_H
#define CLOCK_H

#include "uint_mutex.h"
#include "bool_mutex.h"


#define YEAR    2024
#define MONTH   9
#define DAY     18
#define UTC_MINUS_1 3600

class Clock{
    uint_mutex hour;
    uint_mutex min;
    bool_mutex hour_Changed;
    bool_mutex min_Changed;

public:
    Clock();
    Clock(unsigned h, unsigned m);
    ~Clock();

    void setClock(unsigned Hour, unsigned Min);
    void set_hour_Changed(bool);
    void set_min_Changed(bool);

    bool gethour(unsigned*);
    bool getmin(unsigned*);
    bool get_hour_Changed();
    bool get_min_Changed();

    //bool getmin(unsigned*print);
    //bool gethour(unsigned* print);


};
#endif //CLOCK_H