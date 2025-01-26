#include "Taskhandler.h"

Taskhandler(){
    data=new DataHandler();
    myQueue1 = xQueueCreate(NUMBER_OF_TASKS_CORE1, sizeof(TaskHandle_t));
    myQueue0 = xQueueCreate(NUMBER_OF_TASKS_CORE0, sizeof(TaskHandle_t));
}
~Taskhandler(){
        delete data;
}

void Taskhandler::BIOSTask(void*parameters){
  QueueHandle_t myQueue=*(QueueHandle_t*)parameters;
  TaskHandle_t receivedTaskHandle;
  if (xQueueReceive(myQueue, &receivedTaskHandle, portMAX_DELAY) == pdTRUE) {
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
  xQueueSend(myQueue, &taskHandle, portMAX_DELAY);
  vTaskDelete(nullptr);
}
void Taskhandler::Maintask(void*parameters){
  QueueHandle_t myQueue=*(QueueHandle_t*)parameters;
  TaskHandle_t receivedTaskHandle;
  if (xQueueReceive(myQueue, &receivedTaskHandle, portMAX_DELAY) == pdTRUE) {
    // Code comes here!
    MainTask *Task=new MainTask();
    ESP32Time rtc;
    Serial.begin(115200);
    rtc.setTime(1, data->getTime()->getmin(), data->getTime()->gethour(), DAY, MONTH, YEAR);
            //          s   m   h+1  d    m      y
    Task->main(data, &rtc);
    delay(100);
    delete Task;
    delay(100);

  }
  TaskHandle_t taskHandle = xTaskGetCurrentTaskHandle();
  xQueueSend(myQueue, &taskHandle, portMAX_DELAY);
  vTaskDelete(nullptr);
}
void Taskhandler::initTask(void*parameters){
    QueueHandle_t myQueue=*(QueueHandle_t*)parameters;
    TaskHandle_t receivedTaskHandle;
 // if (xQueueReceive(myQueue, &receivedTaskHandle, portMAX_DELAY) == pdTRUE) {
    InitTask *task=new InitTask();
    task->main(data);
    delete task;
  //}
  TaskHandle_t taskHandle = xTaskGetCurrentTaskHandle();
  xQueueSend(myQueue, &taskHandle, portMAX_DELAY);
  vTaskDelete(nullptr);
}
void Taskhandler::OtherTasks(void*parameters){

}

void Taskhandler::main(){
  xTaskCreatePinnedToCore(Taskhandler::initTask, "core1", 10000, &myQueue1, 5, &core1, 1);
  xTaskCreatePinnedToCore(Taskhandler::Maintask, "core1", 10000, &myQueue1, 5, &core1, 1);
  xTaskCreatePinnedToCore(Taskhandler::BIOSTask, "core1", 10000, &myQueue1, 5, &core1, 1);
  //xTaskCreatePinnedToCore(Taskhandler::OtherTasks, "core0", 10000, &myQueue0, 5, &core0, 0);
}