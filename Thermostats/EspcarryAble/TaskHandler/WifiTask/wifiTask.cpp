#include "wifiTask.h"


wifiTask::wifiTask(DataHandler *obj){
    data=obj;
    server=new MyServer(data->get_wifi_data()->get_ssid(), data->get_wifi_data()->get_pass(), data->get_wifi_data()->get_host());
    lastTime=0;
    function_selector=false;
    timerDelay=TIMER_DELAY;
    init_html_page();
    server->Wifi_connection();
    server->Server_turning_on();
    server->connect_to_server(data->get_wifi_data()->get_ip());
}
wifiTask::~wifiTask(){
    delete server;
}
void wifiTask::init_html_page(){

    server->create_html_page(data->getSensor()->getNickName());
                                        //css class, var id text
    server->get_Page()->add_tag("card-title", "null","Device name ");
    server->get_Page()->add_tag("reading", String(DEVICE_NAME), "null");
    server->get_Page()->add_tag("card-title","null" ,"Mac address: " );
    server->get_Page()->add_tag("reading",String(MAC_ADDRESS),  "null");
    server->get_Page()->add_tag("card-title","null" ,"Device ID ");
    server->get_Page()->add_tag("reading",String(ID), "null");
    server->get_Page()->add_tag("card-title", "null","Heating circle ID ");
    server->get_Page()->add_tag("reading",String(HEATINGCIRCLE_ID), "null");

    server->get_Page()->add_tag("card-title", "null","Temperature");
    server->get_Page()->add_tag("reading",String(TEMPERATURE)+String(data->getSensor()->getHeatingCircleID())+"_"+String(data->getSensor()->getID()), " &deg;C");
    server->get_Page()->add_tag("card-title","null" ,"Humadity");
    server->get_Page()->add_tag("reading",String(HUMADITY)+String(data->getSensor()->getHeatingCircleID())+"_"+String(data->getSensor()->getID()), " %");
    server->get_Page()->add_tag("card-title","null" ,"Server: ");
    server->get_Page()->add_tag("reading","null", "ESPTouch Link: ");
    server->get_Page()->add_list_elem(data->get_wifi_data()->get_ip()+":"+String(data->get_wifi_data()->get_host()),data->get_wifi_data()->get_ip());
    server->get_Page()->set_java_script(get_script(String(data->get_wifi_data()->get_host())));
    server->get_Page()->set_css(get_styles());

}

void wifiTask::set_Json_messages(){
    //mac, name, heating_id, id ++
    JSONVar msg;
    msg[MAC_ADDRESS]=server->get_Mac();
    msg[ID]=String(data->getSensor()->getID());
    msg[HEATINGCIRCLE_ID]=String(data->getSensor()->getHeatingCircleID());
    msg[DEVICE_NAME]=data->getSensor()->getNickName();
    msg[TEMPERATURE+String(data->getSensor()->getHeatingCircleID())+"_"+String(data->getSensor()->getID())]=String(data->getSensor()->getMeasuredTemperature(),1);
    //humadity, temperature 
    msg[HUMADITY+String(data->getSensor()->getHeatingCircleID())+"_"+String(data->getSensor()->getID())]=String(data->getSensor()->getMeasureHmd());
    //wtmp, active prog
    if(data->getProg()->get_active_program_index_changed()){
        msg[ACTIVE_PROGRAM]=String(data->getProg()->get_active_program_index());
        data->getProg()->set_active_program_index_changed(false);
    }
    if(data->getProg()->get_wtmp_changed()){
        msg[WANTED_TEMP]=String(data->getProg()->get_Wanted_temp(),1);
        data->getProg()->set_wtmp_changed(false);
    }
    server->set_JS_msg(JSON.stringify(msg));
}

void wifiTask::set_active_program(String str){
    if(str!="" ){
        data->getProg()->set_program_index(str.toInt()-1);
    }
}
void wifiTask::set_wanted_temp(String str){
    if(str!="" ){
        data->getProg()->set_wtmp(str.toFloat());
    }
}
void wifiTask::set_heating_switch(String str){
    if(str!=""){
        if(str=="OFF"){
            data->setSwitch(false);
        }
        else if(str=="ON"){
            data->setSwitch(true);
        }
    }
}
void wifiTask::set_time_hour(String str){
    if(str!=""){
        data->getTime()->setClock(str.toInt(), data->getTime()->getmin());
    }
}
void wifiTask::set_time_min(String str){
    if(str!=""){
       data->getTime()->setClock(data->getTime()->gethour(),str.toInt());
    }
}

void wifiTask::proccess_received_data(){
    //where is the client receive ? in handleWebSocketMessage or in onEvent1?
    //may be in onEvent1
    //active program, wtmp, headting_index of heatingcircle id
    if(server->get_received_data()!=nullptr){
        JSONVar msg;
        for(unsigned i=0; i< server->get_received_data()->size() && server->get_received_data()->get_msg_array()!=nullptr; i++){
            msg=JSON.parse(server->get_received_data()->get_msg_array()[i]);
            if(JSON.typeof(msg) != "undefined"){
                set_active_program(String((const char*)msg[ACTIVE_PROGRAM]));
                set_wanted_temp(String((const char*)msg[WANTED_TEMP]));
                set_heating_switch(String((const char*)msg[String(HEATINGCIRCLE_SWITCH)+String(data->getSensor()->getHeatingCircleID())]));
                //Serial.println(String(HEATINGCIRCLE_SWITCH)+String(data->getSensor()->getHeatingCircleID()));
                set_time_hour(String((const char*)msg[TIME_HOUR]));
                set_time_min(String((const char*)msg[TIME_MIN]));

            }
            server->get_received_data()->remove_msg(i);
        }
    }
}

void wifiTask::main(){
  //receive time
  //send data if something changed
    //server->reconnect();
    if ((millis() - lastTime) > timerDelay) {
        set_Json_messages();
        server->Client_update();
        set_Json_messages();
        server->updata();
        lastTime = millis();
    }
    else{
        proccess_received_data();
    }
    server->run_server();
}