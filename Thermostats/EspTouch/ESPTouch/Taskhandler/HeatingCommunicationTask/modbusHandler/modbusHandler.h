#pragma once
#ifndef MODBUSHANDLER_H
#define MODBUSHANDLER_H
#include <ModbusMaster.h>
//#include <SoftwareSerial.h>
#include <Arduino.h>
#include "HeatingCircleHandler.h"

#define RX 3
#define TX 1
#define BAUDRATE 9600

class modbusHandler{
public:
    // Konstruktor, amely beállítja a slave ID-t, a regiszter címét és a regiszterek számát
    modbusHandler(uint8_t slaveID, uint16_t registerAddress, uint8_t numberOfRegisters);

    // Függvény az adat küldésére
    void UsingModbus(uint8_t data);

    // Függvény az adat küldésének állapotának ellenőrzésére
    bool isSuccess();

private:
    ModbusMaster node;  // A ModbusMaster objektum
    uint8_t slaveID;    // A slave ID
    uint16_t registerAddress;  // A regiszter címe
    uint8_t numberOfRegisters;  // A regiszterek száma
    bool successFlag;   // A kommunikáció sikerességének nyomon követése
};


#endif //MODBUSHANDLER_H