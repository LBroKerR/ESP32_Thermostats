// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"

// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_mainPanel;
extern lv_obj_t * ui_WtmpARC;
extern lv_obj_t * ui_WtmpLabel;
extern lv_obj_t * ui_TmpLabel;
extern lv_obj_t * ui_HmdLabel;
extern lv_obj_t * ui_buttonpanel;
void ui_event_HeatButton(lv_event_t * e);
extern lv_obj_t * ui_HeatButton;
extern lv_obj_t * ui_Label10;
void ui_event_ProgButton(lv_event_t * e);
extern lv_obj_t * ui_ProgButton;
extern lv_obj_t * ui_ProgLabel;
extern lv_obj_t * ui_wifiLabel;
extern lv_obj_t * ui_TimeLabel;
extern lv_obj_t * ui_AutoManual;
extern lv_obj_t * ui_Label1;
// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
extern lv_obj_t * ui_Screen2;
extern lv_obj_t * ui_ProgPanel;
void ui_event_wtmpSLider(lv_event_t * e);
extern lv_obj_t * ui_wtmpSLider;
extern lv_obj_t * ui_ProgTmpLabel;
void ui_event_Button3(lv_event_t * e);
extern lv_obj_t * ui_Button3;
extern lv_obj_t * ui_Label15;
extern lv_obj_t * ui_Roller1;
extern lv_obj_t * ui_Roller2;
extern lv_obj_t * ui_TmpChart;
extern lv_obj_t * ui_WTMPSliderLable;
void ui_event_SaveButton(lv_event_t * e);
extern lv_obj_t * ui_SaveButton;
extern lv_obj_t * ui_Label2;
void ui_event_SaveBool(lv_event_t * e);
extern lv_obj_t * ui_SaveBool;
// SCREEN: ui_Screen3
void ui_Screen3_screen_init(void);
extern lv_obj_t * ui_Screen3;
extern lv_obj_t * ui_HeatPanel;
void ui_event_Back2Button(lv_event_t * e);
extern lv_obj_t * ui_Back2Button;
extern lv_obj_t * ui_Back2Label;
void ui_event_HeatSetting(lv_event_t * e);
extern lv_obj_t * ui_HeatSetting;
extern lv_obj_t * ui_HeatScreenLabel;
void ui_event_ConnectedDeviceButton(lv_event_t * e);
extern lv_obj_t * ui_ConnectedDeviceButton;
extern lv_obj_t * ui_Label3;
void ui_event_BIOS(lv_event_t * e);
extern lv_obj_t * ui_BIOS;
extern lv_obj_t * ui_BIOSLabel;
extern lv_obj_t * ui_BiosBool;
// SCREEN: ui_Screen4
void ui_Screen4_screen_init(void);
extern lv_obj_t * ui_Screen4;
extern lv_obj_t * ui_devicePanel;
extern lv_obj_t * ui_Panel1;
extern lv_obj_t * ui_DeviceTemplate1;
extern lv_obj_t * ui_DeviceTemplateMAC1;
extern lv_obj_t * ui_DeviceTemplateName1;
extern lv_obj_t * ui_Temptemplate1;
extern lv_obj_t * ui_CeliusLabel1;
void ui_event_BackButtonScreen4(lv_event_t * e);
extern lv_obj_t * ui_BackButtonScreen4;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui____initial_actions0;
extern lv_obj_t * ui_Screen_Number;
// SCREEN: ui_Screen5
void ui_Screen5_screen_init(void);
extern lv_obj_t * ui_Screen5;
void ui_event_Panel2(lv_event_t * e);
extern lv_obj_t * ui_Panel2;
extern lv_obj_t * ui____initial_actions0;







void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
