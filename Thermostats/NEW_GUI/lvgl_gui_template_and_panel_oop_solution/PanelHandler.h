#pragma once 
#ifndef PANEL_HANDLER_H
#define PANEL_HANDLER_H

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

#include "Panel_adapter.h"

class PanelHandler: public Panel_adapter{

 Panel_adapter **panels;
 unsigned number_of_panels;
 
public:
    PanelHandler();
    ~PanelHandler();

};

#endif /*PANEL_HANDLER_H*/