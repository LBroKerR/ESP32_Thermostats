#include "modbusHandler.h"

modbusHandler::modbusHandler(){
    slaveID=1;
    registerAddress=0x0001;
    numRegisters=1;
    messages=nullptr;
    number_of_msg=0;
    node.begin(slaveID, Serial2);
    Serial2.begin(BAUDRATE, SERIAL_8N1, RX, TX);
    delay(100);
}
modbusHandler::modbusHandler(unsigned id, uint16_t register_address, uint8_t num_reg){
    slaveID=id;
    registerAddress=register_address;
    numRegisters=num_reg;
    messages=nullptr;
    number_of_msg=0;
    node.begin(slaveID, Serial2);
    Serial2.begin(BAUDRATE, SERIAL_8N1, RX, TX);
    delay(100);
}
modbusHandler::~modbusHandler(){
    delay(100);
    Serial2.end();
    if(messages!=nullptr){
        delete[] messages;
    }
}

void modbusHandler::add_msg(uint8_t msg){
    if(messages==nullptr || number_of_msg==0){
        delete[] messages;
        number_of_msg=0;
        return;
    }
    uint8_t*tmp=new uint8_t[number_of_msg+1];
    for(unsigned i=0; i<number_of_msg; i++){
        tmp[i]=messages[i];
    }
    tmp[number_of_msg]=msg;
    delete[] messages;
    messages=tmp;
    number_of_msg++;
}
void modbusHandler::remove_msg(uint8_t ack_ed_msg){
    if(messages==nullptr || number_of_msg==0){
        delete[] messages;
        number_of_msg=0;
        return;
    }
    uint8_t*tmp=nullptr;
    unsigned location=0;
    for(unsigned i=0; i<number_of_msg; i++){
        if( ack_ed_msg==messages[i]){
            tmp=new uint8_t[number_of_msg-1];
            location=i;
            break;
        }
    }
    if(tmp==nullptr){
        return;
    }
    for(unsigned i=0; i<number_of_msg-1; i++){
        if(i<location){
            tmp[i]=messages[i];
        }else if(i>=location){
            tmp[i]=messages[i+1];
        }
    }
    delete[] messages;
    messages=tmp;
    number_of_msg--;
}

void modbusHandler::ACKmsgCheck(){
    bool isValid = false; 
    if (node.available()) {
        uint8_t result = node.readHoldingRegisters(registerAddress, numRegisters);
        if (result == node.ku8MBSuccess) {
            uint16_t data = node.getResponseBuffer(0);  // Get the first value from the response buffer
            Serial2.print("Read value: ");
            Serial2.println( data);
            isValid=true;
        } else {
            Serial2.print("Read failed. Error: ");
            Serial2.println(result, HEX);
        }
        if(isValid && (unsigned) result==1){
            return;
        }
    }
    return;

}
void modbusHandler::UsingModbus(uint8_t data){

    node.writeSingleRegister(0x0001, data);
    Serial2.println(data);
    if (data != node.ku8MBSuccess) {
        Serial2.println("Write failed!");
    }

}