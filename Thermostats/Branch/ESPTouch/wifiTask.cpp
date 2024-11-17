#include "wifiTask.h"

wifiTask::wifiTask(DataHandler *obj){
        data=obj;
        server=new MyServer(data->get_wifi_data()->get_ssid(), data->get_wifi_data()->get_pass(), data->get_wifi_data()->get_host());
        init_html_page();
        
    if(data->get_wifi_data()->get_switch()){

        data->get_wifi_data()->set_ip(server->Wifi_connection());
        server->Server_turning_on();
    }
        sensor_location=0;
        lastTime=0;
        function_selector=false;
        timerDelay=TIMER_DELAY;
        if(data->getHeater()!=nullptr){
            for(unsigned i=0; i<data->getHeater()->get_number_of_HeatingCircles(); i++){
                if(data->getHeater()->getHeatingCircleHandler()[i].getSensor()!=nullptr){
                    sensor_location=i;
                }
            }
        }
}
wifiTask::~wifiTask(){
    delete server;
}
void wifiTask::init_html_page(){
    server->create_html_page(TITLE);
                                //css class, var id text
    server->get_Page()->add_tag("card-title", "null", "Active program");
    server->get_Page()->add_tag("reading", ACTIVE_PROGRAM, "null");
    server->get_Page()->add_tag("card-title", "null","Wanted temperature");
    server->get_Page()->add_tag("reading", WANTED_TEMP," &deg;C");
    server->get_Page()->add_tag("card-title","null" ,"Temperature");
    server->get_Page()->add_tag("reading", TEMPERARTURE, " &deg;C");
    server->get_Page()->add_tag("card-title","null","Humadity");
    server->get_Page()->add_tag("reading",HUMADITY, " %");
    if(data->getHeater()!=nullptr){
        for (unsigned i = 0; i < data->getHeater()->get_number_of_HeatingCircles(); i++){
            server->get_Page()->add_tag("card-title","null" ,"Heating status on "+String(i)+". Circle: ");
            server->get_Page()->add_tag("reading", String(HEATINGCIRCLE_SWITCH)+String(i), "null");
        }
    }
    server->get_Page()->add_tag("card-title","null","Connected devices");
    server->get_Page()->add_tag("reading","null", "ESPCarryable links:");
    server->get_Page()->set_java_script(get_script());
    server->get_Page()->set_css(get_styles());
}

void wifiTask::set_Json_messages(){
    JSONVar msg;
                    //var_name, var_value
    if(data->getProg()->get_server_update_prog_index() || server->get_new_client()){
        msg[ACTIVE_PROGRAM]=String(data->getProg()->get_active_program_index()+1);
        msg[ACTIVE_PROGRAM_SLAVE]=String(data->getProg()->get_active_program_index()+1);
        data->getProg()->set_server_update_prog_index(false);
    }
    else{
        msg[ACTIVE_PROGRAM]=String(data->getProg()->get_active_program_index()+1);
    }
    if(data->getProg()->get_server_update_wtmp() || server->get_new_client()){
        msg[WANTED_TEMP]=String(data->getProg()->get_Wanted_temp(),1);
        msg[WANTED_TEMP_SLAVE]=String(data->getProg()->get_Wanted_temp(),1);
        data->getProg()->set_server_update_wtmp(false);
    }
    else{
        msg[WANTED_TEMP]=String(data->getProg()->get_Wanted_temp(),1);
    }
    msg[TEMPERARTURE]=String(data->getHeater()->getHeatingCircleHandler()[sensor_location].getSensor()->getMeasuredTemperature(),1);
    msg[HUMADITY]=String(data->getHeater()->getHeatingCircleHandler()[sensor_location].getSensor()->getMeasureHmd());
    msg[TIME_HOUR]=String(data->getTime()->gethour());
    msg[TIME_MIN]=String(data->getTime()->getmin());
    if(data->getHeater()!=nullptr){
        for (unsigned i = 0; i < data->getHeater()->get_number_of_HeatingCircles(); i++){
            if(data->getHeater()->getStatus()[i]){
                msg[String(HEATINGCIRCLE_SWITCH)+String(i)]=String("ON");
            }
            else{
                msg[String(HEATINGCIRCLE_SWITCH)+String(i)]=String("OFF");
            }
        }
    }
    if(server->get_new_client()){
        server->set_new_client(false);
    }
    server->set_JS_msg(JSON.stringify(msg));
}

