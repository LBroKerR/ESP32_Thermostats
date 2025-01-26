#pragma once
#ifndef SERVERWIFI_H
#define SERVERWIFI_H

#include <WiFi.h>
#include "esp_task_wdt.h"
#include <Arduino.h>


#define U_P_SIZE 20


class ServerWifi{

  char SSID[U_P_SIZE];
  char pass[U_P_SIZE];
  uint16_t HOST;

  unsigned long timeoutTime;

  WiFiServer server;
  WiFiClient client;

  bool Switch;

  float rawdata;

  void SendACK();

public:

  ServerWifi();
  ServerWifi(String username, String pw, unsigned host);
  ~ServerWifi();

  void systembegin();
  bool isConnected();
  void reconnect();
  bool Available();
  void serverBeAvailable();

  bool ReceiveRawData();
  void SendRawData( float param);
  float getRawData();

  bool receiveString(String*);
  bool sendString(String);

  void setSwitch(bool const);
  bool getSwitch()const;

  WiFiClient getClient();
  bool setClient(WiFiClient);

};
#endif // SERVERWIFI_H