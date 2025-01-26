#pragma once
#ifndef SERIALTASK_H
#define SERIALTASK_H

#include "Arduino.h"
#include <EEPROM.h>
#include "MenuHandler.h"
#include "SerialPortHandler.h"
#include "EEPROMhandler.h"
#define ESPCARRY 0
#define ESPTOUCH 1

#if(ESPCARRY && !ESPTOUCH)
  #define EEPROM_SIZE  0x0080
#endif
#if(ESPTOUCH && !ESPCARRY)
  #define EEPROM_SIZE  0x0430
#endif

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
