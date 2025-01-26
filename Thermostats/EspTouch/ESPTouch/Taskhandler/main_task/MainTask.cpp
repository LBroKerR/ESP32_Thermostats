#include "MainTask.h"

//private:

void MainTask::update_wtmp(DataHandler*data){
  String tmp;
    // wanted temp, and acr!
    // if espcarryable change value, or arc-> manual. dont send value
    //if arc modify value or hour change-> send data to carryable
    //if hour change-> auto!
  unsigned hour=0, proghour_tmp=0;
  float wtmp=0.0;

  data->getProg()->get_ProgHour_index(&proghour_tmp);
  data->getTime()->gethour(&hour);
  if(auto_flag || proghour_tmp!=hour){//auto
    data->getProg()->set_ProgHour_index(hour);
    data->getProg()->set_Wanted_temp(data->getProg()->get_program_element(hour));
    lv_arc_set_value(ui_WtmpARC,(data->getProg()->get_program_element(hour)*10.0));
    lv_label_set_text(ui_AutoManual, "Auto");
    auto_flag=false;
  }
  (data->getProg()->get_Wanted_temp(&wtmp));
  if(wtmp!=(float)((lv_arc_get_value(ui_WtmpARC))/10.0) && !data->getProg()->get_wtmp_changed()){//manual
    data->getProg()->set_Wanted_temp((float)(lv_arc_get_value(ui_WtmpARC))/10.0);
    lv_label_set_text(ui_AutoManual, "Manual");
  }
  if(data->getProg()->get_wtmp_changed()){
    data->getProg()->get_Wanted_temp(&wtmp);
    lv_arc_set_value(ui_WtmpARC,(wtmp*10.0));
    lv_label_set_text(ui_AutoManual, "Manual");
    data->getProg()->set_wtmp_changed(false);
  }
  data->getProg()->get_Wanted_temp(&wtmp);
    tmp=String(wtmp,1)+" °C";
    lv_label_set_text(ui_WtmpLabel,tmp.c_str());
}

void MainTask::upgrade_Screen1(DataHandler*data){// temp, wtemp, hmd, clock, wifi, heat switch
  String tmp;
  update_wtmp(data);

  unsigned tmp_uvar=0;
  float tmp_fvar=0.0;
  bool tmp_bvar=false;
  //DHT sensor
  data->getHeater()->getHeatingCircleHandler()[getSensorLocation()].getSensor()->getMeasuredTemperature(&tmp_fvar);
  tmp=String(tmp_fvar,1)+" °C";
  lv_label_set_text(ui_TmpLabel, tmp.c_str());

  data->getHeater()->getHeatingCircleHandler()[getSensorLocation()].getSensor()->getMeasureHmd(&tmp_uvar);
  tmp=String(tmp_uvar)+" %";
  lv_label_set_text(ui_HmdLabel, tmp.c_str());

  data->getTime()->gethour(&tmp_uvar);
  if(tmp_uvar<10){
  //rtc clock 
    tmp="0"+String(tmp_uvar);
  }
  else{
    tmp=String(tmp_uvar);
  }
  tmp+=":";
  data->getTime()->getmin(&tmp_uvar);
  if(tmp_uvar<10){
    tmp+="0"+String(tmp_uvar);
  }
  else{
    tmp+=String(tmp_uvar);
  }
  lv_label_set_text(ui_TimeLabel, tmp.c_str());

  //wtmp

  update_wtmp(data);

  // ON/OFF set;
  data->getHeater()->getStatus()[sensor_location].get_variable(&tmp_bvar);
  if(tmp_bvar){
    lv_label_set_text(ui_Label1, "ON");
  }
  else{
    lv_label_set_text(ui_Label1, "OFF");
  }
  //wifi
  if(data->get_wifi_data()->get_switch()){
    tmp=data->get_wifi_data()->get_ip();
      lv_label_set_text(ui_wifiLabel, tmp.c_str());
  }
}
    // if roller change-> send to clients, set into database, return true
  //if progindex changed by espcarryable then set roller. set bool flag that show the prog index chagned is changeds
