#include "InitTask.h"

void InitTask::main(void*parameters, unsigned size){
    DataHandler *obj=(DataHandler*)parameters;
    obj=WifiInit(obj);
    obj=DataInit(obj);
    parameters=(void*)obj;
    return;
}
DataHandler *InitTask::WifiInit(DataHandler *obj){
    String name,pw;
    EEPROM.begin(EEPROM_SIZE);delay(100);
    bool Switch=getSwitch();
    unsigned host=getHost();
    name=getUser(UPSIZE);
    pw=getPASS(UPSIZE);
    String ip=getIP();
    obj->setWifi(ip,name,pw,host,Switch);
    EEPROM.end();delay(100);
    if(Switch){
        obj->getWifi()->IsconnectedToWifi();
    }
    return obj;
}
DataHandler* InitTask::DataInit(DataHandler *obj){
    unsigned hour, min, prog,id;
    String name=getName();
    double offset=getOffset();
    getClock(&hour,&min);
    prog=getActiveprog();
    id=getID();
    obj->setTime(hour,min);
    obj->setSensor(offset,id,name);
    obj->getProg()->set_active_program_index(prog);
    return obj;
}