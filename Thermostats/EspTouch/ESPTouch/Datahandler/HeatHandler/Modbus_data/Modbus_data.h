#pragma once
#ifndef MODBUS_DATA_H
#define MODBUS_DATA_H

#include <Arduino.h>

class Modbus_data{

    unsigned slaveID;
    uint16_t registerAddress;// 0x0001;  // Register address to read from
    uint8_t numRegisters;
public:
    Modbus_data();
    void set_data(unsigned id, uint16_t address, uint8_t num);
    unsigned get_ID()const;
    uint16_t get_address()const;
    uint8_t get_number()const;
};

#endif //MODBUS_DATA_H