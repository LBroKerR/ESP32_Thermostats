#pragma once
#ifndef WIFITASK_H
#define WIFITASK_H

#include "DataHandler.h"
#include "ClientWifi.h"

#define WANTEDTMP 2 //id 2
#define PROG 3//id 4
#define SWITCH 4 //id 4
#define HOUR_WIFI 5
#define MIN_WIFI 6
#define TEMP 7
#define HEATINGID 8
#define MAC 9
#define NAME 1 


class wifiTask{

    bool sendData(DataHandler *);
    bool receiveData(DataHandler *);
    float makePacket(float, int);
    bool requested(DataHandler *, int);

public:
    void init( DataHandler *);

    // if sendData or receivedata return true, the main will be returning true as well.
    bool main(DataHandler *);
};
#endif // WIFITASK