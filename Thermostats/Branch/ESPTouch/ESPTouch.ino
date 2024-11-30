#include "esp_task_wdt.h"
#include "Taskhandler.h" 

#ifndef ESP_TASK_WDT_IDLE_CORE_MASK_ALL
#define ESP_TASK_WDT_IDLE_CORE_MASK_ALL ((1 << portNUM_PROCESSORS) - 1)
#endif

void setup(){
   esp_task_wdt_config_t wdt_config = {
      .timeout_ms = 10000, // Timeout in milliseconds (10 seconds)
     .idle_core_mask = ESP_TASK_WDT_IDLE_CORE_MASK_ALL, // Monitor all CPU cores
      .trigger_panic = true // Trigger a panic on timeout
  };
   esp_task_wdt_init(&wdt_config);
  Taskhandler task;
  task.main();
}
void loop(){}//look after in Taskhandler.cpp
