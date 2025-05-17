#pragma once 
#ifndef SIDE_PANEL_H
#define SIDE_PANEL_H

if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#include "lv_i18n.h"
#include "visuality_helper.h"


#include "elements_tune.h"
#include "image_buttons.h"
#include "ui_img_back_png.h"
#include "ui_img_home_png.h"
#include "ui_img_menu.h"
#include "ui_img_power_png.h"
#include "ui_img_save_png.h"

#define HOME_                 BUTTON_1
#define BACK_                 BUTTON_2
#define SAVE_                 BUTTON_3
#define MENU_                 BUTTON_4
#define POWER_                BUTTON_5


class Side_Panel
{
    lv_obj_t * panel;
    image_buttons * buttons;

    void power_button_init(unsigned index);
    void back_button_init(unsigned index);
    void save_button_init(unsigned index);
    void menu_button_init(unsigned index);
    void home_button_init(unsigned index);

public:

    Side_Panel();
    Side_Panel(lv_obj_t * parent_panel);
    ~Side_Panel();
    bool get_Panel_element(unsigned* activated_index );
};




#endif /*SIDE_PANEL_H*/