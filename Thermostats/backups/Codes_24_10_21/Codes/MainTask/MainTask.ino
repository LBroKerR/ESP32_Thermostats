#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include "MainTask.h"
#include "DataHandler.h"
#include <ESP32Time.h>

void MTask(void* parameters){
  DataHandler* data=(DataHandler*)parameters;
  MainTask *Task=new MainTask();
  ESP32Time rtc;
  Serial.begin(115200);
  rtc.setTime(1, data->getTime()->getmin(), data->getTime()->gethour(), DAY, MONTH, YEAR);
            //          s   m   h+1  d    m      y
  Task->main(data, &rtc);
  delay(100);
  delete data;
  delete Task;
  delay(100);
  vTaskDelete(nullptr);
}

void setup() {
  // put your setup code here, to run once:
  TaskHandle_t maintask;
  DataHandler* data=new DataHandler();
  data->setTime(20, 7);
  data->setSensor(-1.6, 0, "test");
  data->setWifi("asd", "asd", "asd", 1234, false);
  xTaskCreatePinnedToCore(MTask, "maintask", 10000, data, 5, &maintask, 1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
