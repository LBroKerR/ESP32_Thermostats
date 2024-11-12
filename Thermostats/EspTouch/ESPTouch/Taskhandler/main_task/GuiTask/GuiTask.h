#pragma once
#ifndef GUITASK_H
#define GUITASK_H

#include <TFT_eSPI.h>
#include <Arduino.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include "MainTask.h"
#include "DataHandler.h"
#define USE_UI 1   

#define Display_28 // depending on your board
#include <lvgl.h>

#ifdef USE_UI
#include "ui.h"
#endif
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

#define BACKLIGHT_PIN 21

#if defined Display_35
static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;
extern uint16_t calData[5]; // Declare global variable
#elif defined Display_24
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;
extern uint16_t calData[5];
#elif defined Display_28
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;
extern uint16_t calData[5];
#endif

extern TFT_eSPI lcd; // Declare global variable
extern SPIClass *mySpi; // Declare global variable
extern XPT2046_Touchscreen ts; // Declare global variable

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[ screenWidth * screenHeight / 13 ];

extern uint16_t touchX; // Declare global variable
extern uint16_t touchY; // Declare global variable
extern bool Turn_ON_OFF;
extern bool status;

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
void Gui_init();
void is_user_interacted(DataHandler* data, unsigned *);
bool changeTask(MainTask* screens,DataHandler* data, lv_chart_series_t * ui_TmpChart_series_1,String *screen_number);
void GuiTask_main(MainTask* screens, DataHandler* data);

#endif // GUITASK_H