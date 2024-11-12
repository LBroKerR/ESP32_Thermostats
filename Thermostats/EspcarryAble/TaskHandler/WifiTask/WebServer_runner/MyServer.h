#pragma once
#ifndef MYSERVER_H
#define MYSERVER_H

#include <Arduino.h>

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsClient.h>


#include "HTML_page.h"
#include "Clients.h"
#include "JSON_message.h"


#define DELAY 2500


class MyServer{

  String ssid;
  String pass;
  String server_ip;
  unsigned Host;

  HTML_page *index;
  Clients* clients;

  AsyncWebServer server;
  AsyncWebSocket ws{"/ws"};
  WebSocketsClient webSocket;

  String msg;

  JSON_message * Data;

public:
    MyServer(String user, String pw, unsigned);
    ~MyServer();
    void Wifi_connection();
    void Server_turning_on();
    void connect_to_server(String ip);
    void reconnect();

    String html_page();
    void create_html_page(String title);

    HTML_page* get_Page();

    bool check_ip_host(IPAddress clientIP);

    void handleWebSocketMessage(void *arg, uint8_t *data, size_t len, String);
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    void onEvent1( WStype_t type, uint8_t* payload, size_t length);

    void notifyClients(String sensorReadings); 
    void run_server();
    void updata();
    void Client_update();

    void sendMessage();

    void set_JS_msg(String param);
    String get_JS_msg();

    String get_Mac()const;

    JSON_message *get_received_data();

};
#endif //MYSERVER_H