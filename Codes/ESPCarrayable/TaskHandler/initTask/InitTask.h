#pragma once
#ifndef INITTASK_H
#define INITTASK_H

#include <Arduino.h>
#include "DataHandler.h"
#include <EEPROM.h>
#include "EEPROMhandler.h"

#define EEPROM_SIZE      0x0080

#define UPSIZE           0x0015


class InitTask{
    DataHandler* WifiInit(DataHandler *obj);
    DataHandler* DataInit(DataHandler *obj);
    void saveData(DataHandler*);
public:
  InitTask(){}
    DataHandler* main(DataHandler*);
    void save(DataHandler*);
};
#endif // INITTASK_H