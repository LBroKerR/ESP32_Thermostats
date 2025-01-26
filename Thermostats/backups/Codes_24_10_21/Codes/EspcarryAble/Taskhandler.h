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
#include "wifiTask.h"

#define NUMBER_OF_TASKS_CORE1 3
#define NUMBER_OF_TASKS_CORE0 1

class Taskhandler{
    static DataHandler data;
    QueueHandle_t myQueue1;
    TaskHandle_t core1;
public:
	Taskhandler();
    ~Taskhandler();

    static void BIOSTask(void*parameters);
    static void Maintask(void*parameters);
    static void initTask(void*parameters);
    static void OtherTasks(void*parameters);


    void main();
};

#endif // TASKHANDLER_H