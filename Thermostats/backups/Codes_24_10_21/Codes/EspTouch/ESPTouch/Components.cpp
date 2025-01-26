#include "Components.h"

Components::Components(){

}
Components::~Components(){
 lv_obj_del(ui_Device_TemplateMAC);
 lv_obj_del(ui_Device_TemplateName);
 lv_obj_del(ui_Temp_template);
 lv_obj_del(ui_Device_Template);
}

void Components::fillout(String Mac, String Name, float Temp, int y_pos, unsigned id){

    ui_Device_Template = lv_obj_create(ui_Panel1);
    lv_obj_set_width(ui_Device_Template, 280);
    lv_obj_set_height(ui_Device_Template, 50);
    lv_obj_set_x(ui_Device_Template, 0);
    lv_obj_set_y(ui_Device_Template, y_pos);
    lv_obj_set_align(ui_Device_Template, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_Device_Template, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Device_TemplateMAC = lv_label_create(ui_Device_Template);
    lv_obj_set_width(ui_Device_TemplateMAC, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Device_TemplateMAC, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Device_TemplateMAC, -70);
    lv_obj_set_y(ui_Device_TemplateMAC, 10);
    lv_obj_set_align(ui_Device_TemplateMAC,LV_ALIGN_CENTER);
    lv_label_set_text(ui_Device_TemplateMAC, Mac.c_str());

    ui_Device_TemplateName = lv_label_create(ui_Device_Template);
    lv_obj_set_width(ui_Device_TemplateName, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Device_TemplateName, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Device_TemplateName, -70);
    lv_obj_set_y(ui_Device_TemplateName, -10);
    lv_obj_set_align(ui_Device_TemplateName, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Device_TemplateName, Name.c_str());

    ui_Temp_template = lv_label_create(ui_Device_Template);
    lv_obj_set_width(ui_Temp_template, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Temp_template, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Temp_template, 80);
    lv_obj_set_y(ui_Temp_template, 0);
    lv_obj_set_align(ui_Temp_template, LV_ALIGN_CENTER);
    String temp=String(Temp,1)+" °C";
    lv_label_set_text(ui_Temp_template, temp.c_str());
    lv_obj_set_style_text_font(ui_Temp_template, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    temp=Temp;
    ID=id;
}

void  Components::updata_temp(float Temp){
    temp=Temp;
    String strTemp=String(temp,1)+" °C";
    lv_label_set_text(ui_Temp_template, strTemp.c_str());
}
void  Components::updata_pos(int pos){
    lv_obj_set_y(ui_Device_Template, pos);
}
void Components::setClient(WiFiClient Client){
    client=Client;
 }
WiFiClient Components::getClient(){
    return client;
}
String Components::getMac()const{
    return String(lv_label_get_text( ui_Device_TemplateMAC));
}
unsigned Components::getID(){
    return ID;
}
float Components::getTemp(){
    return temp;
}