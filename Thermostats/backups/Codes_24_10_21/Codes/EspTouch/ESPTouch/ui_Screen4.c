// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"

void ui_Screen4_screen_init(void)
{
ui_Screen4 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_devicePanel = lv_obj_create(ui_Screen4);
    lv_obj_set_width(ui_devicePanel, 320);
    lv_obj_set_height(ui_devicePanel, 240);
    lv_obj_clear_flag(ui_devicePanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_devicePanel, lv_color_hex(0x06053E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_devicePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BackButtonScreen4 = lv_btn_create(ui_devicePanel);
    lv_obj_set_width(ui_BackButtonScreen4, 100);
    lv_obj_set_height(ui_BackButtonScreen4, 40);
    lv_obj_set_x(ui_BackButtonScreen4, 0);
    lv_obj_set_y(ui_BackButtonScreen4, -90);
    lv_obj_set_align(ui_BackButtonScreen4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BackButtonScreen4, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BackButtonScreen4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label4 = lv_label_create(ui_BackButtonScreen4);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "Back");

    ui_Panel1 = lv_obj_create(ui_devicePanel);
    lv_obj_set_width(ui_Panel1, 312);
    lv_obj_set_height(ui_Panel1, 176);
    lv_obj_set_x(ui_Panel1, 0);
    lv_obj_set_y(ui_Panel1, 40);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_Panel1, LV_OBJ_FLAG_SCROLL_ON_FOCUS | LV_OBJ_FLAG_SCROLL_WITH_ARROW |
                    LV_OBJ_FLAG_SCROLL_ONE);     /// Flags
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x060533), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x19ACBA), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);


    lv_obj_add_event_cb(ui_BackButtonScreen4, ui_event_BackButtonScreen4, LV_EVENT_ALL, NULL);

}
