#pragma once
#ifndef LABELED_BUTTON_H
#define LABELED_BUTTON_H


#include "lvgl.h"

class labeled_button{
    lv_obj_t * button;
    lv_obj_t * label;
    bool button_action;
public:
    labeled_button();
    ~labeled_button();

    void add_(lv_obj_t * parent_panel);
    void set_cordinator(int x, int y);
    void set_area(unsigned width, unsigned height, int colour);
    void set_label(const char* label_text, int colour, int font_size = 14);

    void set_action(bool const event);
    void get_action(bool* event);

    void event(lv_event_t* event);
};
#endif /*LABELED_BUTTONS_H*/