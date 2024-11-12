#pragma once
#ifndef JSON_MESSAGE_H
#define JSON_MESSAGE_H

#include <Arduino.h>

class JSON_message{
    String *msg;
    String *ip;
    unsigned number_of_msg;

public:
    JSON_message();
    ~JSON_message();
    void add_msg(String, String);
    void remove_msg(unsigned);
    String *get_msg_array();
    String  get_msg(unsigned);
    unsigned size()const;
    String* get_ip_array();
};

#endif 