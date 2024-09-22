#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "SerialTask.h"

#include "programs.h"
#include "Clock.h"
#include "ClientWifi.h"
#include "TemperatureMeasuring.h"
#include "DataHandler.h"
#include "InitTask.h"


#define NUMBER_OF_TASKS_CORE1 2
#define NUMBER_OF_TASKS_CORE0 1

void Taskcore0(void*parameters){
  QueueHandle_t myQueue=*(QueueHandle_t*)parameters;
  TaskHandle_t receivedTaskHandle;
  if (xQueueReceive(myQueue, &receivedTaskHandle, portMAX_DELAY) == pdTRUE) {

    // Code comes here!

  }
  TaskHandle_t taskHandle = xTaskGetCurrentTaskHandle();
  xQueueSend(myQueue, &taskHandle, portMAX_DELAY);
  vTaskDelete(nullptr);
}

void Taskcore1(void*parameters){
  QueueHandle_t myQueue=*(QueueHandle_t*)parameters;
  TaskHandle_t receivedTaskHandle;
  if (xQueueReceive(myQueue, &receivedTaskHandle, portMAX_DELAY) == pdTRUE) {

    // Code comes here!

  }
  TaskHandle_t taskHandle = xTaskGetCurrentTaskHandle();
  xQueueSend(myQueue, &taskHandle, portMAX_DELAY);
  vTaskDelete(nullptr);
  
}
void BIOS(void*parameters){
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

void setup() {
  // put your setup code here, to run once:
  //DataHandler Data;
  //Taskhadler Tasks(Data);
  QueueHandle_t myQueue1 = xQueueCreate(NUMBER_OF_TASKS_CORE1, sizeof(TaskHandle_t));
  QueueHandle_t myQueue0 = xQueueCreate(NUMBER_OF_TASKS_CORE0, sizeof(TaskHandle_t));
  TaskHandle_t core1, core0;

  xTaskCreatePinnedToCore(Taskcore0, "core0", 1000, &myQueue0, 5, &core0, 0);
  xTaskCreatePinnedToCore(Taskcore1, "core1", 1000, &myQueue1, 5, &core1, 1);
  xTaskCreatePinnedToCore(BIOS, "core1", 1000, &myQueue1, 5, &core1, 1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
