// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t * ui_Screen1;

lv_obj_t * ui_MainPanel;
lv_obj_t * ui_Wifiimage;
lv_obj_t * ui_BatteryImage;
lv_obj_t * ui_ButteryLabel;

lv_obj_t * ui_SidePanel;
lv_obj_t * ui_Home;
lv_obj_t * ui_Back;
lv_obj_t * ui_Save;
lv_obj_t * ui_Menu;
lv_obj_t * ui_Switch;

lv_obj_t * ui_FunctionPanel;

lv_obj_t * ui_Button1;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Button2;
lv_obj_t * ui_Image8;
lv_obj_t * ui_Panel4;
lv_obj_t * ui_Label3;

void ui_event_TextArea1(lv_event_t * e);
lv_obj_t * ui_TextArea1;
lv_obj_t * ui_Keyboard2;
lv_obj_t * ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 32
    #error "LV_COLOR_DEPTH should be 32bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_TextArea1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED) {
        _ui_keyboard_set_target(ui_Keyboard2,  ui_TextArea1);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}
