#pragma once
#ifndef MODBUSHANDLER_H
#define MODBUSHANDLER_H
#include <ModbusMaster.h>
#include <Arduino.h>
#include "HeatingCircleHandler.h"

#define RX 3
#define TX 1
#define BAUDRATE 9600

class modbusHandler{

    unsigned slaveID;
    ModbusMaster node;

    uint16_t registerAddress;// 0x0001;  // Register address to read from
    uint8_t numRegisters;  //2

    uint8_t *messages;
    unsigned number_of_msg;

public:

    modbusHandler();
    modbusHandler(unsigned id, uint16_t register_address, uint8_t num_reg);
    ~modbusHandler();

    void add_msg(uint8_t);
    void remove_msg(uint8_t);

    void ACKmsgCheck();
    void UsingModbus(uint8_t data);


};

#endif //MODBUSHANDLER_H