#include "HeatingCommunicationTask.h"


HeatingCommunicationTask::~HeatingCommunicationTask(){
    if(modbus!=nullptr){
        delete modbus;
    }
}
void HeatingCommunicationTask::set_modbus_communication(unsigned id, uint16_t register_address, uint8_t num_reg){
    modbus=new modbusHandler(id, register_address, num_reg);
}
void HeatingCommunicationTask::Communicate_with_PLC(){
    uint8_t Data=0;
    float wtmp_tmp=0.0;
    bool mode_tmp=false, status_tmp=false;
    data->getProg()->get_Wanted_temp(&wtmp_tmp);
    data->getHeater()->get_HeatingCircles_status(wtmp_tmp);
    if(modbus==nullptr){
        return;
    }
    for(unsigned i=0; i<data->getHeater()->get_number_of_HeatingCircles(); i++){
        if(data->getHeater()->getHeatingCircleHandler()[i].get_switch_changed() || data->getHeater()->get_heatingMode_changed()){
            data->getHeater()->getHeatingMode(&mode_tmp);
            data->getHeater()->getStatus()[i].get_variable(&status_tmp);
            if(status_tmp==true){
                Data=((i&=0x3F)<<2)|(HEATING_ON<<1)| mode_tmp;
            //output: i=3 heatingMode=true-> 0011  1  1-> id space heating on space heating mode(auto(true)/gas(false))
            }
            else{
                Data=((i&=0x3F)<<2) | (HEATING_OFF<<1) | mode_tmp;
            }
            modbus->UsingModbus(Data);
            data->getHeater()->set_heatingMode_changed(false);
            data->getHeater()->getHeatingCircleHandler()[i].set_switch_changed(false);
        }
    }
    // modbus->ACKmsgCheck();
}