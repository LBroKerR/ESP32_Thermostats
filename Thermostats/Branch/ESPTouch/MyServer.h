#pragma once
#ifndef MYSERVER_H
#define MYSERVER_H

#include <Arduino.h>

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Arduino_JSON.h>
#include <WebSocketsClient.h>


#include "HTML_page.h"
#include "Clients.h"
#include "JSON_message.h"

#define DELAY 2500



class MyServer{

  String ssid;
  String pass;
  unsigned Host;

  HTML_page *index;
  Clients* clients;

  AsyncWebServer server;
  AsyncWebSocket ws{"/ws"};
  WebSocketsClient webSocket;

  String msg;
  JSON_message *Data;

  bool new_client;

public:
    MyServer(String user, String pw, unsigned);
    ~MyServer();
    String Wifi_connection();
    void Server_turning_on();
    void connect_to_server();
    void reconnect();

    String html_page();
    void create_html_page(String title);

    HTML_page* get_Page();
    Clients* get_Clients();

    bool check_ip_host(IPAddress clientIP);

    void handleWebSocketMessage(void *arg, uint8_t *data, size_t len, String);
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    void onEvent1( WStype_t type, uint8_t* payload, size_t length);

    void notifyClients(String sensorReadings); 
    void run_server();
    void updata();

    void sendMessage();

    void set_JS_msg(String );
    String get_JS_msg()const;

    JSON_message* get_event_Data();

    void set_new_client(bool);
    bool get_new_client()const;

};
#endif //MYSERVER_H