#pragma once

#include "ui_img_wifi_0_png.h"
#include "ui_img_wifi_1_png.h"
#include "ui_img_wifi_2_png.h"
#include "ui_img_wifi_3_png.h"
#include "ui_img_battery_0_png.h"
#include "ui_img_battery_1_png.h"
#include "ui_img_battery_2_png.h"

#ifndef ELEMENTS_TUNE_H
#define ELEMENTS_TUNE_H

#define BTN_WIDTH             40
#define BTN_HEIGHT            40

#define BTN_IMAGE_WIDTH       40
#define BTN_IMAGE_HEIGHT      40

#define BATTERY_IMAGE_WIDTH   80
#define BATTERY_IMAGE_HEIGHT  40

#define WIFI_IMAGE_WIDTH      64
#define WIFI_IMAGE_HEIGHT     44

#define HOME_IMAGE_WIDTH      BTN_IMAGE_WIDTH
#define HOME_IMAGE_HEIGHT     BTN_IMAGE_HEIGHT

#define BACK_IMAGE_WIDTH      BTN_IMAGE_WIDTH
#define BACK_IMAGE_HEIGHT     BTN_IMAGE_HEIGHT


#define SAVE_IMAGE_WIDTH      BTN_IMAGE_WIDTH
#define SAVE_IMAGE_HEIGHT     BTN_IMAGE_HEIGHT


#define MENU_IMAGE_WIDTH      BTN_IMAGE_WIDTH
#define MENU_IMAGE_HEIGHT     BTN_IMAGE_HEIGHT

#define POWER_IMAGE_WIDTH     BTN_IMAGE_WIDTH
#define POWER_IMAGE_HEIGHT    BTN_IMAGE_HEIGHT

#define PAGE_SELECTOR_WIDTH   BTN_IMAGE_WIDTH
#define PAGE_SELECTOR_HEIGHT  BTN_IMAGE_HEIGHTs

#define EDGE_SPACING          6
#define INTERMEDIETE_SPACING  7

#define SIDE_PANEL_WIDTH      50
#define SIDE_PANEL_HEIGHT     240
#define NUMBER_OF_BUTTONS_SP  5

#define SCREEN_WIDTH          320
#define SCREEN_HEIGHT         240

#define _PANEL_WIDTH          (unint8_t)(SCREEN_WIDTH-50)
#define _PANEL_HEIGHT         SCREEN_HEIGHT

#define BUTTON_1              0
#define BUTTON_2              1
#define BUTTON_3              2
#define BUTTON_4              3
#define BUTTON_5              4

#define POSITION_X            0
#define POSITION_Y_1          (int)(-120-(-26))
#define POSITION_Y_2          (int)(-120-(-46-7-20))
#define POSITION_Y_3          (int)(-120-(-46-7-40-7-20))
#define POSITION_Y_4          (int)(-120-(-46-7-40-7-40-7-20))
#define POSITION_Y_5          (int)(-120-(-46-7-40-7-40-7-40-7-20))


/*colors*/

#define PANEL_MAIN            0x05063E


#endif /*ELEMENTS_TUNE_H*/