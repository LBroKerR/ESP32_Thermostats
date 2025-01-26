#pragma once
#ifndef PROGRAMS_H
#define PROGRAMS_H
#define TOUCH                0
#define NUMBER_OF_PROGRAM    5
#define SIZE_OF_A_PROGRAM    24
#define MIN_TEMP             10.0
#define MAX_TEMP             30.0
#define DEFAULT_TEMP         20.0

class programs{
    //espcarryable/esptouch
    unsigned active_program_index;
    bool active_program_index_changed;

    float Wanted_temp;
    bool wtmp_changed;
public:
    programs();
    ~programs();

    //setters
    bool set_active_program_index(int );
    void set_Wanted_temp(float const);
    void set_active_program_index_changed(bool const);
    void set_wtmp_changed(bool const);
    bool get_active_program_index_changed()const;
    bool get_wtmp_changed()const;
    unsigned get_active_program_index()const;
    float get_Wanted_temp()const;

};
#endif //PROGRAMS_H