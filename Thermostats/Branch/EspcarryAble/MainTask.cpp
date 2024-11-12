#include "MainTask.h"

   MainTask:: MainTask(){
    data=nullptr;
   }
   MainTask:: ~MainTask(){

   }

void MainTask::setData(DataHandler* param){
        data=param;
}
void MainTask::print(Adafruit_SSD1306 *display, ESP32Time *rtc){
  unsigned min=rtc->getMinute();
  unsigned hour=rtc->getHour(true);
    display->setTextColor(SSD1306_WHITE);
    display->clearDisplay();
    display->setTextSize(SIZE1);
    display->setCursor(HMDTXT_X, HMDPROG_Y);
    display->print("hmd:");
    display->setCursor(HMD_X, HMDPROG_Y);
    display->print(data->getSensor()->getMeasureHmd(),1);
    display->setCursor(HMDPERCEN_X, HMDPERCEN);
    display->print("%");
    display->setCursor(CLOCK_HOUR_X, CLOCK_Y );
    if(hour>=10){
      display->print(hour);
    }
    else{
      display->print("0");
      display->print(hour);
    }
    display->setCursor( CLOCK_DOTS_X, CLOCK_Y );
    display->print(":");
    display->setCursor(CLOCK_MIN_X, CLOCK_Y );
    if(min>=10){
      display->print(min);
    }
    else{
      display->print("0");
      display->print(min);
    }
    display->setTextSize(SIZE2);
    display->setCursor(TMPC_X, TMPC_Y);// x,y
    display->print("C");
    display->setCursor(TMP_X, TMP_Y);// x,y
    display->print(data->getSensor()->getMeasuredTemperature(),1);
    
   if(data->get_wifi_data()->get_switch()){
        display->setTextSize(SIZE1);
        display->setCursor(WANTEDC_X, WANTEDTMP_Y);
        display->print("C");
        display->setCursor(WANTEDTXT_X, WANTEDTMP_Y);
        display->print("wtmp:");
        display->setCursor(WANTEDTMP_X,WANTEDTMP_Y);
        display->print(data->getProg()->get_Wanted_temp(),1);// text + if its double or  float, it will printed out like this xy.z
        display->setCursor(PROGTXT_X, HMDPROG_Y);
        display->print("prog:");
        display->setCursor(PROG_X, HMDPROG_Y);
        display->print(data->getProg()->get_active_program_index()+1,1);
        display->setTextSize(SIZE2);
        display->setCursor(SWITCH_X, SWITCH_Y);
        if(data->getSwitch()){
            display->print("ON");
        }
        else{
            display->print("OFF");
        }
    }
    display->display();
}
void  MainTask::buttonInteraction(Buttons* button){
  int progbutt=0;
  double wtmp_button=0.0;
  progbutt=button->progchange();
  if(!progbutt){
    wtmp_button=button->tempchange(STEP);
    if(wtmp_button!=0.0){
      data->getProg()->set_Wanted_temp(button->tempchange(STEP));
    }
  }
  else {
    data->getProg()->set_active_program_index(progbutt);
  }
}
void MainTask::measure(DHT*sensor){
  data->getSensor()->measuring(sensor->readTemperature(), sensor->readHumidity());

}
bool MainTask::SerialExit(Buttons* button,Adafruit_SSD1306 *display){
  bool output=false;
  if( button->exit()){
    display->setTextColor(SSD1306_WHITE);
    display->clearDisplay();

    display->setTextSize(SIZE2);
    display->setCursor(TMP_X, TMP_Y);// x,y
    display->print("BIOS");

    display->display();
    output=true;
  }
  return output;
}
    void MainTask::main(DataHandler* param, ESP32Time* rtc){
        setData(param);
        DHT sensor(DHTPIN,DHTTYPE);
        sensor.begin();
        Buttons button(PLUSPIN,MINUSPIN,PROGPIN);
        Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
        while(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS));
        while(true){
            measure(&sensor);
            buttonInteraction(&button);
            print( &display, rtc);
            if(SerialExit(&button, &display)){
              return;
            }
            delay(5);
        }
    }
