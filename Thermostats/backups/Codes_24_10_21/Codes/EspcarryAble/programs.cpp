#include "programs.h"

    programs::programs(){
        active_program_index=0;
        active_program_index_changed=false;
        Wanted_temp=DEFAULT_TEMP;
        wtmp_changed=false;
    }

    programs::~programs(){
        //void
    }

    //setters
    bool programs::set_active_program_index(int param){
      int tmp=active_program_index+param;
        if(tmp < 0 ){
          active_program_index=NUMBER_OF_PROGRAM-1;
        }
        else if(tmp>=NUMBER_OF_PROGRAM){
          active_program_index=0;
        }
        else if(tmp>=0 && tmp<NUMBER_OF_PROGRAM){
          active_program_index=tmp;
        }
        else if(param==0){
          set_active_program_index_changed(false);
          return false;
        }
        set_active_program_index_changed(true);
        return true;
    }
    void programs::set_Wanted_temp(float const param){
        if((Wanted_temp+param)>=MIN_TEMP && (Wanted_temp+param)<=MAX_TEMP){
            Wanted_temp+=param;
            set_wtmp_changed(true);
        }
    }
    void programs::set_active_program_index_changed(bool const param){
        active_program_index_changed=param;
    }
    void programs::set_wtmp_changed(bool const param){
        wtmp_changed=param;
    }
        bool programs::get_active_program_index_changed()const{
        return active_program_index_changed;
    }
    bool programs::get_wtmp_changed()const{
        return wtmp_changed;
    }
     unsigned programs::get_active_program_index()const{
        return active_program_index;
    }
    float programs::get_Wanted_temp()const{
        return Wanted_temp;
    }