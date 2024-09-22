#pragma once
#ifndef HEATHANDLER_H
#define HEATHANDLER_H

#include <ModbusMaster.h>
#include "HeatingCircleHandler.h"
//#include "Programs.h"

#define RX 3
#define TX 1
#define BAUDRATE 9600


class HeatHandler{
    HeatingCircleHandler* HeatingCircles;

    unsigned number_of_HeatingCircles;
    bool heatingMode;
    unsigned slaveID;
public:

    bool ACKmsgCheck();
    bool UsingModbus(float);

    HeatHandler();
    HeatHandler(unsigned slave_id);
    ~HeatHandler();

    bool add_HeatingCircles();
    bool remove_HeatingCircles(unsigned index);
    bool add_device_to_HeatingCircles(unsigned index, String const MACaddress, String const name, unsigned const Heatingid,unsigned const id);
    bool add_Measuringsensor(unsigned index, float offset, unsigned id, String name);

    void remove_device_from_HeatingCircles(unsigned const id);

    //from designed gui
    void setHeatingMode(bool const );
    bool getHeatingMode()const;
    bool* get_HeatingCircles_status( unsigned*size);


};
#endif //HEATHANDLER_H