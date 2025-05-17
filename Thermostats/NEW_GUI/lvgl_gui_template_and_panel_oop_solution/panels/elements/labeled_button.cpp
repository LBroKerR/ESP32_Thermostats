#include "labeled_button.h"

labeled_button::labeled_button(){
    button = nullptr;
    label = nullptr;
    button_action = false;
}
labeled_button::~labeled_button(){
    if(button){
        lv_obj_del(button);
    }
    if(label){
        lv_obj_del(label);
    }
}

void labeled_button::add_(lv_obj_t * parent_panel){
    button = lv_btn_create(parent_panel);
    label = lv_label_create(button);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_radius(button, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(button, labeled_button::event, LV_EVENT_ALL, NULL);
}
void labeled_button::set_cordinator(int x, int y){
    lv_obj_set_x(button, x);
    lv_obj_set_y(button, y);
}
void labeled_button::set_area(unsigned width, unsigned height,int colour){
    lv_obj_set_width(button, width);
    lv_obj_set_height(button, height);
    lv_obj_set_style_bg_color(button, lv_color_hex(colour), LV_PART_MAIN | LV_STATE_DEFAULT);
}
void labeled_button::set_label(const char* label_text, int colour, int font_size){
    lv_label_set_text(label, label_text);
    lv_obj_set_style_text_color(label, lv_color_hex(colour), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label, font_size, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void labeled_button::set_action(bool const event){
    button_action = event;
}
void labeled_button::get_action(bool* event){
    *event = button_action;
    button_action = false; // Reset action after getting it
}

void labeled_button::event(lv_event_t* event){
    lv_event_code_t event_code = lv_event_get_code(event);
    lv_obj_t * target = lv_event_get_target(event);
    if(event_code == LV_EVENT_PRESSED) {
        button_action = true;
    }
}