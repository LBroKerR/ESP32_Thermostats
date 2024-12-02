#include "Clock.h"

   Clock::Clock(unsigned h, unsigned m){
    setClock(h,m);
    hour_Changed=false;
    min_Changed=false;
    read_write_access=true;
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

void Clock::set_hour_Changed(bool param){
    hour_Changed=param;
}
void Clock::set_min_Changed(bool param){
    min_Changed=param;
}
  //getters
  unsigned Clock::gethour()const{
    return hour;
  }
  unsigned Clock::getmin()const{
    return min;
  }

bool Clock::get_hour_Changed()const{
    return hour_Changed;
}
bool Clock::get_min_Changed()const{
    return min_Changed;
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
bool Clock::get_access()const{
  return read_write_access;
}
void Clock::set_access(bool const param){
  read_write_access=param;
}