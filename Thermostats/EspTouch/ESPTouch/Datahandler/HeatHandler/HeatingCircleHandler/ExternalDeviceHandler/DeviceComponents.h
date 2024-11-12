#pragma once
#ifndef DEVICECOMPONENTS_H
#define DEVICECOMPONENTS_H

#include "Components.h"


class DeviceComponents{
    Components *devices; 
    unsigned number_of_comp;
    bool changed;

public:
    DeviceComponents();
    ~DeviceComponents();

    unsigned getSize()const;

    void add_Component(String Mac, String name, float temp, unsigned id, String ip);
    bool remove_Component(String ip);
    Components* getDevices();

    void Set_changed(bool const);
    bool get_changed()const;

};
#endif //DEVICECOMPONENTS_H