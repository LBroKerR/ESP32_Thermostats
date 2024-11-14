#include "MainTask.h"

//private:

void MainTask::update_wtmp(DataHandler*data){
  String tmp;
    // wanted temp, and acr!
    // if espcarryable change value, or arc-> manual. dont send value
    //if arc modify value or hour change-> send data to carryable
    //if hour change-> auto!

    /*if(data->getProg()->get_wtmp_changed()){
      data->getProg()->set_wtmp_changed(false);
      if(data->getProg()->get_Wanted_temp()!=(((float)lv_arc_get_value(ui_WtmpARC))/10.0)){
        //carryable 
        lv_label_set_text(ui_AutoManual, "Manual");
        //set arc
        lv_arc_set_value(ui_WtmpARC,(data->getProg()->get_Wanted_temp()*10.0));
      }
    }
    else if(!data->getProg()->get_wtmp_changed()){
      if(data->getProg()->get_Wanted_temp()!=(((float)lv_arc_get_value(ui_WtmpARC))/10.0)){
        //set arc -> user interaction
        data->getProg()->set_Wanted_temp((float)lv_arc_get_value(ui_WtmpARC)/10.0);
         lv_label_set_text(ui_AutoManual, "Manual");
      }

    }
    if(data->getTime()->get_hour_Changed()){

      data->getProg()->set_Wanted_temp(data->getProg()->get_program_element(data->getTime()->gethour()));
      lv_arc_set_value(ui_WtmpARC,(data->getProg()->get_Wanted_temp()*10.0)); 
      lv_label_set_text(ui_AutoManual, "Auto");
    }
    if(data->getProg()->get_Wanted_temp()=(((float)lv_arc_get_value(ui_WtmpARC))/10.0)){
      lv_label_set_text(ui_AutoManual, "Auto");
    }
    tmp=String(data->getProg()->get_Wanted_temp(),1)+" °C";
    lv_label_set_text(ui_WtmpLabel, tmp.c_str());*/

  if(auto_flag){//auto
    data->getProg()->set_Wanted_temp(data->getProg()->get_program_element(data->getTime()->gethour()));
    lv_arc_set_value(ui_WtmpARC,(data->getProg()->get_Wanted_temp()*10.0));
    lv_label_set_text(ui_AutoManual, "Auto");
    auto_flag=false;
  }
  if(data->getProg()->get_Wanted_temp()!=(float)((lv_arc_get_value(ui_WtmpARC))/10.0)){//manual
    data->getProg()->set_Wanted_temp((float)(lv_arc_get_value(ui_WtmpARC))/10.0);
      lv_label_set_text(ui_AutoManual, "Manual");
  }
    tmp=String(data->getProg()->get_Wanted_temp(),1)+" °C";
    lv_label_set_text(ui_WtmpLabel,tmp.c_str());
}

