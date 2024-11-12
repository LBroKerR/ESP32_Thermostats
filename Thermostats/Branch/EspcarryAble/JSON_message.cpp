#include "JSON_message.h"

JSON_message::JSON_message(){
    msg=nullptr;
    ip=nullptr;
    number_of_msg=0;
}
JSON_message::~JSON_message(){
    if(msg!=nullptr){
        delete[] msg;
    }
    if(ip!=nullptr){
        delete[] ip;
    }
}
void JSON_message::add_msg(String str, String IP){
    if(msg==nullptr || number_of_msg==0 || ip==nullptr){
        delete[] msg;
        delete[] ip;
        number_of_msg=0;
    }
    else{
        for (unsigned i = 0; i <  number_of_msg; i++){
            if(str==msg[i]){
                return;
            }
            else if(IP==ip[i]){
                msg[i]=str;
                return;
            }
        }
    }
    String*tmp=new String[number_of_msg+1];
    String*tmp_ip=new String[number_of_msg+1];
    for (unsigned i = 0; i < number_of_msg; i++){
        tmp[i]=msg[i];
        tmp_ip[i]=ip[i];
    }
    tmp[number_of_msg]=str;
    tmp_ip[number_of_msg]=IP;
    delete[] ip;
    delete[] msg;
    msg=tmp;
    ip=tmp_ip;
    number_of_msg++;
}
void JSON_message::remove_msg(unsigned index){
    if(msg==nullptr || number_of_msg==0 || ip==nullptr){
        delete[] msg;
        delete[] ip;
        number_of_msg=0;
        return;
    }
    if(index> number_of_msg){
        return;
    }
    String*tmp=nullptr;
    String*tmp_ip=nullptr;
    if(number_of_msg>1){
        tmp=new String[number_of_msg-1];
        tmp_ip=new String[number_of_msg-1];
        for(unsigned i=0; i<number_of_msg-1; i++){
            if(i<index){
                tmp[i]=msg[i];
                tmp_ip[i]=ip[i];
            }
            else if(i>=index){
                tmp[i]=msg[i+1];
                tmp_ip[i]=ip[i+1];
            }
        }
    }
    delete[] msg;
    delete[] ip;
    ip=tmp_ip;
    msg=tmp;
    number_of_msg--;
}

String* JSON_message::get_msg_array(){
    return msg;
}
String  JSON_message::get_msg(unsigned i){
    if(i<number_of_msg){
        return msg[i];
    }
}
unsigned JSON_message::size()const{
  return number_of_msg;
}

String* JSON_message::get_ip_array(){
    return ip;
}