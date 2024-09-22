#include "Clock.h"

   Clock::Clock(unsigned hour, unsigned min){
    rtc=new ESP32Time(UTC_MINUS_1);
                    //          s   m   h+1 d   m   y
    rtc->setTime(1, min, hour-1, DAY, MONTH, YEAR);
   }
   Clock::~Clock(){
    delete rtc;
   }

   //setter
   void Clock::updateClock(){
    unsigned tmp1, tmp2;
    tmp1=rtc->getHour(true);
    tmp2=rtc->getMinute();
    if(tmp1!=hour){
        hour=tmp1;
        hour_Changed=true;
    }
    if(tmp2!=min){
        min=tmp2;
        min_Changed=true;
    }
   }

bool Clock::gethour(unsigned* print){
    if(hour_Changed){
        print=&hour;
        hour_Changed=false;
        return true;
    }
    return false;
}
bool Clock::getmin(unsigned*print){
        if(min_Changed){
        print=&min;
        min_Changed=false;
        return true;
    }
    return false;
}