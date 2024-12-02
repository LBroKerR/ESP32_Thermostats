#pragma once
#ifndef WIFITASK_H
#define WIFITASK_H

#include <Arduino.h>
#include <Arduino_JSON.h>

#include "DataHandler.h"
#include "MyServer.h"
#include "JavaScript.h"
#include "styles.h"

#define TIMER_DELAY 5000

#define SIMPLE_TAG "simple tag"
#define TEMPERATURE "temp_"
#define HUMADITY "hmd_"
#define ACTIVE_PROGRAM "active_prog_slave"
#define WANTED_TEMP "wtmp_slave"
#define HEATINGCIRCLE_SWITCH "heating_"


//client websocket msg to main server, and not for refress its own server page
#define MAC_ADDRESS "mac"
#define ID "id"
#define HEATINGCIRCLE_ID "heating_id"
#define DEVICE_NAME "name"

#define TIME_HOUR "hour"
#define TIME_MIN "min"

class wifiTask{
  MyServer *server;
  DataHandler *data;

  unsigned lastTime;
  unsigned timerDelay;
  bool function_selector;

public:

  wifiTask(DataHandler *);
  ~wifiTask();
  void init_html_page();

  void set_Json_messages();

  //void check_client_activity();

  void set_active_program(String);
  void set_wanted_temp(String);
  void set_heating_switch(String);
  void set_time(String, String);

  void proccess_received_data();


  void main();
  
};
#endif // WIFITASK