#include "Clock.h"

  Clock::Clock(){
    hour.set_variable(0);
    min.set_variable(0);
    hour_Changed.set_variable(false);
    min_Changed.set_variable(false);
  }

   Clock::Clock(unsigned h, unsigned m){
    setClock(h,m);
    hour_Changed.set_variable(false);
    min_Changed.set_variable(false);
   }
   Clock::~Clock(){
   }

   //setter
  void Clock::setClock(unsigned Hour, unsigned Min){
    if(Hour>=0 && Hour<24){
        hour.set_variable(Hour);
        hour_Changed.set_variable(true);
    }
    else{
      hour.set_variable(0);
    }
    if(Min>=0 && Min<60){
        min.set_variable(Min);
        min_Changed.set_variable(true);
    }
    else{
      min.set_variable(0);
    }
  }

void Clock::set_hour_Changed(bool param){
    hour_Changed.set_variable(param);
}
void Clock::set_min_Changed(bool param){
    min_Changed.set_variable(param);
}
  //getters
bool Clock::gethour(unsigned* tmp){
  return hour.get_variable(tmp);
}
bool Clock::getmin(unsigned* tmp){
  return min.get_variable(tmp);
}

bool Clock::get_hour_Changed(){
    bool tmp=false;
    hour_Changed.get_variable(&tmp);
    return tmp;
}
bool Clock::get_min_Changed(){
    bool tmp=false;
    min_Changed.get_variable(&tmp);
    return tmp;
}



/*bool Clock::gethour(unsigned* print){
  bool tmp=false;
  hour_Changed.get_variable(&tmp);
    if(tmp){
        if(hour.get_variable(print)){
        hour_Changed.set_variable(false);
        return true;
      }
    }
    return false;
}
bool Clock::getmin(unsigned*print){
    bool tmp=false;
    min_Changed.get_variable(&tmp);
    if(tmp){
        if(min.get_variable(print)){
        min_Changed.set_variable(false);
        return true;
        }
    }
    return false;
}*/