bool MainTask::update_progindex_roller(DataHandler*data){
  bool output=false;
  unsigned prog_index=0;
  data->getProg()->get_active_program_index(&prog_index);
  if(data->getProg()->get_active_program_index_changed() && prog_index!=lv_roller_get_selected(ui_Roller1)){
    //setting gui with the receive progindex from espcarryable
    lv_roller_set_selected(ui_Roller1, (uint16_t) prog_index, LV_ANIM_OFF);
    output=true;
  }
  if(prog_index!=lv_roller_get_selected(ui_Roller1) && !data->getProg()->get_active_program_index_changed()){
    //user interaction
    // set server_prog_index to true
    //set prog_index_changed to true
    //set prog_index value 
    //return true
    data->getProg()->set_active_program_index_changed(true);
    data->getProg()->set_active_program_index(lv_roller_get_selected(ui_Roller1));
    data->getProg()->set_server_update_prog_index(true);
    output=true;
  }
  return output;
}
bool MainTask::update_proghour_roller(DataHandler*data){
  //if prog index changed-> set slider, set text return true
  //if roller changed-> set slider, set text, set database proghour index. retunr true;
  int ProgHourIndex=lv_roller_get_selected(ui_Roller2);
  unsigned prog_hour_tmp=0, hour=0;
  String str;
  data->getProg()->get_ProgHour_index(&prog_hour_tmp);
  data->getTime()->gethour(&hour);

  if(data->getProg()->get_active_program_index_changed()){
    lv_slider_set_value(ui_wtmpSLider, (int32_t)(data->getProg()->get_program_element()*10.0), LV_ANIM_OFF);
   // str=String(data->getProg()->get_program_element(),1)+" °C";
    //lv_label_set_text(ui_WTMPSliderLable, str.c_str());
    data->getProg()->set_active_program_index_changed(false);
    return true;
  }
  else if(prog_hour_tmp!=ProgHourIndex){
    data->getProg()->set_ProgHour_index(ProgHourIndex);
    return true;
  }
  else if(hour==ProgHourIndex){
    auto_flag=true;
  }
  return false;
}

bool MainTask::update_progindex_slider(DataHandler* data){
  int sliderVaule=lv_slider_get_value(ui_wtmpSLider);
  String str;
  if(data->getProg()->get_ProgHour_index_changed()){
    lv_slider_set_value(ui_wtmpSLider, (int32_t)(data->getProg()->get_program_element()*10.0), LV_ANIM_OFF);
    data->getProg()->set_ProgHour_index_changed(false);
  }
  else{ 
    data->getProg()->set_program_element((float)sliderVaule/10.0);
  }
  str=String(data->getProg()->get_program_element(),1)+" °C";
  lv_label_set_text(ui_WTMPSliderLable, str.c_str());
  return true;
}
void MainTask::upgrade_Screen2(DataHandler*data, lv_chart_series_t * ui_TmpChart_series_1){//prog -> active prog, chart, slider

 bool update_index=update_progindex_roller(data);
 bool update_hour=update_proghour_roller(data);
 bool update_hour_temp_value=update_progindex_slider(data);
  if(update_index || update_hour || update_hour_temp_value){
    static lv_coord_t array[24];
    for(unsigned i=0; i<SIZE; i++){
      array[i]=(lv_coord_t)((int)(data->getProg()->get_program_element(i)*10.0));
    }
    lv_chart_set_ext_y_array(ui_TmpChart, ui_TmpChart_series_1, array);// chart printing
  }
}
void MainTask::upgrade_Screen3(DataHandler*data){//options -> heating mode
  bool tmp=false;
  data->getHeater()->getHeatingMode(&tmp);
  if(tmp!= (bool)lv_dropdown_get_selected(ui_HeatSetting)){
    data->getHeater()->setHeatingMode((bool)lv_dropdown_get_selected(ui_HeatSetting));
  }
}
void MainTask::upgrade_Screen4(DataHandler*data){//external devices -> dynamic deviceses components!
  unsigned size=0;
  String str=" ";
  unsigned pos=0;//+(number_of_comp*55)
  for(unsigned i=0; i<data->getHeater()->get_number_of_HeatingCircles(); i++){
    if(data->getHeater()->getHeatingCircleHandler()[i].getDevices()!=nullptr){
      if(data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getDevices()!=nullptr && data->getHeater()->getHeatingCircleHandler()[i].getDevices()->get_changed()){
        for(unsigned k=0; k<data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getSize() ;k++){
          data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getDevices()[k].updata_pos(pos);
          pos+=55;
        }
      }
    }
  }
}

