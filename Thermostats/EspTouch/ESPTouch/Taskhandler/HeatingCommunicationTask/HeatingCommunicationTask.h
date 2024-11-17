#pragma once
#ifndef HEATINGCOMMUNICATION_H
#define HEATINGCOMMUNICATION_H

#include <Arduino.h>

#include "modbusHandler.h"
#include "DataHandler.h"

class HeatingCommunicationTask{

    modbusHandler *modbus;
    DataHandler* data;

public: 
    HeatingCommunicationTask(DataHandler* obj): data(obj), modbus(nullptr){}
    ~HeatingCommunicationTask();
    void set_modbus_communication(unsigned id, uint16_t register_address, uint8_t num_reg);
    void Communicate_with_PLC();
};

#endif //HEATINGCOMMUNICATION_H