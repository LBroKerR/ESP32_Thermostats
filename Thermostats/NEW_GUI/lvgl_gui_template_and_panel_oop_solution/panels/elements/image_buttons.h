#pragma once
#ifndef IMAGE_BUTTONS_H
#define IMAGE_BUTTONS_H

#include "lvgl.h"

class image_buttons{
    lv_obj_t * button;
    uint8_t** image;
    uint8_t number_of_images;
    const lv_img_dsc_t *obj_image;
    bool button_action;
public:

    image_buttons();
    ~image_buttons();

    void add_(lv_obj_t * parent_panel);
    void set_cordinator(int x, int y);
    void set_area(unsigned width, unsigned height);
    void add_image( uint8_t *image);
    void set_image( unsigned index);

    void get_action(bool* event);

    void event(lv_event_t* event);
};
#endif /*IMAGE_BUTTONS_H*/
/*
  lv_obj_create
  width, height
  x,y pose
  align
  flag add, clear

   //Image data from image.png 
LV_IMG_DECLARE(my_image);  // csak ha külön .c és .h fájlban lenne

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST uint8_t my_image_map[] = {
  0xff, 0xff, 0xff, 0xff,   //pixel 1 RGBA 
  0x00, 0x00, 0x00, 0xff,  // pixel 2 RGBA 
  // ... (további pixelek)
};
*/