void wifiTask::client_server_activity_check(){
    if(server->get_Clients()!=nullptr){
        for(unsigned i=0; i<server->get_Clients()->getSize(); i++){
            if(server->get_Clients()->get_ids()!=nullptr && server->get_Clients()->get()!=nullptr && server->get_Clients()->get_status()!=nullptr){
                if(server->get_Clients()->get_status()[i]==false){
                    server->get_Page()->remove_list_elem(server->get_Clients()->get()[i]);
                   data->getHeater()->remove_device_from_HeatingCircles(server->get_Clients()->get()[i]);
                    server->get_Clients()->Del(server->get_Clients()->get()[i]);
                }
            }
        }
    }
}

void wifiTask::set_active_prog(String str){
    if(str!=""){
        data->getProg()->set_received_index(str.toInt(), data->getTime()->gethour());
    }
}
void wifiTask::set_wtmp(String str){
    if(str!=""){
        data->getProg()->set_received_wtmp(str.toFloat());
    }
}
void wifiTask::set_temp(JSONVar msg){
    if(data->getHeater()!=nullptr){
        String temp_Heatingid_id;
        for(unsigned i=0; i< data->getHeater()->get_number_of_HeatingCircles(); i++){
            if(data->getHeater()->getHeatingCircleHandler()[i].getDevices()!=nullptr){
                for (unsigned ii = 0; ii < data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getSize(); ii++){
                    temp_Heatingid_id=String((const char*)msg[String(TEMPERARTURE)+String(i)+"_"+String(data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getDevices()[ii].getID())]);
                    if(temp_Heatingid_id!=""){
                        data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getDevices()[ii].updata_temp(temp_Heatingid_id.toFloat());
                        return;
                    }
                }
                
            }
        }
    }
}
void wifiTask::set_mac(String msg, JSONVar msg_js, String ip){
    if(data->getHeater()!=nullptr){
        for(unsigned i=0; i<data->getHeater()->get_number_of_HeatingCircles(); i++){
            if(data->getHeater()->getHeatingCircleHandler()[i].getDevices()!=nullptr){
                for (unsigned ii = 0; ii < data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getSize(); ii++){
                    if(data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getDevices()[ii].get_ip()==ip){
                        return;
                    }
                }
            }
        }
    }
    String id=String((const char*)msg_js[ID]);
    String Heating_id=String((const char*)msg_js[HEATINGCIRCLE_ID]);
    String name=String((const char*)msg_js[DEVICE_NAME]);
    if(msg!="" && id!="" && Heating_id!="" && name !=""){
        if(data->getHeater()!=nullptr){
            data->getHeater()->add_device_to_HeatingCircles(Heating_id.toInt(),msg, name,DEFAULT_TEMP, id.toInt(), ip);
        }
    }     
}

void wifiTask::proccess_received_data(){
    //??
    //active prog, wtmp, temp_id_, mac
    //add component elem, if component with specific ip doesnt exist
    if(server->get_event_Data()!=nullptr){
        JSONVar msg;
        String ip;
        for(unsigned i=0; i<server->get_event_Data()->size() && server->get_event_Data()->get_msg_array()!=nullptr; i++){
            msg=JSON.parse(server->get_event_Data()->get_msg_array()[i]);
            if (JSON.typeof(msg) != "undefined") {
                set_mac(String((const char*)msg[MAC_ADDRESS]), msg,server->get_event_Data()->get_ip_array()[i]);
                set_active_prog(String((const char*)msg[ACTIVE_PROGRAM_SLAVE]));
                set_wtmp(String((const char*)msg[WANTED_TEMP_SLAVE]));
                set_temp(msg);
            }
            server->get_event_Data()->remove_msg(i);
        }    
    }
}



void wifiTask::main(){

  // send time with data. 
  //send data if something changed
if(data->get_wifi_data()->get_switch()){
    if ((millis() - lastTime) > timerDelay) {
        if(server->get_Clients()!=nullptr){
            set_Json_messages();
            server->updata();
        }
        lastTime = millis();
    }
      if(!function_selector){
        proccess_received_data();
        function_selector=true;
      }
      else{
      //nullptr not handled in this funcs. Check all the funcs in there.
        client_server_activity_check();//may be wdt reseting here 
        function_selector=false;
      }
    server->run_server();
}
}