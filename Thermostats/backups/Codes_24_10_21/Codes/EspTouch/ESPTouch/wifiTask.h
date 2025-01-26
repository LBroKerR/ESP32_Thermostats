#pragma once
#ifndef WIFITASK_H
#define WIFITASK_H

#include "DataHandler.h"
#include "ServerWifi.h"
#include "ACK_wifi.h"
#include <WiFi.h>
//#include <WebServer.h>
#include <Arduino.h>

#define CODE     1000
#define DECODE   1000

//inner data id

//requestable
//send if changed
#define WANTEDTMP 2 //id 2
#define PROG 3//id 3
#define SWITCH 4 //id 4
//requestable
#define HOUR_WIFI 5
#define MIN_WIFI 6

//not requestable
#define TEMP 7
//#define HEATINGID 9

//requests 
#define MAC 8
#define NAME 1 
#define NEGATIV 100
#define RESENDACKS 1000

//outter data id will be heatingcircle indexes, and component id-s

//example 99 99 2 0 223
//         index 99 id 99 wtemp=22.3


class wifiTask{

    DataHandler* data;
    ACK_wifi* acks;
    unsigned number_of_waited_Answer;
    unsigned wait;

    float makePackage(ACK_wifi, unsigned device_id, String*);
    bool Answer_Request( ACK_wifi, unsigned ID);
    bool requestData();
    void storeData(unsigned heatingID, unsigned index);
    bool check_acks(unsigned heatingID, String Mac);
    bool ReceiveData();

    void send_again();
    void send_msg_to_heatingcircle_devices(unsigned index, bool);
    void send_msg_to_all_devices(float , unsigned);
    void sendData();

    void add_Waited_ack(ACK_wifi const newAck);
    void remove_disconnected_device_ACKS(String mac);
    void remove_ACK(String mac);

    void checkActiveClients();

public:

    wifiTask(DataHandler*);
    ~wifiTask();

    void main();


};
#endif // WIFITASK