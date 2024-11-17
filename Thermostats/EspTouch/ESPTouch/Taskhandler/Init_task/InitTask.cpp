#include "InitTask.h"

    DataHandler* InitTask::WifiInit(DataHandler *obj){
        String pw,user;
        unsigned host=getHost();
        pw=getPASS(UPSIZE);
        user=getUser(UPSIZE);
        obj->set_wifi(user,pw,host,getSwitch());
      return obj;
    }

    DataHandler* InitTask::ProgInit(DataHandler *obj){
      unsigned active_prog=0;
      double Defaultprog[24];
      double alprogs[24];
      for(unsigned i=0; i<24; i++){
        Defaultprog[i]=20.0;
        alprogs[i]=10.0;
      }
      active_prog=getActiveprog();
      for(unsigned i=0; i<5; i++){
        if(!getProgram(i,alprogs)){
          *alprogs=*Defaultprog;
        }
        obj->getProg()->set_programs(alprogs,i);
      }
      obj->getProg()->set_active_program_index(active_prog);
      obj->getProg()->set_Wanted_temp( obj->getProg()->get_program_element( obj->getTime()->gethour() ) );
      return obj;
    }
    DataHandler* InitTask::ClockInit(DataHandler *obj){
      unsigned hour=0, min=0;
      getClock(&hour, &min);
      obj->setTime(hour, min);
      return obj;
    }
    DataHandler* InitTask::HeaterInit(DataHandler *obj){
      unsigned heating_circle_Number_ID=0; // how many heating circle will be implemented
      unsigned id=0; // tells where to belong among in heating circle 
      // id>0 and id<=heating_circle_Number_ID
      float offset=getOffset();
      String name=getName();
      heating_circle_Number_ID=getNumber_of_heating_circle();
      id=getID();
      obj->getHeater()->add_HeatingCircles(heating_circle_Number_ID);
      obj->getHeater()->add_Measuringsensor(id-1, offset, id-1,name);
      obj->getHeater()->setHeatingMode(read_heating_mode());
      obj->getHeater()->set_modbus_data(get_modbus_id(),get_modbus_register_address(),get_modbus_register_number());
      return obj;
    }


    DataHandler* InitTask::DataInit(DataHandler *obj){
      obj=ClockInit(obj);
      obj=HeaterInit(obj);
      obj=ProgInit(obj);
      obj->getProg()->set_ProgHour_index(obj->getTime()->gethour());
      return obj;
    }
    void InitTask::saveData(DataHandler*obj){
      //prog index, progs, hour, min
      if(obj->getTime()->get_hour_Changed() || obj->getTime()->get_min_Changed()){
        write_out_clock(obj->getTime()->gethour(),obj->getTime()->getmin());
      if(obj->getTime()->get_hour_Changed()){
        obj->getProg()->set_Wanted_temp(obj->getProg()->get_program_element(obj->getTime()->gethour()));
      }
        obj->getTime()->set_hour_Changed(false);
        obj->getTime()->set_min_Changed(false);
      }
        write_out_active_program_number(obj->getProg()->get_active_program_index());
      save_heating_mode(obj->getHeater()->getHeatingMode());
      if(obj->getProgSave()){
        double tmp[24];
        for(unsigned i=0; i<5;i++){
          for(unsigned k=0; k<24; k++){
            tmp[k]=(double)obj->getProg()->get_programs(i)[k];
          }
          write_out_full_program(i,tmp);
        }
        obj->setProgSave(false);
      }
    }
   void InitTask::print(DataHandler*parameters){
    Serial.begin(115200);
    delay(100);
    String str=" ";
    if(parameters->get_wifi_data()==nullptr){
      str+="Wifi disabled!";
    }
    if(parameters->getTime()!=nullptr){
       str+="\n"+ String(parameters->getTime()->gethour())+" : "+String(parameters->getTime()->getmin());
    }
    if(parameters->getHeater()!=nullptr){
      if(parameters->getHeater()->getHeatingCircleHandler()!=nullptr){
        unsigned index=parameters->getHeater()->get_number_of_HeatingCircles();
        for(unsigned i=0; i<index; i++){
          if(parameters->getHeater()->getHeatingCircleHandler()[i].getSensor()!=nullptr){
            str+="\n"+String(parameters->getHeater()->getHeatingCircleHandler()[i].getSensor()->getMeasuredTemperature())+ "  "+String(parameters->getHeater()->getHeatingCircleHandler()[i].getSensor()->getMeasureHmd());
          }
          else
          {
            str+="\n\r"+String(i)+". sensor null\n\r";
          }
        }
      }
      else
      {
        str+="HeaterCircle null";
      }
    }
    else{
       str+="Heater null";
    }
    Serial.println(str);
    str=" ";
    if(parameters->getProg()!=nullptr){
       str+="\n\r"+String(parameters->getProg()->get_wtmp_changed());
       str+=" ,"+ String(parameters->getProg()->get_active_program_index());
       str+="\n\r";
       float *tmp;
       for(unsigned i=0; i<5; i++){
        tmp=parameters->getProg()->get_programs(i);
         str+=String(i+1)+".\n\r";
         if(tmp!=nullptr){
          for(unsigned k=0; k<24; k++){
           str+=String(tmp[i])+" ";
          }
        }
        Serial.println(str);
        str=" ";
       }
    }
    delay(100);
    Serial.end();
   }
    DataHandler *InitTask::main(DataHandler*parameters){
      EEPROM.begin(EEPROM_SIZE);
      delay(100);
      parameters=WifiInit(parameters);
      parameters=DataInit(parameters);
      delay(100);
      EEPROM.end();
      //print(parameters);
      return parameters;
    }
    void InitTask::save(DataHandler*parameters){
      EEPROM.begin(EEPROM_SIZE);
      delay(100);
      saveData(parameters);
      delay(100);
      EEPROM.end();
    }
