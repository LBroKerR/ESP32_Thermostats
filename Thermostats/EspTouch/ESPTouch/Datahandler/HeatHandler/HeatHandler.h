#pragma once
#ifndef HEATHANDLER_H
#define HEATHANDLER_H

#include "HeatingCircleHandler.h"
#include "Modbus_data.h"

#include "bool_mutex.h"

#define HEATING_ON true
#define HEATING_OFF false


class HeatHandler{
    HeatingCircleHandler* HeatingCircles;
    Modbus_data modbusData;
    unsigned number_of_HeatingCircles;
    bool_mutex *status;
    bool_mutex heatingMode;
    bool heatingMode_changed;

public:


    HeatHandler();
    HeatHandler(unsigned slave_id);
    ~HeatHandler();

    bool add_HeatingCircles();
    bool add_HeatingCircles(unsigned number);
    bool remove_HeatingCircles(unsigned index);
    //index is the must be between 0 and number_of_HeatingCircles
    bool add_device_to_HeatingCircles(unsigned index, String const MACaddress, String const name, float const temp,unsigned const id, String ip);
    bool add_Measuringsensor(unsigned index, float offset, unsigned id, String name);

    void remove_device_from_HeatingCircles(String ip);
    HeatingCircleHandler* getHeatingCircleHandler();

    //from designed gui
    void setHeatingMode(bool const );
    bool getHeatingMode(bool*);
    void get_HeatingCircles_status(float );
    unsigned get_number_of_HeatingCircles();
    bool_mutex* getStatus();

    bool get_heatingMode_changed()const;
    void set_heatingMode_changed(bool const);

    void set_modbus_data(unsigned id, uint16_t register_address, uint8_t register_number);
    Modbus_data get_modbus_data();


};
#endif //HEATHANDLER_H