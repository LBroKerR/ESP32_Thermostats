#pragma once
#ifndef CLIENTS_H
#define CLIENTS_H

#include <Arduino.h>

class Clients{

    unsigned size;
    String *IPs;
    unsigned *ids;
    bool *status;

public:
    Clients();
    ~Clients();
    bool add(String, unsigned id, bool state);
    int Del(String);
    String *get();
    unsigned *get_ids();
    String get(unsigned);
    unsigned getSize();
    bool *get_status();
    void set_status(bool, unsigned);
};



#endif//CLIENT_H