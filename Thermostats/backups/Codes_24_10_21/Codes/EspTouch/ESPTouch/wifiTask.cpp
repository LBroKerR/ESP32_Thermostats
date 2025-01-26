#include "wifiTask.h"

//private

// create a package
// structure:
// heatingcircle, id,  data
//data:
// inner ide(defines) + components data
//      223
//    20000
//  9900000
//990000000
//+
//---------
//999921223

//example 99*(100) 99(*100) 2(*1000) 0(+1000/+0) 223(*10)
//         index 99 id 99 wtemp=22.3
float wifiTask::makePackage(ACK_wifi newAck, unsigned device_id, String *Raw){
    float rawdata=0.0;
    unsigned multiplier=10;
    void* data;
    float Fdata=0.0;
    String Sdata=" ";
    if(!newAck.get_data(data)){
        Fdata=*(float*)data;
        rawdata+=(multiplier*Fdata);
        if(Fdata<0){
            rawdata+=1000;
        }
        multiplier=multiplier*1000;
        rawdata+=(multiplier*newAck.get_data_id());
        multiplier=multiplier*100;
        rawdata+=(multiplier*device_id);
        multiplier=multiplier*100;
        rawdata+=(multiplier*newAck.get_heating_circle());
    }
    else{
        Sdata=*(String*)data;
        *Raw=String(newAck.get_heating_circle())+"\n";
        *Raw+=String(device_id)+"\n";
        *Raw+=String(newAck.get_data_id())+"\n";
        *Raw+=Sdata;
    }
    return rawdata;
}
bool wifiTask::Answer_Request( ACK_wifi msg, unsigned ID){
    String str=" ";
    if (msg.get_heating_circle()>=0 && msg.get_heating_circle()< data->getHeater()->get_number_of_HeatingCircles()){
        if(data->getHeater()->getHeatingCircleHandler()[msg.get_heating_circle()].getDevices()!=nullptr){
            for(unsigned i=0; i<data->getHeater()->getHeatingCircleHandler()[msg.get_heating_circle()].getDevices()->getSize(); i++){
                if(data->getHeater()->getHeatingCircleHandler()[msg.get_heating_circle()].getDevices()->getDevices()[i].getID()==ID){
                    msg.set_device_MAC(data->getHeater()->getHeatingCircleHandler()[msg.get_heating_circle()].getDevices()->getDevices()[i].getMac());
                    float Data=0.0;
                    switch(msg.get_data_id()){
                        case WANTEDTMP: Data=data->getProg()->get_Wanted_temp();break;
                        case PROG: Data=data->getProg()->get_active_program_index(); break;
                        case SWITCH: Data=data->getHeater()->getStatus()[msg.get_heating_circle()];break;
                        case HOUR_WIFI: Data=data->getTime()->gethour();break;
                        case MIN_WIFI: Data=data->getTime()->getmin();break;
                        default: break;
                    }
                    msg.set_data((void*)&Data,false);
                    add_Waited_ack(msg);
                    data->getWifi()->SendRawData(makePackage(msg,ID,&str));
                    return true;
                }
            }
        }
    }
    return false;
}
bool wifiTask::requestData(){
    // new device will connect!
    String str="null";
    bool done=false;
    while(true){
        data->getWifi()->sendString("{mac:,name:,id1:,id2:}\n");
        for(unsigned i=0; i<300; i++){
             if(data->getWifi()->receiveString(&str)){
                if(str=="ack"){
                     Serial.println(str+" received");
                    done=true;
                    break;
                }
                else{
                    Serial.println(str+" else receive");
                }
             }
             vTaskDelay(10/ portTICK_PERIOD_MS);
        }
        if(done){
            done=false;
            break;
        }
    }
    for(unsigned i=0; i<1000; i++){
        if(data->getWifi()->receiveString(&str)){
          Serial.println(str);
          data->getWifi()->sendString("ack\n");
          done=true;
          break;
        }
        else{
             Serial.println(str+"received");
        }
        vTaskDelay(10/ portTICK_PERIOD_MS);
    }
    if(!done){
      return false;
    }
    unsigned startindex=str.indexOf("mac:") + 4;
    unsigned endindex=str.indexOf(",", startindex);
    String mac=str.substring(startindex,  endindex);
    startindex=str.indexOf("name:") + 5;
    endindex=str.indexOf(",",  startindex);
    String name=str.substring(startindex,  endindex);
    startindex=str.indexOf("id1:") + 4;
    endindex=str.indexOf(",",  startindex);
    String id1=str.substring(startindex,  endindex);
    startindex=str.indexOf("id2:") + 3;
    endindex=str.indexOf(",",  startindex);
    String id2=str.substring(startindex,  endindex);
    // heatingID= id1, device id=id2
    unsigned heatingId=id1.toInt();
    unsigned device_id=id2.toInt();
    if(data->getHeater()->get_number_of_HeatingCircles()>heatingId && heatingId>=0){
        if(data->getHeater()->getHeatingCircleHandler()[heatingId].getDevices()!=nullptr){
            data->getHeater()->getHeatingCircleHandler()[heatingId].getDevices()->add_Component(mac,name,21.0,device_id);
            for(unsigned i=0; i<data->getHeater()->getHeatingCircleHandler()[heatingId].getDevices()->getSize(); i++){
                if(mac==data->getHeater()->getHeatingCircleHandler()[heatingId].getDevices()->getDevices()[i].getMac()){
                    data->getHeater()->getHeatingCircleHandler()[heatingId].getDevices()->getDevices()[i].setClient(data->getWifi()->getClient());
                }
            }
            return true;
        }
    }
    return false;
}
void wifiTask::storeData(unsigned heatingID, unsigned index){
    unsigned header=(int)data->getWifi()->getRawData()/100000;
    unsigned data_id=((int)data->getWifi()->getRawData()-header)/10000;
    float Fdata=(data->getWifi()->getRawData()-((int)data->getWifi()->getRawData()/1000))/10;
    switch(data_id){
        case WANTEDTMP: data->getProg()->set_Wanted_temp(Fdata);break;
        case PROG: data->getProg()->set_active_program_index((unsigned)Fdata);break;
        case TEMP: data->getHeater()->getHeatingCircleHandler()[heatingID].getDevices()->getDevices()[index].updata_temp(Fdata);break;
        default: break;
    }

}
bool wifiTask::check_acks(unsigned heatingID, String Mac){
    ACK_wifi tmp;
    int ReceiveHeatingID=((int)data->getWifi()->getRawData()/10000000);
    int Receive_device_id=((int)data->getWifi()->getRawData()/100000)-(ReceiveHeatingID*100);
    int Receiveid=((int)data->getWifi()->getRawData()/10000)-(((int)data->getWifi()->getRawData()/100000)*10);
    int ack=data->getWifi()->getRawData()-(data->getWifi()->getRawData()/100000);
    bool request=false;
    if(Receiveid<0){
        tmp.set_data_id(Receiveid*(-1));
        tmp.set_heating_circle(ReceiveHeatingID*(-1));
        Answer_Request(tmp,Receive_device_id*(-1));
    }
    else{
        for (unsigned i = 0; i < number_of_waited_Answer; i++){
            if(acks[i].get_heating_circle()==heatingID && acks[i].get_device_MAC()==Mac){
                if(data->getHeater()->get_number_of_HeatingCircles() > ReceiveHeatingID){
                    if(data->getHeater()->getHeatingCircleHandler()[ReceiveHeatingID].getDevices()!=nullptr){
                        for(unsigned ii=0; ii<data->getHeater()->getHeatingCircleHandler()[ReceiveHeatingID].getDevices()->getSize(); i++){
                            if(Receive_device_id==data->getHeater()->getHeatingCircleHandler()[ReceiveHeatingID].getDevices()->getDevices()[ii].getID()){
                                if(ack==1){
                                    acks[i].set_ack(true);
                                    return true;
                                }
                                else{
                                    storeData(ReceiveHeatingID,ii );
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool wifiTask::ReceiveData(){
    WiFiClient client;
    if(data->getWifi()->setClient(client)){
        //request
        //new client->get name, and mac! -> request data!
        //name, mac address->String
        Serial.print("new client!");
        return requestData();
    }
    for (unsigned i = 0; i < data->getHeater()->get_number_of_HeatingCircles(); i++){
        if(data->getHeater()->getHeatingCircleHandler()[i].getDevices()!=nullptr){
            for(unsigned ii=0; ii<data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getSize(); i++){
                data->getWifi()->setClient(data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getDevices()[ii].getClient());
                if(data->getWifi()->ReceiveRawData()){
                    //check acks!
                    check_acks(i,data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getDevices()[ii].getMac());
                    //connected device requested/answare(ack/data)
                }
            }
          return true;
        }
    }
    return false;
}

void wifiTask::send_again(){
    unsigned rawdata;
    String raw=" ";
    if(acks!=nullptr){
        for (unsigned i = 0; i < number_of_waited_Answer; i++){
            if(!acks[i].get_ack()){
                for (unsigned ii = 0; ii < data->getHeater()->get_number_of_HeatingCircles(); ii++){
                    if(data->getHeater()->getHeatingCircleHandler()[ii].getDevices()!=nullptr){
                        for (unsigned iii = 0; iii < data->getHeater()->getHeatingCircleHandler()[ii].getDevices()->getSize(); iii++){
                            if(data->getHeater()->getHeatingCircleHandler()[ii].getDevices()->getDevices()[iii].getMac()==acks[i].get_device_MAC()){
                                rawdata=makePackage(acks[i],data->getHeater()->getHeatingCircleHandler()[ii].getDevices()->getDevices()[iii].getID(),&raw);
                                data->getWifi()->setClient(data->getHeater()->getHeatingCircleHandler()[ii].getDevices()->getDevices()[iii].getClient());
                                if(data->getWifi()->Available()){
                                  data->getWifi()->SendRawData(rawdata);
                                }
                            }
                        }
                
                    }
                }
            }
            else{
                remove_ACK(acks[i].get_device_MAC());
            }
        }
    }
}
void  wifiTask::send_msg_to_heatingcircle_devices(unsigned index, bool Switch){
    ACK_wifi newAck;
    String raw=" ";
    newAck.set_data((void*)&Switch,false);
    newAck.set_heating_circle(index);
    if(data->getHeater()->getHeatingCircleHandler()[index].getDevices()!=nullptr){
        for(unsigned i=0;i< data->getHeater()->getHeatingCircleHandler()[index].getDevices()->getSize();i++){
                newAck.set_data_id((int)SWITCH);
                newAck.set_device_MAC(data->getHeater()->getHeatingCircleHandler()[index].getDevices()->getDevices()[i].getMac());
                add_Waited_ack(newAck);
                data->getWifi()->setClient(data->getHeater()->getHeatingCircleHandler()[index].getDevices()->getDevices()[i].getClient());
                if(data->getWifi()->Available()){
                  data->getWifi()->SendRawData(makePackage(newAck,data->getHeater()->getHeatingCircleHandler()[index].getDevices()->getDevices()[i].getID(),&raw));
                }
        }
    }
}
void wifiTask::send_msg_to_all_devices(float param, unsigned id){
    float rawdata=0.0;
    String raw=" ";
    for (unsigned i = 0; i < data->getHeater()->get_number_of_HeatingCircles(); i++){
        if(data->getHeater()->getHeatingCircleHandler()[i].getDevices()!=nullptr){
            if(data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getDevices()!=nullptr){
                for(unsigned k=0; k< data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getSize(); k++){
                    ACK_wifi newAck;
                    newAck.set_data((void*)&param,false);
                    newAck.set_heating_circle(i);
                    newAck.set_data_id(id);
                    newAck.set_device_MAC(data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getDevices()[k].getMac());
                    add_Waited_ack(newAck);
                    rawdata=makePackage(newAck,data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getDevices()[k].getID(),&raw );
                    data->getWifi()->setClient(data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getDevices()[k].getClient());
                    if(data->getWifi()->Available()){
                      data->getWifi()->SendRawData(rawdata);
                    }
                }
            }
        }
    }
    
}
void wifiTask::sendData(){
    if(acks!=nullptr){
        if(wait==RESENDACKS){
            send_again();
        }
    }
    else if(data->getProg()->get_wtmp_changed()){
        send_msg_to_all_devices(data->getProg()->get_Wanted_temp(),WANTEDTMP);
    }
    else if(data->getProg()->get_active_program_index_changed()){
        send_msg_to_all_devices((float)data->getProg()->get_active_program_index(),PROG);
    }
    else if( data->getHeater()!=nullptr){
        for (unsigned i = 0; i < data->getHeater()->get_number_of_HeatingCircles(); i++){
            if(data->getHeater()->getHeatingCircleHandler()[i].get_switch_changed()){
                send_msg_to_heatingcircle_devices(i,data->getHeater()->getStatus()[i]);
            }
       }
        
    }
}
void wifiTask::add_Waited_ack(ACK_wifi const newAck){
    if(acks==nullptr || number_of_waited_Answer==0){
        delete[] acks;
        number_of_waited_Answer=0;
    }
    ACK_wifi *tmp=new ACK_wifi[number_of_waited_Answer+1];
    if(tmp!=nullptr){
        for (unsigned i = 0; i < number_of_waited_Answer; i++){
            tmp[i]=acks[i];
        }
        delete[] acks;
        acks=tmp;
        acks[number_of_waited_Answer]=newAck;
        number_of_waited_Answer++;
    }
}
void wifiTask::remove_disconnected_device_ACKS(String mac){
    if(acks==nullptr || number_of_waited_Answer==0){
        delete[] acks;
        number_of_waited_Answer=0;
        return;
    }
    unsigned number_of_acks=number_of_waited_Answer;
    ACK_wifi tmp_elem;
    for (unsigned i = 0; i < number_of_acks; i++){
        if(acks[i].get_device_MAC()==mac){
            tmp_elem=acks[i];
            for (unsigned k = i; i < number_of_acks-1; k++){
                acks[k]=acks[k+1];
            }
            acks[number_of_acks-1]=tmp_elem;
            number_of_acks--;
            i=0;
        }
    }
    ACK_wifi* tmp_array=new ACK_wifi[number_of_acks];
    for(unsigned i=0; i< number_of_acks; i++ ){
        tmp_array[i]=acks[i];
    }
    delete acks;
    acks=tmp_array;
}
void wifiTask::remove_ACK(String mac){
    if(acks==nullptr || number_of_waited_Answer==0){
        delete[] acks;
        number_of_waited_Answer=0;
        return;
    }
    int index_of_ack=-1;
    for(unsigned i=0; i< number_of_waited_Answer; i++){
        if(acks[i].get_device_MAC()==mac){
            index_of_ack=i;
            break;
        }
    }
    if(index_of_ack!=-1){
        ACK_wifi *tmp=new ACK_wifi[number_of_waited_Answer-1];
        for(unsigned i=0; i< number_of_waited_Answer-1; i++){
            if(index_of_ack > i){
                tmp[i]=acks[i];
            }
            else if(index_of_ack <= i){
                tmp[i]=acks[i+1];
            }
        }
        delete[] acks;
        acks=tmp;
        number_of_waited_Answer--;
    }
}

void wifiTask::checkActiveClients(){
    WiFiClient client;
    String Mac=" ";
    for(unsigned i=0; i< data->getHeater()->get_number_of_HeatingCircles(); i++){
        if(data->getHeater()->getHeatingCircleHandler()[i].getDevices()!=nullptr){
            for(unsigned ii=0; ii<data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getSize(); ii++){
               client = data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getDevices()[ii].getClient();
               Mac=data->getHeater()->getHeatingCircleHandler()[i].getDevices()->getDevices()[ii].getMac();
               if (!client.connected()){
                  client.stop();
                  remove_disconnected_device_ACKS(Mac);
                  data->getHeater()->getHeatingCircleHandler()[i].getDevices()->remove_Component(Mac);
               }
            }
        }
    }
}

//public:

wifiTask::wifiTask(DataHandler*Data){
    data=Data;
    acks=nullptr;
    wait=0;
    number_of_waited_Answer=0;

}
wifiTask::~wifiTask(){
    if(acks!=nullptr){
        delete[] acks;
    }
}

void wifiTask::main(){
    if(data->getWifi()!=nullptr){
        if(data->getWifi()->getSwitch()){
            Serial.begin(115200);
            if(!data->getWifi()->isConnected()){
                data->getWifi()->reconnect();
            }else{
                checkActiveClients();
                wait++;
                if(ReceiveData()){
                    sendData();
                }
                if(wait>=RESENDACKS){
                wait=0;
                }
            }
        }
    }
}