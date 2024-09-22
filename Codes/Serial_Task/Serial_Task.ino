#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "SerialTask.h"

#define NUMBER_OF_TASKS 2

void Taskcore(void* parameters){
  QueueHandle_t myQueue=*(QueueHandle_t*)parameters;
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
  //sending msg to the queue about the end of the TaskCore
  //TaskHandle_t taskHandle = xTaskGetCurrentTaskHandle();
  //xQueueSend(myQueue, &taskHandle, portMAX_DELAY);
  vTaskDelete(nullptr);
}

void task2(void* parameters){
  QueueHandle_t myQueue=*(QueueHandle_t*)parameters;
  TaskHandle_t receivedTaskHandle;
  if (xQueueReceive(myQueue, &receivedTaskHandle, portMAX_DELAY) == pdTRUE) {

    // Code comes here!

  }
  TaskHandle_t taskHandle = xTaskGetCurrentTaskHandle();
  xQueueSend(myQueue, &taskHandle, portMAX_DELAY);
  vTaskDelete(nullptr);
}


void setup() {
  // put your setup code here, to run once:
  QueueHandle_t myQueue = xQueueCreate(NUMBER_OF_TASKS, sizeof(TaskHandle_t));
  TaskHandle_t serialTask, Task2;

  xTaskCreatePinnedToCore(Taskcore, "serialTask", 10000, &myQueue, 5, &serialTask, 1);
  xTaskCreatePinnedToCore(task2, "Task2", 10000, &myQueue, 5, &Task2, 1);
}

void loop() {
}
  // put your main code here, to run repeatedly:


