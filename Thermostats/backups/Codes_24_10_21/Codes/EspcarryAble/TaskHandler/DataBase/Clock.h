#pragma once
#ifndef CLOCK_H
#define CLOCK_H

#define YEAR    2024
#define MONTH   9
#define DAY     18
#define UTC_MINUS_1 3600

class Clock{
    unsigned hour;
    unsigned min;
    bool hour_Changed;
    bool min_Changed;

public:
    Clock():hour(0),min(0),hour_Changed(false),min_Changed(false){}
    Clock(unsigned h, unsigned m);
    ~Clock();

    void setClock(unsigned Hour, unsigned Min);
    void set_hour_Changed(bool);
    void set_min_Changed(bool);

    unsigned gethour()const;
    unsigned getmin()const;
    bool get_hour_Changed()const;
    bool get_min_Changed()const;

    bool getmin(unsigned*print);
    bool gethour(unsigned* print);


};
#endif //CLOCK_H