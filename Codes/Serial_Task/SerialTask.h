#pragma once
#ifndef SERIALTASK_H
#define SERIALTASK_H

#include "Arduino.h"
#include <EEPROM.h>
#include "MenuHandler.h"
#include "SerialPortHandler.h"
#include "EEPROMhandler.h"
#define EEPROM_SIZE  0x0400

class SerialTask{

  MenuHandler* menu;
  SerialPortHandler*IO;
  String incomingData; 

  void init();
  void functioncalling(MenuHandler*,bool(*func)(void*));
  bool system(MenuHandler*&);

public:
  SerialTask();
  SerialTask(SerialPortHandler *param);
  ~SerialTask();


  void main();
};

#endif // SERIALTASK_H
