#pragma once
#ifndef MAIN_PANEL_H
#define MAIN_PANEL_H

#include "Panel_adapter.h"
#include "Side_Panel.h"
#include "image_handler.h"
#include "elements_tune.h"

#include "lvgl.h"

#define PANEL_ID   0
#define WIFI_ID    1
#define BATTERY_ID 2

#define DECODE     100;

typedef images_handler battery_icons;
typedef images_handler WIFI_icons;

/*
 battery should be an object with label, on a panel?
 the wifi image as well?

 consider it!

 next steps: child panels creation and add them to the panels obj!

 let's think about how is it gonna be work with events!

 where will I call the virtual func with selector_id, to make thinks work!
*/

class Main_Panel{
    lv_obj_t * main_panel;

    Panel_adapter ** panels;
    unsigned number_of_panels;
    unsigned current_panel;

    battery_icons *battery;
    WIFI_icons* WIFI;

    lv_obj_t* clock_label;
    lv_obj_t* battery_percent_label;

    void battery_img_init();
    void wifi_img_init();

    bool panel_handler(unsigned index);
    bool wifi_image_handler(unsigned index);
    bool battery_image_handler(unsigned index);

public:
    Main_Panel();
    Main_Panel(lv_obj_t * parent);
    ~Main_Panel();

    bool add_panel(Panel_adapter * panel);

    bool get_panel(unsigned *selector_id)override;

};



#endif