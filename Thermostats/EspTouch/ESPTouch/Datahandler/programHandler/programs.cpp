#include "programs.h"

    programs::programs(){
        active_program_index=0;
        ProgHour_index=0;
        active_program_index_changed=false;
        Wanted_temp=DEFAULT_TEMP;
        wtmp_changed=false;
        manual_mode=false;
        programs_Changed=false;
        ProgHour_index_changed=false;
        server_update_wtmp=false;
        server_update_prog_index=false;
        for(unsigned i=0; i<NUMBER_OF_PROGRAM; i++){
            Programs[i]=new float[SIZE_OF_A_PROGRAM];
            for(unsigned k=0; k<SIZE_OF_A_PROGRAM; k++){
                Programs[i][k]=DEFAULT_TEMP;
            }
        }
    }
    programs::~programs(){
        //void
        for(unsigned i=0; i<NUMBER_OF_PROGRAM; i++){
          delete[] Programs[i];
        }
        delete[] Programs;
    }

    //setters
    void programs::set_server_update_prog_index(bool param){
        server_update_prog_index=param;
    }
    void programs::set_active_program_index(unsigned const param){
        if(param>=0 && param<NUMBER_OF_PROGRAM){
            active_program_index=param;
            set_active_program_index_changed(true);
        }
    }
    void programs::set_Wanted_temp(float const param){
        if(param>=MIN_TEMP && param<=MAX_TEMP){
            Wanted_temp=param;
            set_server_update_wtmp(true);
        }
    }
    void programs::set_programs(float* param, unsigned const size, unsigned const index){
        if(param!=nullptr && size<SIZE_OF_A_PROGRAM && size>0 && index>=0 && index<NUMBER_OF_PROGRAM){
            for(unsigned i=0; i<size; i++){
                Programs[index][i]=param[i];
            }
        }
    }
     void programs::set_programs(double* param, unsigned const index){
        if(param!=nullptr && index>=0 && index<NUMBER_OF_PROGRAM){
            for(unsigned i=0; i<SIZE_OF_A_PROGRAM; i++){
                Programs[index][i]=(float)param[i];
            }
        }
    }
    bool programs::set_program_element( unsigned hour, float data){
        if(hour<SIZE_OF_A_PROGRAM && hour>=0){
            if(data>=MIN_TEMP && data<=MAX_TEMP){
                Programs[get_active_program_index()][hour]=data;
                set_programs_Changed(true);
                return true;
            }
        }
        return false;
    }
    bool programs::set_program_element( float data){
            if(data>=(float)MIN_TEMP && data<=(float)MAX_TEMP){
                Programs[get_active_program_index()][get_ProgHour_index()]=data;
                set_programs_Changed(true);
                return true;
            }
        return false;
    }

    void programs::set_active_program_index_changed(bool const param){
        active_program_index_changed=param;
    }
    void programs::set_wtmp_changed(bool const param){
        wtmp_changed=param;
    }
    void programs::set_manual_mode(bool const param){
        manual_mode=param;
    }
    void programs::set_programs_Changed(bool const param){
        programs_Changed=param;
    }
    void programs::set_ProgHour_index(unsigned param){
        if(param!=ProgHour_index){
            ProgHour_index=param;
            set_ProgHour_index_changed(true);
        }
    }
    void programs::set_ProgHour_index_changed(bool param){
         ProgHour_index_changed=param;
    }
    void programs::set_server_update_wtmp(bool param){
        server_update_wtmp=param;
    }

    void programs::set_received_index(unsigned param){
        if(param>=0 && param<NUMBER_OF_PROGRAM){
            active_program_index=param;
            set_Wanted_temp(get_program_element());
            set_active_program_index_changed(true);
        }
    }
    void programs::set_received_wtmp(float param){
        if(param>=MIN_TEMP && param<=MAX_TEMP){
            Wanted_temp=param;
            set_wtmp_changed(true);
        }
    }


    //getters
    bool programs::get_server_update_prog_index()const{
        return server_update_prog_index;
    }
    bool programs::get_active_program_index_changed()const{
        return active_program_index_changed;
    }
    bool programs::get_wtmp_changed()const{
        return wtmp_changed;
    }
    bool programs::get_manual_mode()const{
        return manual_mode;
    }
    bool programs::get_programs_Changed()const{
        return programs_Changed;
    }

    unsigned programs::get_active_program_index()const{
        return active_program_index;
    }
    float programs::get_Wanted_temp()const{
        return Wanted_temp;
    }

    float* programs::get_programs()const{
        return Programs[get_active_program_index()];
    }
    float* programs::get_programs(unsigned index)const{
        if(index<NUMBER_OF_PROGRAM && index>=0){
            return  Programs[index];
        }
        return nullptr;
    }

    float programs::get_program_element(unsigned hour)const{
        float tmp=21.0;
        if(hour>=0 && hour<(unsigned)SIZE_OF_A_PROGRAM){
            tmp=Programs[get_active_program_index()][hour];
        }
        return tmp;
    }
    float programs::get_program_element()const{

        return Programs[get_active_program_index()][get_ProgHour_index()];
    }

    unsigned programs::get_ProgHour_index()const{
        return ProgHour_index;
    }
    bool programs::get_ProgHour_index_changed()const{
        return ProgHour_index_changed;
    }

    bool programs::get_server_update_wtmp()const{
        return server_update_wtmp;
    }