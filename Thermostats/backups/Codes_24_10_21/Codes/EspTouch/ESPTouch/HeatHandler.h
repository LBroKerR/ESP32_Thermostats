#pragma once
#ifndef HEATHANDLER_H
#define HEATHANDLER_H

#include "HeatingCircleHandler.h"
#include "modbusHandler.h"

#define HEATING_ON true
#define HEATING_OFF false


class HeatHandler{
    HeatingCircleHandler* HeatingCircles;
    modbusHandler* modbus;
    unsigned number_of_HeatingCircles;
    bool *status;
    bool heatingMode;
    bool heatingMode_changed;

public:

    void Communicate_with_PLC(float);

    HeatHandler();
    HeatHandler(unsigned slave_id);
    ~HeatHandler();

    bool add_HeatingCircles();
    bool add_HeatingCircles(unsigned number);
    bool remove_HeatingCircles(unsigned index);
    //index is the must be between 0 and number_of_HeatingCircles
    bool add_device_to_HeatingCircles(unsigned index, String const MACaddress, String const name, float const temp,unsigned const id);
    bool add_Measuringsensor(unsigned index, float offset, unsigned id, String name);

    void remove_device_from_HeatingCircles(String Mac);
    HeatingCircleHandler* getHeatingCircleHandler();

    //from designed gui
    void setHeatingMode(bool const );
    bool getHeatingMode()const;
    void get_HeatingCircles_status(float );
    unsigned get_number_of_HeatingCircles();
    bool* getStatus();

    bool get_heatingMode_changed()const;
    void set_heatingMode_changed(bool const);


};
#endif //HEATHANDLER_H