#pragma once
#ifndef HTML_PAGE_H
#define HTML_PAGE_H


#include <Arduino.h>

#include "UnorderedList.h"
#include "P_tag.h"
class HTML_page{

    String head;

    P_tag *data;
    unsigned number_of_tags;

    String JavaScipt;

    UnorderedList* list;
    unsigned number_of_listelem;
public:
    HTML_page();
    HTML_page(String);
    ~HTML_page();

    void setHead(String);
    void add_tag(String, String, String);
    void remove_tag(unsigned);
    void add_list_elem(String url, String text);
    void remove_list_elem(uint32_t);

    String get_page();

    void set_java_script(String param);
    String get_java_script();

};
#endif //HTML_PAGE_H