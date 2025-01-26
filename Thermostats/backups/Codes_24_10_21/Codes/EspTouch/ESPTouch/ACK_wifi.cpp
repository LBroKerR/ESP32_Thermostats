#include "ACK_wifi.h"

//private setters
void ACK_wifi::set_Fdata(float const param){
    Fdata=param;
}
void ACK_wifi::set_Sdata(String const param){
    Sdata=param;
}
//private getters
float ACK_wifi::get_Fdata(){
    return Fdata;
}
String ACK_wifi::get_Sdata(){
    return Sdata;
}

ACK_wifi::ACK_wifi(){
    device_MAC=" ";
    heating_circle=0;
    data_id=0;
    Fdata=0.0;
    Sdata=" ";
    ack=false;
    data=false;
}

    //setters
void ACK_wifi::set_device_MAC(String const param){
    device_MAC=param;
}
void ACK_wifi::set_heating_circle(unsigned const param){
    heating_circle=param;
}
void ACK_wifi::set_data_id(int const param){
    data_id=param;
}
void  ACK_wifi::set_data(void* param, bool Data){
    data=Data;
    if(data){
        String *str=(String*)param;
        set_Sdata(*str);
    }
    else{
        float *flt=(float*)param;
        set_Fdata(*flt);
    }
}
void ACK_wifi::set_ack(bool const param){
    ack=param;
}

    //getters
String ACK_wifi::get_device_MAC() const{
    return device_MAC;
}
unsigned ACK_wifi::get_heating_circle()const{
    return heating_circle;
}
int ACK_wifi::get_data_id()const{
    return data_id;
}
bool ACK_wifi::get_data(void*param){
    if(data){
        String str=get_Sdata();
        param=(void*)&str;
    }
    else{
        float flt=get_Fdata();
        param=(void*)&flt;
    }
    return data;
}
bool ACK_wifi::get_ack()const{
    return ack;
}