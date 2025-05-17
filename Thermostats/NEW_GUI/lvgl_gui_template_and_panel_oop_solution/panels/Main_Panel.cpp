#include "Main_Panel.h"

Main_Panel::Main_Panel(/* args */){
    number_of_panels=0;
    current_panel=0;
    panels=nullptr;
    WIFI=nullptr;
    battery=nullptr;
}
Main_Panel::Main_Panel(lv_obj_t * parent){
    number_of_panels=0;
    current_panel=0;
    panels=nullptr;

    main_panel=lv_obj_create(parent);
    lv_obj_set_width( main_panel, SCREEN_WIDTH);
    lv_obj_set_height( main_panel, SCREEN_HEIGHT);
    lv_obj_set_align( main_panel, LV_ALIGN_CENTER);
    lv_obj_clear_flag( main_panel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(main_panel, lv_color_hex(PANEL_MAIN), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(main_panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    battery_img_init();
    wifi_img_init();
}

Main_Panel::~Main_Panel(){
    if(panels){
        delete[] panels;
    }
    if(main_panel){
        lv_obj_del(main_panel);
    }
}

bool Main_Panel::add_panel(Panel_adapter * panel){
    if(panel!= nullptr){
        if(panels==nullptr){
            panels=new Panel_adapter*[ number_of_panels+1];
            panels[number_of_panels]=panel;
            number_of_panels++;
        }
        else{
            Panel_adapter ** temp=new Panel_adapter*[number_of_panels+1];
            for(int i=0; i<number_of_panels; i++){
                temp[i]=panels[i];
            }
            temp[number_of_panels]=panel;
            delete[] panels;
            panels=temp;
            number_of_panels++;
        }
        return true;
    }
    return false;
}

bool Main_Panel::get_panel(unsigned *selector_id){
    unsigned id=*selector_id;
    unsigned index=*selector_id;
    id=id/DECODE;
    index=-(id*DECODE);
    switch(id){
        case PANEL_ID:   panel_handler(index)         ? continue : return false; break;
        case WIFI_ID:    wifi_image_handler(index)    ? continue : return false; break;
        case BATTERY_ID: battery_image_handler(index) ? continue : return false; break;
        default:         return nullptr;
    }
    return true;
}

void Main_Panel::battery_img_init(){
    battery= new battery_icons(main_panel);
    battery->set_coordinates(BATTERY_IMAGE_X,BATTERY_IMAGE_Y);
    battery->set_size(BATTERY_IMAGE_WIDTH, BATTERY_IMAGE_HEIGHT);
    battery->add_image(BATTERY_0_IMAGE);
    battery->add_image(BATTERY_1_IMAGE);
    battery->add_image(BATTERY_2_IMAGE);
}
void Main_Panel::wifi_img_init(){
    WIFI=new WIFI_icons(main_panel);
    WIFI->set_coordinates(WIFI_IMAGE_X, WIFI_IMAGE_Y);
    WIFI->set_size(WIFI_IMAGE_WIDTH, WIFI_IMAGE_HEIGHT);
    WIFI->add_image(WIFI_0_IMAGE);
    WIFI->add_image(WIFI_1_IMAGE);
    WIFI->add_image(WIFI_2_IMAGE);
    WIFI->add_image(WIFI_3_IMAGE);;
}

bool Main_Panel::panel_handler(unsigned index){
    if(index<number_of_panels){
        for(unsigned i=0; i<number_of_panels; i++){
            if(index!=i){
                panels[i]->flag_for_hide_element(true);
            }
            else{
                panels[i]->flag_for_hide_element(false);
            }
        }
        return true;
    }
    return false;
}
bool Main_Panel::wifi_image_handler(unsigned index){
    return WIFI->set_picture(&index);
}
bool Main_Panel::battery_image_handler(unsigned index){
    return battery->set_picture(&index);
}