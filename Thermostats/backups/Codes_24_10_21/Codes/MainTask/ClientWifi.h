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
  unsigned Host;
  WiFiClient client;

  float rawdata;
  float data;
  int Id;
  bool Switch;

  bool ConnectToWiFi();
  bool ConncetToServer();

  bool ReceiveRequestedData();
  void sendACK();
  void sendMAC();

  void setID();
  void SetData();

public:
  ClientWifi();
  ClientWifi(String ip, String username, String pw, unsigned host, bool );
  ~ClientWifi();

  void IsconnectedToWifi();
  void IsconnectedToServer();

  void sendData(float);
  bool ReceiveRawData();
  bool RequestData(int);

  float getData();
  int getID();
  bool getSwitch();

};
#endif // CLIENTWIFI_H