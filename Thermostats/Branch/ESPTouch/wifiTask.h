#pragma once
#ifndef WIFITASK_H
#define WIFITASK_H

#include <Arduino.h>
#include <WiFi.h>
#include <Arduino_JSON.h>

#include "DataHandler.h"
#include "MyServer.h"
#include "JavaScript.h"
#include "styles.h"

#define TITLE "ESPTouch"

#define TIMER_DELAY 500

//javaScript span variables
#define ACTIVE_PROGRAM "active_prog"
#define WANTED_TEMP "wtmp"

#define ACTIVE_PROGRAM_SLAVE "active_prog_slave"
#define WANTED_TEMP_SLAVE "wtmp_slave"

#define TEMPERARTURE "temp_"
#define HUMADITY "hmd_"
#define SIMPLE_TAG "simple tag"
#define HEATINGCIRCLE_SWITCH "heating_"

//client websocket msg to main server, and not for refress its own server page
#define MAC_ADDRESS "mac"
#define ID "id"
#define HEATINGCIRCLE_ID "heating_id"
#define DEVICE_NAME "name"

#define TIME_HOUR "hour"
#define TIME_MIN "min"

#define DEFAULT_TEMP 20.0


class wifiTask{

  MyServer *server;
  DataHandler *data;
  unsigned sensor_location;

  unsigned lastTime;
  unsigned timerDelay;
  bool function_selector;

  void init_html_page();
  void set_Json_messages();
  void client_server_activity_check();

  void set_active_prog(String);
  void set_wtmp(String);
  void set_temp(JSONVar);
  void set_mac(String,JSONVar,String);
  void proccess_received_data();

public:

  wifiTask(DataHandler *);
  ~wifiTask();

  void main();
};
#endif // WIFITASK