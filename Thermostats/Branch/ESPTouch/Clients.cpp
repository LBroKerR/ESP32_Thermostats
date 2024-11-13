#include "Clients.h"

Clients::Clients(){
    IPs=nullptr;
    ids=nullptr;
    status=nullptr;
    size=0;
}
   
Clients::~Clients(){
    if(IPs!=nullptr){
      delete[] IPs;
    }
    if(ids!=nullptr){
      delete[] ids;
    }
    if(status!=nullptr){
      delete[] status;
    }
}
bool Clients::add(String param, unsigned id, bool state){
    for(unsigned i=0; i<size; i++){
        if(param==IPs[i]){
          if(id!= ids[i]){
            ids[i]=id;
            status[i]=state;
          }
            return false;
        }
    }
    String*tmp=new String[size+1];
    unsigned *utmp=new unsigned[size+1];
    bool * status_tmp=new bool[size+1];
    for (unsigned i = 0; i < size; i++){
        tmp[i]=IPs[i];
        utmp[i]=ids[i];
        status_tmp[i]=status[i];
    }
    tmp[size]=param;
    utmp[size]=id;
    status_tmp[size]=state;
    delete[] IPs;
    delete[] ids;
    delete[] status;
    IPs=tmp;
    ids=utmp;
    status=status_tmp;
    size++;
    return true;
}
int Clients::Del(String param){
    int place=-1;
    if(IPs==nullptr || ids== nullptr || status==nullptr || size==0){
        delete[] IPs;
        delete[] ids;
        delete[] status;
        size=0;
        return place;
    }
    for(unsigned i=0; i<size; i++){
        if(param==IPs[i]){
            place=i;
        }
    }
    if(place>-1 ){
        String *tmp=nullptr;
        unsigned *utmp=nullptr;
        bool* status_tmp=nullptr;
        if(size>1){
            tmp=new String[size-1];
            utmp=new unsigned[size-1];
             status_tmp=new bool[size-1];
            for (unsigned i = 0; i < size-1; i++){
                if(place>i){
                    tmp[i]=IPs[i];
                    utmp[i]=ids[i];
                    status_tmp[i]=status[i];

                }
                else if(place<=i){
                    tmp[i]=IPs[i+1];
                    utmp[i]=ids[i+1];
                    status_tmp[i]=status[i+1];
                }
            }
        }
        delete[] IPs;
        delete[] ids;
        delete[] status;
        IPs=tmp;
        ids=utmp;
        status=status_tmp;
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
bool *Clients::get_status(){
    return status;
}
void Clients::set_status(bool state, unsigned id){
    for(unsigned i=0; i< size; i++){
        if(id==ids[i]){
            status[i]=state;
            return;
        }
    }
}