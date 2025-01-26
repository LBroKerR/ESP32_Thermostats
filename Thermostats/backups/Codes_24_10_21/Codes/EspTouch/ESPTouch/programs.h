#pragma once
#ifndef PROGRAMS_H
#define PROGRAMS_H

#define NUMBER_OF_PROGRAM    5
#define SIZE_OF_A_PROGRAM    24
#define MIN_TEMP             10.0
#define MAX_TEMP             30.0
#define DEFAULT_TEMP         20.0

class programs{
    //espcarryable/esptouch
    unsigned active_program_index;
    bool active_program_index_changed;

    unsigned ProgHour_index;
    bool ProgHour_index_changed;
    bool active_prog_send;

    float Wanted_temp;
    bool wtmp_changed;
    bool wtmp_chanded_send;

    //esptouch
    bool manual_mode;
    float *Programs[NUMBER_OF_PROGRAM];
    bool programs_Changed;

public:
    programs();
    ~programs();

    //setters
    void set_active_program_index(unsigned const);
    void set_Wanted_temp(float const);
    void set_programs(float*, unsigned const size,unsigned const);
    void set_programs(double* param, unsigned const index);
    bool set_program_element( unsigned hour, float data);
    bool set_program_element( float data);

    void set_active_program_index_changed(bool const);
    void set_wtmp_changed(bool const);
    void set_manual_mode(bool const);
    void set_programs_Changed(bool const);
    void set_ProgHour_index(unsigned);
    void set_ProgHour_index_changed(bool);

    //getters
    bool get_active_program_index_changed()const;
    bool get_wtmp_changed()const;
    bool get_manual_mode()const;
    bool get_programs_Changed()const;

    unsigned get_active_program_index()const;
    float get_Wanted_temp()const;

    float* get_programs()const;
    float* get_programs(unsigned index)const;

    float get_program_element(unsigned hour)const;
    float get_program_element()const;

    unsigned get_ProgHour_index()const;
    bool get_ProgHour_index_changed()const;
};
#endif //PROGRAMS_H