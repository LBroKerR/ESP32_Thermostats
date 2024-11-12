#pragma once
#ifndef UNORDEREDLIST_H
#define UNORDEREDLIST_H

#include <Arduino.h>

class UnorderedList{
    String list_elem_vaule;
    String text;

public:
    UnorderedList();
    void set_elem_vaule(String, String);
    String get_text()const;
    String get_link()const;
    String get_html_link();
};

#endif //UNORDEREDLIST_H