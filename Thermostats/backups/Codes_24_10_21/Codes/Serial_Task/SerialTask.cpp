#include "SerialTask.h"

SerialTask::SerialTask(){
  menu = nullptr;
  IO = new SerialPortHandler();
  init();
  incomingData="";
}
SerialTask::SerialTask(SerialPortHandler *param){
  menu = nullptr;
  IO = param;
  init();
  incomingData="";
}

SerialTask::~SerialTask(){
  	delete menu;
	  delete IO;
}

void SerialTask::init() {
	if (menu!= nullptr) {
		delete menu;
	}
	menu = new MenuHandler();
	menu->addFunctions("hardreset", Hardreset);
    menu->addFunctions("read", print);
	MenuHandler* setparams = new MenuHandler();
	setparams->addFunctions("temp", check_temp_datagramm);
	setparams->addFunctions("NickName", check_Nickname_datagramm);
	setparams->addFunctions("ID", check_ID_datagramm);
#if(ESPTOUCH && !ESPCARRY)
	setparams->addFunctions("HeatingID", check_number_of_heating_circle_datagramm);
#endif
	MenuHandler* wifimenu= new MenuHandler();
	MenuHandler* clock= new MenuHandler();
	clock->addFunctions("hour", check_hour_datagramm);
	clock->addFunctions("min", check_min_datagramm);
#if(!ESPTOUCH && ESPCARRY)
	wifimenu->addFunctions("ip", check_IP_datagramm);
#endif
	wifimenu->addFunctions("host", check_host_datagramm);
	wifimenu->addFunctions("pass", check_pass_datagramm);
	wifimenu->addFunctions("user", check_user_datagramm);
	wifimenu->addFunctions("wifi", check_switch_datagramm);
	setparams->addSideMenus("clock", clock);
	setparams->addSideMenus("wifimenu", wifimenu);
	menu->addSideMenus("settings", setparams);
}
void SerialTask::functioncalling(MenuHandler*head,bool(*func)(void*)){
  String tmp="";
      if(head!=menu){
        IO->getdata(&incomingData);
      }
      else if(IO->useStack(&tmp)){
          incomingData=tmp;
      }
      IO->prints("Loading...");
      Serial.end();delay(100);
      EEPROM.begin(EEPROM_SIZE);delay(100);
      bool output=func((void*)&incomingData);
      EEPROM.end();delay(100);
      Serial.begin(BAUDRATE);delay(100);
		  if(!output){//log error!
        IO->prints((incomingData+="\n\rIncorrect input!"));
      }
      else{
        IO->prints(incomingData+="\n\rCall succeeded!");
      }
}


bool SerialTask::system(MenuHandler*&head) {
  incomingData="";
	MenuHandler* tmp=nullptr;
  bool(*tmpfunc)(void*) = nullptr;
  if(IO->Input(&incomingData, "")){
    if (!head->menu(&incomingData, tmp, &tmpfunc)) {//quit
	    return false;
    }
	  if (tmp == nullptr && tmpfunc == nullptr) {
		  if (incomingData != "") {//function: help
			  tmp = head;
			  IO->prints(incomingData);
		  }
		  else {
			  head = tmp; // cancel
		  }
		  return true;
	  }
	  else if (tmpfunc == nullptr) {//next menu
		  head = tmp;
		  return true;
	  }
	  else if (tmp == nullptr) {
      functioncalling(head,tmpfunc);
      head=tmp;
	  }
  }
	return true;
}
void SerialTask::main() {
	MenuHandler* tmp = nullptr;
	tmp = menu;
  IO->printshelp();
	while (true) {
		if (!system(tmp)) {
			break;
		}
		if (tmp == nullptr) {
      tmp=menu;
		}
    vTaskDelay(10 / portTICK_PERIOD_MS);
	}
  Serial.end();
	//_CrtDumpMemoryLeaks();
}