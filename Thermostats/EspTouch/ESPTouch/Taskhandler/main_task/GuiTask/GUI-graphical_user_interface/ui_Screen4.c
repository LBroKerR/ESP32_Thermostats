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

    /*ui_DeviceTemplate1 = lv_obj_create(ui_Panel1);
    lv_obj_set_width(ui_DeviceTemplate1, 280);
    lv_obj_set_height(ui_DeviceTemplate1, 50);
    lv_obj_set_x(ui_DeviceTemplate1, -3);
    lv_obj_set_y(ui_DeviceTemplate1, 0);
    lv_obj_set_align(ui_DeviceTemplate1, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_DeviceTemplate1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_DeviceTemplateMAC1 = lv_label_create(ui_DeviceTemplate1);
    lv_obj_set_width(ui_DeviceTemplateMAC1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DeviceTemplateMAC1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DeviceTemplateMAC1, -63);
    lv_obj_set_y(ui_DeviceTemplateMAC1, 11);
    lv_obj_set_align(ui_DeviceTemplateMAC1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DeviceTemplateMAC1, "3A:34:52:C4:69:B8");

    ui_DeviceTemplateName1 = lv_label_create(ui_DeviceTemplate1);
    lv_obj_set_width(ui_DeviceTemplateName1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DeviceTemplateName1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DeviceTemplateName1, -70);
    lv_obj_set_y(ui_DeviceTemplateName1, -10);
    lv_obj_set_align(ui_DeviceTemplateName1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DeviceTemplateName1, "BedRoom");

    ui_Temptemplate1 = lv_label_create(ui_DeviceTemplate1);
    lv_obj_set_width(ui_Temptemplate1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Temptemplate1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Temptemplate1, 80);
    lv_obj_set_y(ui_Temptemplate1, 0);
    lv_obj_set_align(ui_Temptemplate1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Temptemplate1, "20.0");
    lv_obj_set_style_text_font(ui_Temptemplate1, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CeliusLabel1 = lv_label_create(ui_DeviceTemplate1);
    lv_obj_set_width(ui_CeliusLabel1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CeliusLabel1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CeliusLabel1, 115);
    lv_obj_set_y(ui_CeliusLabel1, 0);
    lv_obj_set_align(ui_CeliusLabel1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CeliusLabel1, "°C");
    lv_obj_set_style_text_font(ui_CeliusLabel1, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DeviceTemplate2 = lv_obj_create(ui_Panel1);
    lv_obj_set_width(ui_DeviceTemplate2, 280);
    lv_obj_set_height(ui_DeviceTemplate2, 50);
    lv_obj_set_x(ui_DeviceTemplate2, -4);
    lv_obj_set_y(ui_DeviceTemplate2, 58);
    lv_obj_set_align(ui_DeviceTemplate2, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_DeviceTemplate2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_DeviceTemplateMAC2 = lv_label_create(ui_DeviceTemplate2);
    lv_obj_set_width(ui_DeviceTemplateMAC2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DeviceTemplateMAC2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DeviceTemplateMAC2, -70);
    lv_obj_set_y(ui_DeviceTemplateMAC2, 10);
    lv_obj_set_align(ui_DeviceTemplateMAC2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DeviceTemplateMAC2, "3A:34:52:C4:69:B8");

    ui_DeviceTemplateName2 = lv_label_create(ui_DeviceTemplate2);
    lv_obj_set_width(ui_DeviceTemplateName2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DeviceTemplateName2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DeviceTemplateName2, -70);
    lv_obj_set_y(ui_DeviceTemplateName2, -10);
    lv_obj_set_align(ui_DeviceTemplateName2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DeviceTemplateName2, "BedRoom");

    ui_Temptemplate2 = lv_label_create(ui_DeviceTemplate2);
    lv_obj_set_width(ui_Temptemplate2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Temptemplate2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Temptemplate2, 80);
    lv_obj_set_y(ui_Temptemplate2, 0);
    lv_obj_set_align(ui_Temptemplate2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Temptemplate2, "20.0");
    lv_obj_set_style_text_font(ui_Temptemplate2, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CeliusLabel2 = lv_label_create(ui_DeviceTemplate2);
    lv_obj_set_width(ui_CeliusLabel2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CeliusLabel2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CeliusLabel2, 115);
    lv_obj_set_y(ui_CeliusLabel2, 0);
    lv_obj_set_align(ui_CeliusLabel2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CeliusLabel2, "°C");
    lv_obj_set_style_text_font(ui_CeliusLabel2, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DeviceTemplate3 = lv_obj_create(ui_Panel1);
    lv_obj_set_width(ui_DeviceTemplate3, 280);
    lv_obj_set_height(ui_DeviceTemplate3, 50);
    lv_obj_set_x(ui_DeviceTemplate3, -5);
    lv_obj_set_y(ui_DeviceTemplate3, 116);
    lv_obj_set_align(ui_DeviceTemplate3, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_DeviceTemplate3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_DeviceTemplateMAC3 = lv_label_create(ui_DeviceTemplate3);
    lv_obj_set_width(ui_DeviceTemplateMAC3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DeviceTemplateMAC3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DeviceTemplateMAC3, -70);
    lv_obj_set_y(ui_DeviceTemplateMAC3, 10);
    lv_obj_set_align(ui_DeviceTemplateMAC3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DeviceTemplateMAC3, "3A:34:52:C4:69:B8");

    ui_DeviceTemplateName3 = lv_label_create(ui_DeviceTemplate3);
    lv_obj_set_width(ui_DeviceTemplateName3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DeviceTemplateName3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DeviceTemplateName3, -70);
    lv_obj_set_y(ui_DeviceTemplateName3, -10);
    lv_obj_set_align(ui_DeviceTemplateName3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DeviceTemplateName3, "BedRoom");

    ui_Temptemplate3 = lv_label_create(ui_DeviceTemplate3);
    lv_obj_set_width(ui_Temptemplate3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Temptemplate3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Temptemplate3, 80);
    lv_obj_set_y(ui_Temptemplate3, 0);
    lv_obj_set_align(ui_Temptemplate3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Temptemplate3, "20.0");
    lv_obj_set_style_text_font(ui_Temptemplate3, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CeliusLabel3 = lv_label_create(ui_DeviceTemplate3);
    lv_obj_set_width(ui_CeliusLabel3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CeliusLabel3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CeliusLabel3, 115);
    lv_obj_set_y(ui_CeliusLabel3, 0);
    lv_obj_set_align(ui_CeliusLabel3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CeliusLabel3, "°C");
    lv_obj_set_style_text_font(ui_CeliusLabel3, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DeviceTemplate4 = lv_obj_create(ui_Panel1);
    lv_obj_set_width(ui_DeviceTemplate4, 280);
    lv_obj_set_height(ui_DeviceTemplate4, 50);
    lv_obj_set_x(ui_DeviceTemplate4, -5);
    lv_obj_set_y(ui_DeviceTemplate4, 170);
    lv_obj_set_align(ui_DeviceTemplate4, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_DeviceTemplate4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_DeviceTemplateMAC4 = lv_label_create(ui_DeviceTemplate4);
    lv_obj_set_width(ui_DeviceTemplateMAC4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DeviceTemplateMAC4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DeviceTemplateMAC4, -70);
    lv_obj_set_y(ui_DeviceTemplateMAC4, 10);
    lv_obj_set_align(ui_DeviceTemplateMAC4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DeviceTemplateMAC4, "3A:34:52:C4:69:B8");

    ui_DeviceTemplateName4 = lv_label_create(ui_DeviceTemplate4);
    lv_obj_set_width(ui_DeviceTemplateName4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DeviceTemplateName4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DeviceTemplateName4, -70);
    lv_obj_set_y(ui_DeviceTemplateName4, -10);
    lv_obj_set_align(ui_DeviceTemplateName4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DeviceTemplateName4, "BedRoom");

    ui_Temptemplate4 = lv_label_create(ui_DeviceTemplate4);
    lv_obj_set_width(ui_Temptemplate4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Temptemplate4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Temptemplate4, 80);
    lv_obj_set_y(ui_Temptemplate4, 0);
    lv_obj_set_align(ui_Temptemplate4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Temptemplate4, "20.0");
    lv_obj_set_style_text_font(ui_Temptemplate4, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CeliusLabel4 = lv_label_create(ui_DeviceTemplate4);
    lv_obj_set_width(ui_CeliusLabel4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CeliusLabel4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CeliusLabel4, 115);
    lv_obj_set_y(ui_CeliusLabel4, 0);
    lv_obj_set_align(ui_CeliusLabel4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CeliusLabel4, "°C");
    lv_obj_set_style_text_font(ui_CeliusLabel4, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);*/

    lv_obj_add_event_cb(ui_BackButtonScreen4, ui_event_BackButtonScreen4, LV_EVENT_ALL, NULL);

}
