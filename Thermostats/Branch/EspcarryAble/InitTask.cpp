#include "InitTask.h"

DataHandler* InitTask::main(DataHandler*parameters){
  EEPROM.begin(EEPROM_SIZE);
  delay(100);
  parameters=WifiInit(parameters);
  parameters=DataInit(parameters);
  delay(100);
  EEPROM.end();
  return parameters;
}
DataHandler* InitTask::WifiInit(DataHandler *obj){
    String name,pw;
    bool Switch=getSwitch();
    unsigned host=getHost();
    name=getUser(UPSIZE);
    pw=getPASS(UPSIZE);
    String ip=getIP();
    obj->setWifi(ip,name,pw,host,Switch);
    return obj;
}
DataHandler* InitTask::DataInit(DataHandler *obj){
    unsigned hour, min, prog,id, heatingID;
    String name=getName();
    double offset=getOffset();
    getClock(&hour,&min);
    prog=getActiveprog();
    heatingID=getNumber_of_heating_circle();
    id=getID();
    obj->setTime(hour,min);
    obj->setSensor(offset,id,heatingID,name);
    obj->getProg()->set_active_program_index(prog);
    return obj;
}

void InitTask::save(DataHandler*data){
    EEPROM.begin(EEPROM_SIZE);
    delay(100);
    saveData(data);
    delay(100);
    EEPROM.end();
}

void InitTask::saveData(DataHandler*data){
    if(data->getTime()->get_hour_Changed() || data->getTime()->get_min_Changed()){
        write_out_clock(data->getTime()->gethour(), data->getTime()->getmin());
        data->getTime()->set_hour_Changed(false);
        data->getTime()->set_min_Changed(false);
    }
        write_out_active_program_number(data->getProg()->get_active_program_index());
}