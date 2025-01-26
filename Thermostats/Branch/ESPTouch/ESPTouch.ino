#include "Taskhandler.h" 

#ifndef ESP_TASK_WDT_IDLE_CORE_MASK_ALL
#define ESP_TASK_WDT_IDLE_CORE_MASK_ALL ((1 << portNUM_PROCESSORS) - 1)
#endif

void setup(){
  Taskhandler task;
  task.main();
}
void loop(){}//look after in Taskhandler.cpp
