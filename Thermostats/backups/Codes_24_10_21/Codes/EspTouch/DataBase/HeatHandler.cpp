#include "HeatHandler.h"

bool HeatHandler::ACKmsgCheck(){
    bool isValid = false; 
    if(Serial2.available()>0){
        uint8_t receivedData = Serial2.read(); 
        isValid = true;  // Feltételezzük, hogy az adat helyes// For ciklussal végigellenőrizzük az összes bitet
        for (int i = 0; i < 8; i++) {// Ellenőrizzük a biteket egyenként
            if (i == 0) {
                if (!(receivedData & (1 << i))) {// Az első bitnek 1-nek kell lennie
                isValid = false;  // Ha az első bit nem 1, hibás
                }
            } 
            else {
                // A többi bitnek 0-nak kell lennie
                if (receivedData & (1 << i)) {
                    isValid = false;  // Ha bármelyik más bit 1, hibás
                }
            }
        }
    }
    return isValid;
}

bool HeatHandler::UsingModbus(float wtmp){
    Serial2.begin(BAUDRATE, SERIAL_8N1, RX, TX);
    node.begin(slaveID, Serial2);  // Modbus slave ID = 1
    for(unsigned i=0; i<number_of_HeatingCircles; i++){
        if(HeatingCircles[i].Heating(wtmp)){
            Serial2.write(uint8_t(i+false+true+false+heatingMode)); //output: i=3 heatingMode=true-> 0011 0 1 0 1-> id space heating on space heating mode(auto(true)/gas(false))
            delay(1000);
        }
        while(!ACKmsgCheck()){
            //wait, while no respond-> error log!!
            delay(1000);
        }
    }
    Serial2.end();
}

HeatHandler::HeatHandler(){
    HeatingCircles=nullptr;
    number_of_HeatingCircles=0;
    bool heatingMode=false;
    unsigned slaveID=0;
}
HeatHandler::HeatHandler(unsigned slave_id){
    HeatingCircles=nullptr;
    number_of_HeatingCircles=0;
    bool heatingMode=false;
    unsigned slaveID=slave_id;
}
HeatHandler::~HeatHandler(){
    if(HeatingCircles!=nullptr){
        delete[] HeatingCircles;
    }
}

bool HeatHandler::add_HeatingCircles(){
    if(HeatingCircles==nullptr || number_of_HeatingCircles==0){
        delete[] HeatingCircles;
        number_of_HeatingCircles=0;
    }
    HeatingCircleHandler* tmp=new HeatingCircleHandler[number_of_HeatingCircles+1];
    if(HeatingCircles!=nullptr && number_of_HeatingCircles!=0){
        for (unsigned i = 0; i < number_of_HeatingCircles; i++){
            tmp[i]=HeatingCircles[i];
        }
        delete[] HeatingCircles;
        HeatingCircles=tmp;
    }
    HeatingCircles=tmp;
    number_of_HeatingCircles++;
    return true;
}

bool HeatHandler::remove_HeatingCircles(unsigned index){
    if(HeatingCircles==nullptr || number_of_HeatingCircles==0){
        return false;
    }
    if(index> 0 && index< number_of_HeatingCircles){
        HeatingCircleHandler* tmp=new HeatingCircleHandler[number_of_HeatingCircles-1];
        for(unsigned i=0; i< number_of_HeatingCircles-1; i++){
            if(i<index){
                tmp[i]=HeatingCircles[i];
            }
            else{
                tmp[i]=HeatingCircles[i+1];
            }
        }
        delete[] HeatingCircles;
        number_of_HeatingCircles--;
        return true;
    }
    return false;
}

bool HeatHandler::add_device_to_HeatingCircles(unsigned index, String const MACaddress, String const name, unsigned const Heatingid,unsigned const id){
    if(HeatingCircles==nullptr || number_of_HeatingCircles==0 ){
        return false;
    }
    if(index>=0 && index<number_of_HeatingCircles){
        if(HeatingCircles[index].addDevice(MACaddress,name,id)){
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

void HeatHandler::remove_device_from_HeatingCircles(unsigned const id){
    if(HeatingCircles==nullptr || number_of_HeatingCircles==0){
        return;
    }
    for(unsigned i=0; i<number_of_HeatingCircles; i++){
        if(HeatingCircles[i].removeDevice(id)){
            break;
        }
    }
}

    //from designed gui
void HeatHandler::setHeatingMode(bool const param){
    heatingMode=param;
}
bool HeatHandler::getHeatingMode()const{
    return heatingMode;
}
bool* HeatHandler::get_HeatingCircles_status( unsigned*size){

}