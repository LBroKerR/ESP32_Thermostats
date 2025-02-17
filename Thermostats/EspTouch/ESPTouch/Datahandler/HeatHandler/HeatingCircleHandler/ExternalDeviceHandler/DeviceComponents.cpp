#include "DeviceComponents.h"

DeviceComponents::DeviceComponents(){
    devices=nullptr;
    number_of_comp=0;
    changed=false;
}
DeviceComponents::~DeviceComponents(){
    delete[] devices;
}

unsigned DeviceComponents::getSize()const{
    return number_of_comp;
}

void DeviceComponents::add_Component(String Mac, String name, float temp, unsigned id, String ip){
    if(devices==nullptr ||  number_of_comp==0){
        delete[] devices;
         devices = nullptr;
        number_of_comp=0;
    }
    Components* tmp=new Components[number_of_comp+1];
    for(unsigned i=0; i<number_of_comp; i++){
        tmp[i]=devices[i];
    }
    delete[] devices;
    tmp[number_of_comp].fillout(Mac,name,temp,5+(number_of_comp*55), id );
    tmp[number_of_comp].set_ip(ip);
    devices=tmp;
    number_of_comp++;
    changed=true;
}
bool DeviceComponents::remove_Component(String ip) {
    if (devices == nullptr || number_of_comp == 0) {
        return false; // Itt nem kell delete[] hívás
    }
    int index = -1;
    for (unsigned i = 0; i < number_of_comp; i++) {
        if (ip == devices[i].get_ip()) {
            index = i;
            break; // Ha megtaláltuk, nem kell tovább keresni
        }
    }
    if (index > -1) {
        Components* tmp = nullptr;
        // Csak akkor hozzunk létre új tömböt, ha több mint egy elem marad
        if (number_of_comp > 1) {
            tmp = new Components[number_of_comp - 1];
            for (unsigned i = 0; i < number_of_comp - 1; i++) {
                if (i < index) {
                    tmp[i] = devices[i];
                } else {
                    tmp[i] = devices[i + 1];
                }
            }
        }
        if(devices!=nullptr){
            delete[] devices; // Régi tömb felszabadítása
            devices = nullptr;
        }
        if(tmp!=nullptr){
            devices = tmp;    // Új tömb átvétele
        }
        number_of_comp--;
        changed = true;
        return true;
    }
    return false; // Ha az elem nem található
}
Components* DeviceComponents::getDevices(){
  return devices;
}
void DeviceComponents::Set_changed(bool const param){
  changed=param;
}
bool DeviceComponents::get_changed()const{
  return changed;
}