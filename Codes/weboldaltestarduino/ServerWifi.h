#pragma once
#ifndef SERVERWIFI_H
#define SERVERWIFI_H

#include <WiFi.h>
#include "esp_task_wdt.h"
#include <Arduino.h>

#define CODE     1000
#define DECODE   1000

#define U_P_SIZE 20

#define MAC_ID   0

class ServerWifi{

  char SSID[U_P_SIZE];
  char pass[U_P_SIZE];
  unsigned HOST;

  WiFiServer server;
  WiFiClient *clients;
  unsigned Current_Client;
  unsigned number_of_client;

  float rawdata;
  float data;
  int ID;
  String Client_MAC_ADDRESS;

  void setData();
  void setID();
  void setMAC(String );

  void SendACK();

  bool remove_lost_client();
  bool add_client(WiFiClient newClient);

public:

  ServerWifi();
  ServerWifi(String username, String pw, unsigned host);
  ~ServerWifi();

  float getData();
  int getID();
  String getMAC(unsigned);

  bool ReceiveRawData();
  bool RequestData();
  void SendData(unsigned id, float param);

  void Device_try_to_Connect();
  void Check_active_clients();

};
#endif // SERVERWIFI_H