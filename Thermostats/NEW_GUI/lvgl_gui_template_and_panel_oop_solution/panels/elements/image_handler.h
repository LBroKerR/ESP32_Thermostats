#pragma once
#ifndef IMAGES_HANDLER_H
#define IMAGES_HANDLER_H

#include "lvgl.h"
#include "Panel_adapter.h"

#include "elements_tune.h"


class images_handler: public Panel_adapter{
    uint8_t** images;
    unsigned number_of_images;
    unsigned current_image;
    const lv_img_dsc_t *obj_image;

    lv_obj_t * image;

public:
    images_handler();
    images_handler(lv_obj_t * parent_panel);
    ~images_handler();

    void add_image(uint8_t* image);
    void set_size(unsigned w, unsigned h);
    void set_coordinates(int x, int y);

    bool set_picture(unsigned*index);
};
#endif