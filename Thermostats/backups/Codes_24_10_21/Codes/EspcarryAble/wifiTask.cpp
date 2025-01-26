#include "wifiTask.h"
//request data from server.
//checking wifi and server connection 
void wifiTask::init( DataHandler *data){
    //prog, wtmp, switch, hour, min
    Serial.begin(115200);
    delay(100);
    data->getWifi()->IsconnectedToWifi();
    data->getWifi()->connection_check();
    while(!requested(data)){
      delay(1000);
      Serial.println("data send needed");
    }
    while(!data->getWifi()->RequestData(WANTEDTMP));
    data->getProg()->set_Wanted_temp(data->getWifi()->getData());
    data->getProg()->set_wtmp_changed(true);

    while(!data->getWifi()->RequestData(PROG));
    data->getProg()->set_active_program_index(data->getWifi()->getData());
    data->getProg()->set_active_program_index_changed(true);

    while(!data->getWifi()->RequestData(SWITCH));
    data->setSwitch((bool)data->getWifi()->getData());

    while(!data->getWifi()->RequestData(HOUR_WIFI));
    data->getTime()->setClock(data->getWifi()->getData(),data->getTime()->getmin());
    data->getTime()->set_hour_Changed(true);

    while(!data->getWifi()->RequestData(MIN_WIFI));
    data->getTime()->setClock(data->getTime()->gethour(),data->getWifi()->getData());
    data->getTime()->set_min_Changed(true);

    data->getWifi()->setInitDone(true);
    Serial.end();
}
//make sendable variable
float wifiTask::makePacket(float data, int id){
    float pack=0.0;
    if(data<0.0){
     pack=1000;   
    }
    pack+=data*10;
    return (pack+10000*(float)id);
}
// send changed datas, what the server must have.
bool wifiTask::sendData(DataHandler *data){
    //prog,wtmp,tmp
    unsigned pack=data->getSensor()->getHeatingCircleID()*1000;
    pack+=data->getSensor()->getID()*10;
    pack*=10;
    if(data->getProg()->get_active_program_index_changed()){
        pack+=PROG;
        data->getWifi()->sendData(makePacket(data->getProg()->get_active_program_index(), pack));
    }
    else if(data->getSensor()->get_tempChange()){
        pack+=TEMP;
        data->getWifi()->sendData(makePacket(data->getSensor()->getMeasuredTemperature(),pack));
    }
    else if(data->getProg()->get_wtmp_changed()){
        pack+=WANTEDTMP;
        data->getWifi()->sendData(makePacket(data->getProg()->get_Wanted_temp(),pack));
    }
    for(unsigned i=0; data->getWifi()->ReceiveACK(); i++){
        if(i>=10000){
            return false;
        }
    }
    if(data->getProg()->get_active_program_index_changed()){
        data->getProg()->set_active_program_index_changed(false);
    }
    else if(data->getProg()->get_wtmp_changed()){
        data->getProg()->set_wtmp_changed(false);
    }
    else if(data->getSensor()->get_tempChange()){
        data->getSensor()->set_tempChange(false);
    }
    return true;
}
// if server request datas. the slave will send it to the server
bool wifiTask::requested(DataHandler *data){
    String str="null";
    String ack="null";
    //data->getWifi()->sendString("ping\n");
    while(true){
      if(data->getWifi()->receiveString(&str)){
            Serial.println(str+"received");
            if(str=="{mac:,name:,id1:,id2:}"){
                data->getWifi()->sendString("ack\n");
              break;
            }
        }
      vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    if(str=="{mac:,name:,id1:,id2:}"){
        str="{mac:"+data->getWifi()->getMAC()+",";
        str+="name:"+data->getSensor()->getNickName()+",";
        str+="id1:"+String(data->getSensor()->getHeatingCircleID())+",";
        str+="id2:"+String(data->getSensor()->getID())+"}\n";
        data->getWifi()->sendString(str);
        while(true){
            if(data->getWifi()->receiveString(&ack)){
                if(ack=="ack"){
                    break;
                }
                else{
                    data->getWifi()->sendString(str);
                    delay(1000);
                     Serial.println(str+"need to be send!");
                }
            }
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
        return true;
    }
    return false;
}

// monitoring dataflow, if not a request, then save the incoming data, if the data right.
bool wifiTask::receiveData(DataHandler *data){
    if(data->getWifi()->ReceiveRawData()){
        if(data->getWifi()->get_device_id()==data->getSensor()->getID() && data->getWifi()->get_heating_id()==data->getSensor()->getHeatingCircleID()){
            switch(data->getWifi()->getID()){
                case WANTEDTMP:data->getProg()->set_Wanted_temp(data->getWifi()->getData()); break;
                case PROG: data->getProg()->set_active_program_index((unsigned)data->getWifi()->getData()); break;
                case SWITCH: data->setSwitch((bool)data->getWifi()->getData());break;
                default: return false;
            }
        return true;
        }
    }
    return false;
}
// senidng or receive. if the output true, it will save some parameter to the eeprom, after return to the call point.
bool wifiTask::main(DataHandler *data){
    bool output=false;
    data->getWifi()->IsconnectedToWifi();
    if(receiveData(data)){
        output=true;
    }
    else if(sendData(data)){
        output=true;
    }
    return output;
}