#include "image_buttons.h"


image_buttons::image_buttons(){
    button=nullptr;
    obj_image=nullptr;
    button_action=false;
}
image_buttons::~image_buttons(){
    if(button){
        lv_obj_del(button);
    }
    if(image){
        lv_obj_del(image);
    }
    if(obj_image){
        lv_obj_del(obj_image);
    }
    if(image!=nullptr){
        delete[] image;
    }
}

void image_buttons::add_(lv_obj_t* parent_panel){
    button=lv_imgbtn_create(parent_panel);
    lv_obj_set_align(button, LV_ALIGN_CENTER);
    lv_obj_add_event_cb(button,image_buttons::event , LV_EVENT_ALL, nullptr);
}
void image_buttons::set_cordinator(int x, int y){
    lv_obj_set_x(button,x);
    lv_obj_set_y(button,y);
}
void image_buttons::set_area(unsigned width, unsigned height){
    lv_obj_set_width(button, width);
    lv_obj_set_height(button, height);
    obj_image.header.always_zero=0;
    obj_image.header.w=width;
    obj_image.header.h=height;
    obj_image.header.cf=LV_IMG_CF_TRUE_COLOR_ALPHA;
    
}
void image_buttons::set_image( unsigned index){
    if(index>=number_of_images){
        return;
    }
    obj_image.data_size=sizeof(image);
    obj_image.header.cf=LV_IMG_CF_TRUE_COLOR_ALPHA;
    obj_image.data=image[index];
    lv_imgbtn_set_src( button, LV_IMGBTN_STATE_RELEASED, NULL, &obj_image, NULL);
}

void image_buttons::add_image( uint8_t *image){
    if(image!=nullptr){
        number_of_images++;
        uint8_t** new_image=new uint8_t*[number_of_images];
        for(int i=0; i<number_of_images-1; i++){
            new_image[i]=image[i];
        }
        new_image[number_of_images-1]=image;
        delete[] this->image;
        this->image=new_image;
    }
}

void image_buttons::get_action(bool* event){
    *event=button_action;
    button_action=false;
}

void image_buttons::event(lv_event_t* event){
    lv_event_code_t event_code = lv_event_get_code(event);
    lv_obj_t * target = lv_event_get_target(event);
    if(event_code == LV_EVENT_PRESSED) {
        button_action=true;
    }
}