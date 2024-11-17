#include "Modbus_data.h"


Modbus_data::Modbus_data(){
    slaveID=0;
    registerAddress=0;
    numRegisters=0;
}
void Modbus_data::set_data(unsigned id, uint16_t address, uint8_t num){
    slaveID=id;
    registerAddress=address;
    numRegisters=num;
}
unsigned Modbus_data::get_ID()const{
    return slaveID;
}
uint16_t Modbus_data::get_address()const{
    return registerAddress;
}
uint8_t Modbus_data::get_number()const{
    return numRegisters;
}