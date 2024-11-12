#include "Clients.h"

Clients::Clients(){
    IPs=nullptr;
    ids=nullptr;
    size=0;
}
   
Clients::~Clients(){
    if(IPs!=nullptr){
        delete[] IPs;
    }
    if(ids!=nullptr){
      delete[] ids;
    }
}
bool Clients::add(String param, unsigned id){
    for(unsigned i=0; i<size; i++){
        if(param==IPs[i]){
          if(id!= ids[i]){
            ids[i]=id;
          }
            return false;
        }
    }
    String*tmp=new String[size+1];
    unsigned *utmp=new unsigned[size+1];
    for (unsigned i = 0; i < size; i++){
        tmp[i]=IPs[i];
        utmp[i]=ids[i];
    }
    tmp[size]=param;
    utmp[size]=id;
    delete[] IPs;
    delete[] ids;
    IPs=tmp;
    ids=utmp;
    size++;
    return true;
}
int Clients::Del(String param){
    int place=-1;
    String *tmp=nullptr;
    for(unsigned i=0; i<size; i++){
        if(param==IPs[i]){
            place=i;
        }
    }
    if(place>-1 ){
        String *tmp=nullptr;
        unsigned *utmp=nullptr;
        if(size>1){
            tmp=new String[size-1];
            utmp=new unsigned[size-1];
            for (unsigned i = 0; i < size-1; i++){
                if(place>i){
                    tmp[i]=IPs[i];
                    utmp[i]=ids[i];
                }
                else if(place<=i){
                    tmp[i]=IPs[i+1];
                    utmp[i]=ids[i+1];
                }
            }
        }
        delete[] IPs;
        delete[] ids;
        IPs=tmp;
        ids=utmp;
        size--;
    }
    return place;
}
String* Clients::get(){
    return IPs;
}
unsigned* Clients::get_ids(){
  return ids;
}
String Clients::get(unsigned param){
    if(param<size){
        return IPs[param];
    }
    return "null";
}
unsigned Clients::getSize(){
  return size;
}