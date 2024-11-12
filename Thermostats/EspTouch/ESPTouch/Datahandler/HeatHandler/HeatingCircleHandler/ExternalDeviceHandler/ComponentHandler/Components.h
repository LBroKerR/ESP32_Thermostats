#pragma once
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "lvgl.h"
#include "ui.h"
#include "ui_helpers.h"
#include <Arduino.h>

class Components{
    //panels
 lv_obj_t * ui_Device_Template;

 lv_obj_t * ui_Device_TemplateMAC;
 lv_obj_t * ui_Device_TemplateName;
 lv_obj_t * ui_Temp_template;
 float temp;
 unsigned ID;
 String IP;


public:
    Components();
    ~Components();
    void fillout(String Mac, String Name, float temp, int y_pos, unsigned id);
    void updata_temp(float temp);
    void updata_pos(int pos);
    String getMac()const;
    unsigned getID();
    float getTemp();

    void set_ip(String);
    String get_ip()const;

};
#endif //COMPONENTS_H