#include "Main_Panel.h"

Main_Panel::Main_Panel(/* args */){
    number_of_panels=0;
    panels=nullptr;

    panel_selctor=new Side_Panel(main_panel);
    main_panel=lv_obj_create(NULL);
}
Main_Panel::Main_Panel(lv_obj_t * screen){
    number_of_panels=0;
    panels=nullptr;
    
    panel_selctor=new Side_Panel(main_panel);

    main_panel=lv_obj_create(screen);
    lv_obj_set_width( main_panel, SCREEN_WIDTH);
    lv_obj_set_height( main_panel, SCREEN_HEIGHT);
    lv_obj_set_align( main_panel, LV_ALIGN_CENTER);
    lv_obj_clear_flag( main_panel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(main_panel, lv_color_hex(PANEL_MAIN), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(main_panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
}

Main_Panel::~Main_Panel(){
    if(panels){
        delete[] panels;
    }
    if(panel_selctor){
        delete panel_selctor;
    }
    if(main_panel){
        lv_obj_del(main_panel);
    }
}

bool add_panel(Panel_adapter * panel){
    if(panel!= nullptr){
        if(panels==nullptr){
            panels=new Panel_adapter*[1];
            panels[0]=panel;
            number_of_panels=1;
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

Panel_adapter * get_panel(unsigned selector_id){
    if(selector_id < number_of_panels){
        return panels[selector_id];
    }
    return nullptr;
}