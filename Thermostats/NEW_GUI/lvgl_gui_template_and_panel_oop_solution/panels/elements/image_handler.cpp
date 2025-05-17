#include "image_handler.h"

images_handler::images_handler(){
    images=nullptr;
    number_of_images=0;
    current_image=0;
    obj_image.header.always_zero = 0;
    obj_image.header.cf=LV_IMG_CF_TRUE_COLOR_ALPHA;
    image=nullptr;
}
images_handler::images_handler(unsigned w, unsigned h){
    images=nullptr;
    number_of_images=0;
    current_image=0;
    
    image = lv_img_create(parent_panel);
    lv_img_set_src(image, &obj_image);
    lv_obj_set_align(image, LV_ALIGN_CENTER);
    lv_obj_add_flag(image, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(image, LV_OBJ_FLAG_SCROLLABLE);  

    obj_image.header.always_zero = 0;
    obj_image.header.w=w;
    obj_image.header.h=h;
    obj_image.header.cf=LV_IMG_CF_TRUE_COLOR_ALPHA;

}
images_handler::~images_handler(){
    if(obj_image){
        lv_obj_del(obj_image);
    }
    if(image){
        lv_obj_del(image);
    }
    if(images!=nullptr){
        delete[] images;
    }
}

void images_handler::add_image(uint8_t* image){
    if(images==nullptr){
        number_of_images++;
        images=new uint8_t*[number_of_images];
        *images=image;
    }
    else{
        uint8_t **tmp=new uint8_t*[number_of_images+1];
        for (unsigned i = 0; i < number_of_images; i++){
            tmp[i]=images[i];
        }
        tmp[number_of_images]=image;
        delete[] images;
        images=tmp;
        number_of_images++;
    }
}
void images_handler::set_size(unsigned w, unsigned h){
    obj_image.header.w=w;
    obj_image.header.h=h;
    lv_obj_set_width(image, w);
    lv_obj_set_height(image, h);
}

void images_handler::set_coordinates(int x, int y){
    lv_obj_set_x(image, x);
    lv_obj_set_y(image, y);
}

bool images_handler::get_Panel_element(unsigned*index){
    unsigned elem=*index;
    if(elem < number_of_images && elem!= current_image){
        obj_image.data_size = sizeof(images[elem]);
        obj_image.data=images[elem];
        current_image=elem;
        return true;
    }
    return false;
}