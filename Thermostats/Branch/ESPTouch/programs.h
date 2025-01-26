#pragma once
#ifndef PROGRAMS_H
#define PROGRAMS_H

#include "float_mutex.h"
#include "uint_mutex.h"
#include "bool_mutex.h"


#define NUMBER_OF_PROGRAM    5
#define SIZE_OF_A_PROGRAM    24
#define MIN_TEMP             10.0
#define MAX_TEMP             30.0
#define DEFAULT_TEMP         20.0

class programs{
    //espcarryable/esptouch
    uint_mutex active_program_index;
    bool active_program_index_changed;

    uint_mutex ProgHour_index;
    bool ProgHour_index_changed;
    bool active_prog_send;

    float_mutex Wanted_temp;
    bool wtmp_changed;
    bool wtmp_chanded_send;

    //esptouch
    bool_mutex manual_mode;
    float *Programs[NUMBER_OF_PROGRAM];
    bool programs_Changed;

    bool server_update_wtmp;
    bool server_update_prog_index;

public:
    programs();
    ~programs();

    //setters
    void set_server_update_prog_index(bool);
    void set_active_program_index(unsigned const);
    void set_Wanted_temp(float );
    void set_programs(float*, unsigned const size,unsigned const);
    void set_programs(double* param, unsigned const index);
    bool set_program_element( unsigned hour, float data);
    bool set_program_element( float data);
    void set_received_index(unsigned prog, unsigned);
    void set_received_wtmp(float param);

    void set_active_program_index_changed(bool const);
    void set_wtmp_changed(bool const);
    void set_manual_mode(bool const);
    void set_programs_Changed(bool const);
    void set_ProgHour_index(unsigned);
    void set_ProgHour_index_changed(bool);

    void set_server_update_wtmp(bool);

    //getters
    bool get_server_update_prog_index()const;
    bool get_active_program_index_changed()const;
    bool get_wtmp_changed()const;
    bool get_manual_mode(bool*);
    bool get_programs_Changed()const;

    bool get_active_program_index(unsigned*);
    bool get_Wanted_temp(float*);

    float* get_programs();
    float* get_programs(unsigned index);

    float get_program_element(unsigned hour);
    float get_program_element();

    bool get_ProgHour_index(unsigned*);
    bool get_ProgHour_index_changed()const;

    bool get_server_update_wtmp()const;
};
#endif //PROGRAMS_H