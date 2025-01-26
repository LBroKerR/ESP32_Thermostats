#include "Clock.h"

   Clock::Clock(unsigned h, unsigned m){
    setClock(h,m);
    hour_Changed=true;
    min_Changed=true;
   }
   Clock::~Clock(){
   }

   //setter
  void Clock::setClock(unsigned Hour, unsigned Min){
    if(Hour>=0 && Hour<24){
      hour=Hour;
    }
    else{
      hour=0;
    }
    if(Min>=0 && Min<60){
      min=Min;
    }
    else{
      min=0;
    }
  }
  //getters
  unsigned Clock::gethour()const{
    return hour;
  }
  unsigned Clock::getmin()const{
    return min;
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