void MainTask::upgrade_Screen1(DataHandler*data){// temp, wtemp, hmd, clock, wifi, heat switch
  String tmp;
  update_wtmp(data);
  //DHT sensor
  tmp=String(data->getHeater()->getHeatingCircleHandler()[getSensorLocation()].getSensor()->getMeasuredTemperature(),1)+" °C";
      lv_label_set_text(ui_TmpLabel, tmp.c_str());
  tmp=String(data->getHeater()->getHeatingCircleHandler()[getSensorLocation()].getSensor()->getMeasureHmd())+" %";
      lv_label_set_text(ui_HmdLabel, tmp.c_str());
  if(data->getTime()->gethour()<10){
  
  //rtc clock 
  tmp="0"+String(data->getTime()->gethour());
  }
  else{
    tmp=String(data->getTime()->gethour());
  }
  tmp+=":";
  if(data->getTime()->getmin()<10){
    tmp+="0"+String(data->getTime()->getmin());
  }
  else{
    tmp+=String(data->getTime()->getmin());
  }
  lv_label_set_text(ui_TimeLabel, tmp.c_str());

  //wtmp

  update_wtmp(data);

  // ON/OFF set;
  if(data->getHeater()->getStatus()[sensor_location]){
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
  if(data->getProg()->get_active_program_index_changed() && data->getProg()->get_active_program_index()!=lv_roller_get_selected(ui_Roller1)){
    //setting gui with the receive progindex from espcarryable
    lv_roller_set_selected(ui_Roller1, (uint16_t) data->getProg()->get_active_program_index(), LV_ANIM_OFF);
    output=true;
  }
   if(data->getProg()->get_active_program_index()!=lv_roller_get_selected(ui_Roller1)){ //&& !data->getProg()->get_active_program_index_changed()){
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
  String str;
  if(data->getProg()->get_active_program_index_changed()){
    lv_slider_set_value(ui_wtmpSLider, (int32_t)(data->getProg()->get_program_element()*10.0), LV_ANIM_OFF);
    str=String(data->getProg()->get_program_element(),1)+" °C";
    lv_label_set_text(ui_WTMPSliderLable, str.c_str());
    data->getProg()->set_active_program_index_changed(false);
    return true;
  }
  else if(data->getProg()->get_ProgHour_index()!=lv_roller_get_selected(ui_Roller2)){
    data->getProg()->set_ProgHour_index(lv_roller_get_selected(ui_Roller2));
    return true;
  }
  else{
    auto_flag=true;
  }
  return false;
}

bool MainTask::update_progindex_slider(DataHandler* data){
  bool output=false;
  String str;
  if(data->getProg()->get_ProgHour_index_changed()){
    data->getProg()->set_ProgHour_index_changed(false);
    lv_slider_set_value(ui_wtmpSLider, (int32_t)(data->getProg()->get_program_element()*10.0), LV_ANIM_OFF);
    str=String(data->getProg()->get_program_element(),1)+" °C";
    lv_label_set_text(ui_WTMPSliderLable, str.c_str());
    output=true;
  }
  else if(data->getProg()->get_program_element()!=((float)lv_slider_get_value(ui_wtmpSLider)/10.0)){
    data->getProg()->set_program_element((float)lv_slider_get_value(ui_wtmpSLider)/10.0);
    str=String(data->getProg()->get_program_element(),1)+" °C";
    lv_label_set_text(ui_WTMPSliderLable, str.c_str());
    output=true;
  }
  return output;
}
void MainTask::upgrade_Screen2(DataHandler*data, lv_chart_series_t * ui_TmpChart_series_1){//prog -> active prog, chart, slider
 data->getProg()->set_active_program_index_changed(true);
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
/*String str;
  int ProgHourIndex=lv_roller_get_selected(ui_Roller2);
  int ActiveprogIndex=lv_roller_get_selected(ui_Roller1);
  int sliderVaule=lv_slider_get_value(ui_wtmpSLider);
  bool printChart=false;


  if(data->getProg()->get_ProgHour_index()!=ProgHourIndex){
    data->getProg()->set_ProgHour_index(ProgHourIndex);
    lv_slider_set_value(ui_wtmpSLider, (int32_t)(data->getProg()->get_program_element(ProgHourIndex)*10.0), LV_ANIM_OFF);
    str= String((float)(lv_slider_get_value(ui_wtmpSLider)/10.0)) +" °C";
    lv_label_set_text(ui_WTMPSliderLable, str.c_str());
  }
  else if(data->getProg()->get_ProgHour_index()==ProgHourIndex)
  {
    str= String((float)sliderVaule/10.0,1) +" °C";
    lv_label_set_text(ui_WTMPSliderLable, str.c_str());
    data->getProg()->set_program_element(ProgHourIndex,(float)sliderVaule/10.0);
    if(data->getTime()->gethour()==ProgHourIndex){
      data->getProg()->set_Wanted_temp((float)sliderVaule/10.0);
    }
    printChart=true;
  }
  if(data->getProg()->get_active_program_index()!=ActiveprogIndex){
    data->getProg()->set_active_program_index(ActiveprogIndex);
    //slider
    lv_slider_set_value(ui_wtmpSLider, (int32_t)(data->getProg()->get_program_element(ProgHourIndex)*10.0), LV_ANIM_OFF);
    str= String((float)(lv_slider_get_value(ui_wtmpSLider)/10.0)) +" °C";
    lv_label_set_text(ui_WTMPSliderLable, str.c_str());
    printChart=true;
  }
  if(printChart){
    static lv_coord_t array[24];
    for(unsigned i=0; i<SIZE; i++){
      array[i]=(lv_coord_t)((int)(data->getProg()->get_program_element(i)*10.0));
    }
    lv_chart_set_ext_y_array(ui_TmpChart, ui_TmpChart_series_1, array);// chart printing
  }*/
}
void MainTask::upgrade_Screen3(DataHandler*data){//options -> heating mode
  data->getHeater()->setHeatingMode((bool)lv_dropdown_get_selected(ui_HeatSetting));
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
  //screen1 home
 lv_label_set_text(ui_wifiLabel, "Offline");
 lv_label_set_text(ui_AutoManual, "Auto");
  tmp=String(data->getProg()->get_Wanted_temp(),1)+" °C";
      lv_label_set_text(ui_WtmpLabel, tmp.c_str());
      lv_arc_set_value(ui_WtmpARC,(data->getProg()->get_Wanted_temp()*10.0));
  tmp=String(data->getHeater()->getHeatingCircleHandler()[getSensorLocation()].getSensor()->getMeasuredTemperature(),1)+" °C";
      lv_label_set_text(ui_TmpLabel, tmp.c_str());
  tmp=String(data->getHeater()->getHeatingCircleHandler()[getSensorLocation()].getSensor()->getMeasureHmd())+" %";
      lv_label_set_text(ui_HmdLabel, tmp.c_str());

  if(data->getTime()->gethour()<10){
    tmp="0"+String(data->getTime()->gethour());
  }
  else{
    tmp=String(data->getTime()->gethour());
  }
  tmp+=":";
  if(data->getTime()->getmin()<10){
    tmp+="0"+String(data->getTime()->getmin());
  }
  else{
    tmp+=String(data->getTime()->getmin());
  }
  lv_label_set_text(ui_TimeLabel, tmp.c_str());
  //screen2 prog
  lv_roller_set_selected(ui_Roller1, (uint16_t) data->getProg()->get_active_program_index(), LV_ANIM_OFF); //active prog index
  lv_roller_set_selected(ui_Roller2, (uint16_t) data->getProg()->get_ProgHour_index(), LV_ANIM_OFF); // hour
  lv_slider_set_value(ui_wtmpSLider, (int32_t)(data->getProg()->get_program_element( data->getProg()->get_ProgHour_index())*10.0), LV_ANIM_OFF);
  tmp=String(data->getProg()->get_program_element( data->getProg()->get_ProgHour_index()),1);
  lv_label_set_text(ui_WTMPSliderLable, tmp.c_str());
  static lv_coord_t array[24];
  for(unsigned i=0; i<SIZE; i++){
    array[i]=(lv_coord_t)((int)(data->getProg()->get_program_element(i)*10.0));
  }
  lv_chart_set_ext_y_array(ui_TmpChart, ui_TmpChart_series_1, array);// chart printing
  //screen3 options
  lv_dropdown_set_selected(ui_HeatSetting, (unsigned)data->getHeater()->getHeatingMode());
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

void MainTask::measuring(DataHandler*data, DHT*sensor,ESP32Time *rtc){
    unsigned min=rtc->getMinute();
    unsigned hour=rtc->getHour(true);
    data->getTime()->setClock(hour, min);
    if(data->getHeater()->getHeatingCircleHandler()[getSensorLocation()].getSensor()!=nullptr){
        data->getHeater()->getHeatingCircleHandler()[getSensorLocation()].getSensor()->measuring(sensor->readTemperature(),(unsigned)sensor->readHumidity());
    }
}