void MainTask::init_screens_datas(DataHandler*data,lv_chart_series_t * ui_TmpChart_series_1){
   String tmp;
   float wtmp_tmp=0.0, measured_temp_tmp=0.0;
   unsigned hmd_tmp=0, hour=0, min=0, prog_index=0, prog_hour=0;
   bool mode=false;
  //screen1 home
  lv_label_set_text(ui_wifiLabel, "Offline");
  lv_label_set_text(ui_AutoManual, "Auto");
  data->getProg()->get_Wanted_temp(&wtmp_tmp);
  tmp=String(wtmp_tmp,1)+" °C";
  lv_label_set_text(ui_WtmpLabel, tmp.c_str());
  lv_arc_set_value(ui_WtmpARC,(wtmp_tmp*10.0));
  data->getHeater()->getHeatingCircleHandler()[getSensorLocation()].getSensor()->getMeasuredTemperature(&measured_temp_tmp);
  tmp=String(measured_temp_tmp,1)+" °C";
  lv_label_set_text(ui_TmpLabel, tmp.c_str());
  data->getHeater()->getHeatingCircleHandler()[getSensorLocation()].getSensor()->getMeasureHmd(&hmd_tmp);
  tmp=String(hmd_tmp)+" %";
  lv_label_set_text(ui_HmdLabel, tmp.c_str());
  data->getTime()->gethour(&hour);
  data->getTime()->getmin(&min);
  if(hour<10){
    tmp="0"+String(hour);
  }
  else{
    tmp=String(hour);
  }
  tmp+=":";
  if(min<10){
    tmp+="0"+String(min);
  }
  else{
    tmp+=String(min);
  }
  lv_label_set_text(ui_TimeLabel, tmp.c_str());
  //screen2 prog
  while (!data->getProg()->get_active_program_index(&prog_index));
  while (!data->getProg()->get_ProgHour_index(&prog_hour));
  while (!data->getHeater()->getHeatingMode(&mode));
  lv_roller_set_selected(ui_Roller1, (uint16_t) prog_index, LV_ANIM_OFF); //active prog index
  lv_roller_set_selected(ui_Roller2, (uint16_t) prog_hour, LV_ANIM_OFF); // hour
  lv_slider_set_value(ui_wtmpSLider, (int32_t) (data->getProg()->get_program_element( prog_hour)*10.0), LV_ANIM_OFF);
  tmp=String(data->getProg()->get_program_element( prog_hour),1);
  lv_label_set_text(ui_WTMPSliderLable, tmp.c_str());
  static lv_coord_t array[24];
  for(unsigned i=0; i<SIZE; i++){
    array[i]=(lv_coord_t)((int)(data->getProg()->get_program_element(i)*10.0));
  }
  lv_chart_set_ext_y_array(ui_TmpChart, ui_TmpChart_series_1, array);// chart printing
  //screen3 options
  lv_dropdown_set_selected(ui_HeatSetting, (unsigned)mode);
  data->getHeater()->set_heatingMode_changed(false);
  //screen4 devices list
  //empty!
}

void MainTask::set_Active(unsigned param){
    activeScreen=param;
}
unsigned MainTask::get_Active()const{
    return activeScreen;
}

void MainTask::Screen_Upgrading(DataHandler*data, lv_chart_series_t * ui_TmpChart_series_1){
  switch(get_Active()){
    case 0: upgrade_Screen1(data);break;
    case 1: upgrade_Screen2(data, ui_TmpChart_series_1);break;
    case 2: upgrade_Screen3(data);break;
    case 3: upgrade_Screen4(data);break;
    default: return;
  }
  return;
}
void  MainTask::setSensor_Location(DataHandler*data){
  for(unsigned i=0; i<data->getHeater()->get_number_of_HeatingCircles(); i++){
      if(data->getHeater()->getHeatingCircleHandler()[i].getSensor()!=nullptr){
        sensor_location=i;
      }
    }
}
unsigned MainTask::getSensorLocation(){
  return sensor_location;
}