#pragma once
#ifndef P_TAG_H
#define P_TAG_H


#include <Arduino.h>

class P_tag{
    String id;
    String name;
    String SI;

public:
    P_tag(/* args */);
    P_tag(String param, String param2, String param3);

    void set_tag(String, String, String param3 );
    String get_html_tag();

};

#endif //P_TAG_H