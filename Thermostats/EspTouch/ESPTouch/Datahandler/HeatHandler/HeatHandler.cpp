#include "HeatHandler.h"


HeatHandler::HeatHandler(){
    HeatingCircles=nullptr;
    number_of_HeatingCircles=0;
    heatingMode=false;
    heatingMode_changed=false;
    status=nullptr;
}
HeatHandler::HeatHandler(unsigned slave_id){
    HeatingCircles=nullptr;
    number_of_HeatingCircles=0;
    heatingMode=false;
    status=nullptr;
}
HeatHandler::~HeatHandler(){
    if(HeatingCircles!=nullptr){
        delete[] HeatingCircles;
    }
    if(status!=nullptr){
        delete[] status;
    }
}

bool HeatHandler::add_HeatingCircles(){
    if(HeatingCircles==nullptr || number_of_HeatingCircles==0 || status==nullptr){
        delete[] HeatingCircles;
        delete[] status;
        number_of_HeatingCircles=0;
    }
    HeatingCircleHandler* tmp=new HeatingCircleHandler[number_of_HeatingCircles+1];
    bool *tmpStatus=new bool[number_of_HeatingCircles+1];
    if( status!=nullptr && HeatingCircles!=nullptr && number_of_HeatingCircles!=0){
        for (unsigned i = 0; i < number_of_HeatingCircles; i++){
            tmp[i]=HeatingCircles[i];
            tmpStatus[i]=status[i];

        }
        delete[] HeatingCircles;
        HeatingCircles=tmp;
        delete[] status;
        status=tmpStatus;
        status[number_of_HeatingCircles]=false;
        number_of_HeatingCircles++;
    }
    return true;
}

bool HeatHandler::add_HeatingCircles(unsigned number){
    if(HeatingCircles!=nullptr && status!=nullptr){
        delete[] HeatingCircles;
        delete[] status;
    }
    number_of_HeatingCircles= number;
    HeatingCircles=new HeatingCircleHandler[number_of_HeatingCircles];
    status=new bool[number_of_HeatingCircles];
    for(unsigned i=0; i< number_of_HeatingCircles; i++){
        status[i]=false;
    }
    return true;
}

bool HeatHandler::remove_HeatingCircles(unsigned index){
    if(HeatingCircles==nullptr || number_of_HeatingCircles==0 || status==nullptr){
        return false;
    }
    if(index> 1 && index< number_of_HeatingCircles){
        HeatingCircleHandler* tmp=new HeatingCircleHandler[number_of_HeatingCircles-1];
        bool *tmpStatus=new bool[number_of_HeatingCircles-1];
        for(unsigned i=0; i< number_of_HeatingCircles-1; i++){
            if(i<index){
                tmp[i]=HeatingCircles[i];
                tmpStatus[i]=status[i];
            }
            else{
                tmp[i]=HeatingCircles[i+1];
                tmpStatus[i]=status[i+1];
            }
        }
        delete[] status;
        delete[] HeatingCircles;
        number_of_HeatingCircles--;
        HeatingCircles=tmp;
        status=tmpStatus;
        return true;
    }
    return false;
}

 HeatingCircleHandler* HeatHandler::getHeatingCircleHandler(){
        return HeatingCircles;
 }

bool HeatHandler::add_device_to_HeatingCircles(unsigned index, String const MACaddress, String const name, float const temp,unsigned const id, String ip){
    if(HeatingCircles==nullptr || number_of_HeatingCircles==0 ){
        return false;
    }
    if(index>=0 && index<number_of_HeatingCircles){
        if(HeatingCircles[index].addDevices(MACaddress,name,temp,id, ip)){
            return true;
        }
    }
    return false;
}
bool HeatHandler::add_Measuringsensor(unsigned index, float offset, unsigned id, String name){
    if(index>=0 && index<number_of_HeatingCircles){
        if(HeatingCircles[index].addSensor(offset,id,name)){
            return true;
        }
    }
    return false;
}

void HeatHandler::remove_device_from_HeatingCircles(String ip){
    if(HeatingCircles==nullptr || number_of_HeatingCircles==0){
        return;
    }
    for(unsigned i=0; i<number_of_HeatingCircles; i++){
        Serial.println(i);
        if(HeatingCircles[i].getDevices()!=nullptr && HeatingCircles[i].getDevices()->getDevices()!=nullptr){
            Serial.println("inner");
            if(HeatingCircles[i].getDevices()->remove_Component(ip)){
               break;
            }
        }
    }
}

    //from designed gui
void HeatHandler::setHeatingMode(bool const param){
    if(param!=heatingMode){
        heatingMode_changed=true;
    }
    heatingMode=param;
}
bool HeatHandler::getHeatingMode()const{
    return heatingMode;
}
void HeatHandler::get_HeatingCircles_status(float wtmp){
    //size will be the number of heating circle!
    //check every heating circle device-> components temp-> summ it, then devide with the number of component!
    // if the getter number bigger then wtmp+step-> status[i]=false;
    // number<=wtmp-step
    if(status!=nullptr &&  HeatingCircles!=nullptr && number_of_HeatingCircles!=0){
        for(unsigned i=0; i<number_of_HeatingCircles; i++){
            switch (HeatingCircles[i].Heating(wtmp)){
            case 0:  
                    if(status[i]){
                        HeatingCircles[i].set_switch_changed(true);
                    }
                    status[i]=false;
                    break;
            case 1: 
                     if(!status[i]){
                        HeatingCircles[i].set_switch_changed(true);
                     }
                     status[i]=true; 
                     break;
            case 2: break; // not changed!
            case 3: break; //diveding with zero
            default:;
            }
        }
    }
    return;
}
unsigned HeatHandler::get_number_of_HeatingCircles(){
    return number_of_HeatingCircles;
}
bool* HeatHandler::getStatus(){
    return status;
}

bool HeatHandler::get_heatingMode_changed()const{
    return heatingMode_changed;
}
void HeatHandler::set_heatingMode_changed(bool const param){
    heatingMode_changed=param;
}

void HeatHandler::set_modbus_data(unsigned id, uint16_t register_address, uint8_t register_number){
    modbusData.set_data(id, register_address, register_number);
}
Modbus_data HeatHandler::get_modbus_data(){
    return modbusData;
}