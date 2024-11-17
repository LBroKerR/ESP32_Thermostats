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
    uint8_t Data;
    data->getHeater()->get_HeatingCircles_status(data->getProg()->get_Wanted_temp());
    if(modbus==nullptr){
        return;
    }
    for(unsigned i=0; i<data->getHeater()->get_number_of_HeatingCircles(); i++){
        if(data->getHeater()->getHeatingCircleHandler()[i].get_switch_changed() || data->getHeater()->get_heatingMode_changed()){
            if(data->getHeater()->getStatus()[i]==true){
                Data=((i&=0x3F)<<2)|(HEATING_ON<<1)| data->getHeater()->getHeatingMode();
            //output: i=3 heatingMode=true-> 0011  1  1-> id space heating on space heating mode(auto(true)/gas(false))
            }
            else{
                Data=((i&=0x3F)<<2) | (HEATING_OFF<<1) | data->getHeater()->getHeatingMode();
            }
            modbus->UsingModbus(Data);
            data->getHeater()->set_heatingMode_changed(false);
            data->getHeater()->getHeatingCircleHandler()[i].set_switch_changed(false);
        }
    }
    // modbus->ACKmsgCheck();
}