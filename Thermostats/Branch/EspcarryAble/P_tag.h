#pragma once
#ifndef P_TAG_H
#define P_TAG_H


#include <Arduino.h>

class P_tag{
    String id;
    String name;
    String Class;

public:
    P_tag(/* args */);
    P_tag(String Klass, String id, String text);

    void set_tag(String CClass, String id, String text);
    String get_html_tag();

};

#endif //P_TAG_H