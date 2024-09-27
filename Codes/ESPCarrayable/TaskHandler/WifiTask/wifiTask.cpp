#include "wifiTask.h"
//request data from server.
//checking wifi and server connection 
void wifiTask::init( DataHandler *data){
    //prog, wtmp, switch, hour, min
    data->getWifi()->IsconnectedToWifi();
    data->getWifi()->IsconnectedToServer();

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
}
//make sendable variable
float wifiTask::makePacket(float data, int id){
    return (data+1000*(float)id);
}
// send changed datas, what the server must have.
bool wifiTask::sendData(DataHandler *data){
    //prog,wtmp,tmp
    if(data->getProg()->get_active_program_index_changed()){
        data->getWifi()->sendData(makePacket(data->getProg()->get_active_program_index(), PROG));
    }
    else if(data->getSensor()->get_tempChange()){
        data->getWifi()->sendData(makePacket(data->getSensor()->getMeasuredTemperature(),TEMP));
    }
    else if(data->getProg()->get_wtmp_changed()){
        data->getWifi()->sendData(makePacket(data->getProg()->get_Wanted_temp(),WANTEDTMP));
    }
    return data->getWifi()->ReceiveACK();
}
// if server request datas. the slave will send it to the server
bool wifiTask::requested(DataHandler *data, int index){
     //HeatingID, name, MAC
    float Data=0.0;
    switch(index){
        case NAME:data->getWifi()->sendString("name "+data->getSensor()->getNickName());break;
        case HEATINGID: data->getWifi()->sendData(makePacket(data->getSensor()->getHeatingCircleID(),HEATINGID));break;
        case MAC:data->getWifi()->sendMAC();break;
        default: return false;
    }
    return data->getWifi()->ReceiveACK();
}

// monitoring dataflow, if not a request, then save the incoming data, if the data right.
bool wifiTask::receiveData(DataHandler *data){
    if(data->getWifi()->ReceiveRawData()){
        if(data->getWifi()->getID()<0){//request.

            return requested(data,(-1)*data->getWifi()->getID());
        }
        else{
            switch(data->getWifi()->getID()){
                case WANTEDTMP:data->getProg()->set_Wanted_temp(data->getWifi()->getData()); data->getProg()->set_wtmp_changed(true); break;
                case PROG: data->getProg()->set_active_program_index((unsigned)data->getWifi()->getData());data->getProg()->set_active_program_index_changed(true); break;
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
    data->getWifi()->IsconnectedToServer();
    if(receiveData(data)){
        output=true;
    }
    else if(sendData(data)){
        output=true;
    }
    return output;
}