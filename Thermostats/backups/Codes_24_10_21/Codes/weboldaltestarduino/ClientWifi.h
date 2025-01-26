#pragma once
#ifndef CLIENTWIFI_H
#define CLIENTWIFI_H

#include <WiFi.h>
#include "esp_task_wdt.h"
#include <Arduino.h>

#define CODE     1000
#define DECODE   1000

#define IP_SIZE  16
#define U_P_SIZE 20

class ClientWifi{

  char IP[IP_SIZE];
  char SSID[U_P_SIZE];
  char pass[U_P_SIZE];
  unsigned HOST;
  WiFiClient client;

  float rawdata;
  float data;
  int ID;

  bool ConnectToWiFi();
  bool ConncetToServer();

  bool ReceiveRequestedData();
  void sendACK();
  void sendMAC();

  void setID();
  void SetData();

public:
  ClientWifi();
  ClientWifi(String ip, String username, String pw, unsigned host );
  ~ClientWifi();

  void IsconnectedToWifi();
  void IsconnectedToServer();

  void sendData(float);
  bool ReceiveRawData();
  bool RequestData(int);

  float getData();
  int getID();

};
#endif // CLIENTWIFI_H