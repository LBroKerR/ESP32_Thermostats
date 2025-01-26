#pragma once
#ifndef TASKHANDLER_H
#define TASKHANDLER_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include "SerialTask.h"
#include "MainTask.h"
#include "DataHandler.h"
#include <ESP32Time.h>
#include "InitTask.h"


#define NUMBER_OF_TASKS_CORE1 3
#define NUMBER_OF_TASKS_CORE0 1

class Taskhandler{
    DataHandler* data;
    QueueHandle_t myQueue1, myQueue0;
    TaskHandle_t core1, core0;
public:
	Taskhandler();
    ~Taskhandler();

    void BIOSTask(void*parameters);
    void Maintask(void*parameters);
    void initTask(void*parameters);
    void OtherTasks(void*parameters);

    void main();
};

#endif // TASKHANDLER_H