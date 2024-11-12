#pragma once
#ifndef CLIENTS_H
#define CLIENTS_H

#include <Arduino.h>

class Clients{

    unsigned size;
    String *IPs;
    unsigned *ids;

public:
    Clients();
    ~Clients();
    bool add(String, unsigned id);
    int Del(String);
    String *get();
    unsigned *get_ids();
    String get(unsigned);
    unsigned getSize();
};



#endif//CLIENT_H