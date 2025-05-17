#include "Side_Panel.h"

Side_Panel::Side_Panel(){
    panel=nullptr;
    buttons=nullptr;
}
Side_Panel::Side_Panel(lv_obj_t * parent_panel){
    panel=lv_obj_create(parent_panel);
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_width(panel, SIDE_PANEL_WIDTH);
    lv_obj_set_height(panel, SIDE_PANEL_HEIGHT);
    lv_obj_set_align(panel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE); 

    buttons=new image_buttons[NUMBER_OF_BUTTONS_SP];

    void *init_funcs(unsigned selector_id)[NUMBER_OF_BUTTONS_SP];
    init_funcs(unsigned selector_id)[HOME_]=home_button_init;
    init_funcs(unsigned selector_id)[BACK_]=back_button_init;
    init_funcs(unsigned selector_id)[SAVE_]=save_button_init;
    init_funcs(unsigned selector_id)[MENU_]=menu_button_init;
    init_funcs(unsigned selector_id)[POWER_]=power_button_init;
    
    for(int i=0; i<NUMBER_OF_BUTTONS; i++){
        buttons[i]->add_(panel);
        init_funcs[i](i);
        switch (i){
        case BUTTON_1:buttons[i].set_cordinator(POSITION_X,POSITION_Y_1 );break;
        case BUTTON_2:buttons[i].set_cordinator(POSITION_X,POSITION_Y_2 );break;
        case BUTTON_3:buttons[i].set_cordinator(POSITION_X,POSITION_Y_3 );break;
        case BUTTON_4:buttons[i].set_cordinator(POSITION_X,POSITION_Y_4 );break;
        case BUTTON_5:buttons[i].set_cordinator(POSITION_X,POSITION_Y_5 );break;
        default: break;
        }
        buttons[i].set_image(0);
    }
}

Side_Panel::~Side_Panel(){
    if(buttons){
        delete[] buttons;
    }
    if(panel){
        lv_obj_del(panel);
    }
}

bool Side_Panel::get_Panel_element(unsigned selector_id,image_buttons* button ){
    if(selector_id < NUMBER_OF_BUTTONS_SP){
        *button=buttons[selector_id];
        return true;
    }
    return false;
}
void Side_Panel::power_button_init(unsigned i){
    buttons[i].set_area(POWER_IMAGE_WIDTH,POWER_IMAGE_HEIGHT);
    buttons[i].add_image((uint8_t*)POWER_IMAGE);
}
void Side_Panel::back_button_init(unsigned i){
    buttons[i].set_area(BACK_IMAGE_WIDTH,BACK_IMAGE_HEIGHT);
    buttons[i].add_image((uint8_t*)BACK_IMAGE);
}
void Side_Panel::save_button_init(unsigned i){
    buttons[i].set_area(SAVE_IMAGE_WIDTH,SAVE_IMAGE_HEIGHT);
    buttons[i].add_image((uint8_t*)SAVE_IMAGE);
}
void Side_Panel::menu_button_init(unsigned i){
    buttons[i].set_area(MENU_IMAGE_WIDTH,MENU_IMAGE_HEIGHT);
    buttons[i].add_image((uint8_t*)MENU_IMAGE);
}
void Side_Panel::home_button_init(unsigned i){
    buttons[i].set_area(HOME_IMAGE_WIDTH,HOME_IMAGE_HEIGHT);
    buttons[i].add_image((uint8_t*)HOME_IMAGE);
}