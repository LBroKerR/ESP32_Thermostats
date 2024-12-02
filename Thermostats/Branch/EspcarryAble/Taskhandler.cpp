#include "Taskhandler.h"

DataHandler Taskhandler::data;
bool Taskhandler::core_0_task_disable;
Taskhandler::Taskhandler(){
    //data=new DataHandler();
    myQueue1 = xQueueCreate(NUMBER_OF_TASKS_CORE1, sizeof(TaskHandle_t));
    core_0_task_disable=false;
   // myQueue0 = xQueueCreate(NUMBER_OF_TASKS_CORE0, sizeof(TaskHandle_t));
}
Taskhandler::~Taskhandler(){
        //delete data;
}

void Taskhandler::BIOSTask(void*parameters){
  QueueHandle_t Queue=*(QueueHandle_t*)parameters;
  TaskHandle_t receivedTaskHandle;
  if (xQueueReceive(Queue, &receivedTaskHandle, portMAX_DELAY) == pdTRUE ) {
    SerialTask *bios=new SerialTask();
    bios->main();
    delete bios;
    delay(1000);
    Serial.begin(115200);
    Serial.println("Rebooting device...\n\r");
    delay(1000);
    Serial.end();
  //tells the SDK to reboot, so its a more clean reboot, use this one if possible.
    ESP.restart();
  }
  TaskHandle_t taskHandle = xTaskGetCurrentTaskHandle();
 xQueueSend(Queue, &taskHandle, portMAX_DELAY);
  vTaskDelete(nullptr);
}


void Taskhandler::Maintask(void*parameters){
  QueueHandle_t Queue=*(QueueHandle_t*)parameters;
  TaskHandle_t receivedTaskHandle;
  if (xQueueReceive(Queue, &receivedTaskHandle, portMAX_DELAY) == pdTRUE) {
    // Code comes here!
    TaskHandle_t core0;
    xTaskCreatePinnedToCore(Taskhandler::OtherTasks, "core0", 10000, NULL, 1, &core0, 0);
    MainTask *Task=new MainTask();
    ESP32Time rtc;
    if(data.get_wifi_data()->get_switch()){
      rtc.setTime(1, data.getTime()->getmin(), data.getTime()->gethour(), DAY, MONTH, YEAR);
         //          s   m   h+1  d    m      y
    }
    Task->main(&data, &rtc);
    delay(100);
    delete Task;
    delay(100);
    core_0_task_disable=true;
    vTaskDelete(core0);
  }
  TaskHandle_t taskHandle = xTaskGetCurrentTaskHandle();
  xQueueSend(Queue, &taskHandle, portMAX_DELAY);
  vTaskDelete(nullptr);
}


void Taskhandler::initTask(void*parameters){
  QueueHandle_t Queue=*(QueueHandle_t*)parameters;
  TaskHandle_t receivedTaskHandle;
  //if (xQueueReceive(Queue, &receivedTaskHandle, portMAX_DELAY) == pdTRUE) {
    InitTask *task=new InitTask();
    task->main(&data);
    delete task;
  //}
  TaskHandle_t taskHandle = xTaskGetCurrentTaskHandle();
  xQueueSend(Queue, &taskHandle, portMAX_DELAY);
  vTaskDelete(nullptr);
}


void Taskhandler::OtherTasks(void*parameters){
    if(data.get_wifi_data()->get_switch()){
     // Serial.begin(115200);
        wifiTask wifi(&data);
        InitTask task;
      while(!core_0_task_disable){
        wifi.main();
        task.save(&data);
        vTaskDelay(10 / portTICK_PERIOD_MS);
      }
      //Serial.end();
    }
    while(true){
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}



void Taskhandler::main(){
  xTaskCreatePinnedToCore(Taskhandler::initTask, "core1", 10000, &myQueue1, 5, &core1, 1);
  xTaskCreatePinnedToCore(Taskhandler::Maintask, "core1", 10000, &myQueue1, 5, &core1, 1);
  xTaskCreatePinnedToCore(Taskhandler::BIOSTask, "core1", 10000, &myQueue1, 5, &core1, 1);
}