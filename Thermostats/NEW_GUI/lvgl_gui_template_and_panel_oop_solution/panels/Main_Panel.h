#pragma once
#ifndef MAIN_PANEL_H
#define MAIN_PANEL_H

#include "Panel_adapter.h"
#include "Side_Panel.h"
#include "elements_tune.h"

#include "lvgl.h"

class Main_Panel{
    lv_obj_t * main_panel;
    Side_Panel * panel_selctor;
    Panel_adapter ** panels;
    unsigned number_of_panels;

public:
    Main_Panel();
    Main_Panel(lv_obj_t * screen);
    ~Main_Panel();

    bool add_panel(Panel_adapter * panel);

    Panel_adapter * get_panel(unsigned selector_id);
    

};



#endif