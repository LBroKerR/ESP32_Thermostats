#pragma once
#ifndef CLIENTWIFI_H
#define CLIENTWIFI_H

#include <WiFi.h>
#include "esp_task_wdt.h"
#include <Arduino.h>

    #define CODE             1000
    #define DECODE           1000

    #define UPSIZE           0x0015
    #define IPSIZE           0x0010

class ClientWifi{

  char Ip[IPSIZE];
  char SSID[UPSIZE];
  char pass[UPSIZE];
  
  uint16_t Host;
  WiFiClient client;

  float rawdata;
  float data;
  int Id;
  int heatingid;
  int deviceid;
  bool Switch;
  bool initDone;
  unsigned long timeoutTime;

  bool ConnectToWiFi();
  void sendACK();


public:
  ClientWifi();
  ClientWifi(String ip, String username, String pw, unsigned host, bool );
  ~ClientWifi();

  void IsconnectedToWifi();
  bool ConncetToServer();
  bool connection_check();
  String getMAC();

  void sendString(String);
  bool receiveString(String*); 

  void sendData(float);
  bool ReceiveRawData();
  bool ReceiveRequestedData();
  bool RequestData(int id);
  bool ReceiveACK();

  float getRawData();
  void setRawDAta(float);

  void SetData();
  float getData();

  void setID();
  int getID();

  void set_device_id();
  void set_heating_id();
  bool getSwitch();
  int get_device_id();
  int get_heating_id();
  void setInitDone(bool const param);
  bool getInitDone();
};
#endif // CLIENTWIFI_H