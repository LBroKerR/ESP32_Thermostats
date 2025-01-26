#include "HeatHandler.h"


HeatHandler::HeatHandler(){
    HeatingCircles=nullptr;
    number_of_HeatingCircles=0;
    heatingMode.set_variable(false);
    heatingMode_changed=false;
    status=nullptr;
}
HeatHandler::HeatHandler(unsigned slave_id){
    HeatingCircles=nullptr;
    number_of_HeatingCircles=0;
    heatingMode.set_variable(false);
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
    bool_mutex *tmpStatus=new bool_mutex[number_of_HeatingCircles+1];
    bool tmp_var=false;
    if( status!=nullptr && HeatingCircles!=nullptr && number_of_HeatingCircles!=0){
        for (unsigned i = 0; i < number_of_HeatingCircles; i++){
            tmp[i]=HeatingCircles[i];
            while (!status[i].get_variable(&tmp_var));
            while (!tmpStatus[i].set_variable(tmp_var));
        }
        delete[] HeatingCircles;
        HeatingCircles=tmp;
        delete[] status;
        status=tmpStatus;
        status[number_of_HeatingCircles].set_variable(false);
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
    status=new bool_mutex[number_of_HeatingCircles];
    for(unsigned i=0; i< number_of_HeatingCircles; i++){
        status[i].set_variable(false);
    }
    return true;
}

bool HeatHandler::remove_HeatingCircles(unsigned index){
    if(HeatingCircles==nullptr || number_of_HeatingCircles==0 || status==nullptr){
        return false;
    }
    if(index> 1 && index< number_of_HeatingCircles){
        HeatingCircleHandler* tmp=new HeatingCircleHandler[number_of_HeatingCircles-1];
        bool_mutex *tmpStatus=new bool_mutex[number_of_HeatingCircles-1];
        bool tmp_var=false;
        for(unsigned i=0; i< number_of_HeatingCircles-1; i++){
            if(i<index){
                tmp[i]=HeatingCircles[i];
                status[i].get_variable(&tmp_var);
                tmpStatus[i].set_variable(tmp_var);
            }
            else{
                tmp[i]=HeatingCircles[i+1];
                status[i+1].get_variable(&tmp_var);
                tmpStatus[i].set_variable(tmp_var);
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
    heatingMode.set_variable(param);
    heatingMode_changed=true;
}
bool HeatHandler::getHeatingMode(bool* param){
    return heatingMode.get_variable(param);
}
void HeatHandler::get_HeatingCircles_status(float wtmp){
    //size will be the number of heating circle!
    //check every heating circle device-> components temp-> summ it, then devide with the number of component!
    // if the getter number bigger then wtmp+step-> status[i]=false;
    // number<=wtmp-step
    bool tmp_var=false;
    if(status!=nullptr &&  HeatingCircles!=nullptr && number_of_HeatingCircles!=0){
        for(unsigned i=0; i<number_of_HeatingCircles; i++){
            status[i].get_variable(&tmp_var);
            switch (HeatingCircles[i].Heating(wtmp)){
            case 0:  
                    if(tmp_var){
                        HeatingCircles[i].set_switch_changed(true);
                    }
                    tmp_var=false;
                    break;
            case 1: 
                     if(!tmp_var){
                        HeatingCircles[i].set_switch_changed(true);
                     }
                     tmp_var=true; 
                     break;
            case 2: break; // not changed!
            case 3: break; //diveding with zero
            default:;
            }
            status[i].set_variable(tmp_var);
        }
    }
    return;
}
unsigned HeatHandler::get_number_of_HeatingCircles(){
    return number_of_HeatingCircles;
}
bool_mutex* HeatHandler::getStatus(){
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