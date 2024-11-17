#pragma once
#ifndef TASKHANDLER_H
#define TASKHANDLER_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <Arduino.h>
#include <DHT.h>
#include <ESP32Time.h>

#include "DataHandler.h"

#include "MainTask.h"
#include "GuiTask.h"
#include "SerialTask.h"
#include "InitTask.h"
#include "wifiTask.h"
#include "HeatingCommunicationTask.h"

#define NUMBER_OF_TASKS_CORE1 3
#define NUMBER_OF_TASKS_CORE0 1
#define SCREENS 4
#define DHTPIN 27
#define DHTTYPE DHT11

class Taskhandler{
    static DataHandler data;
    QueueHandle_t myQueue1;
    TaskHandle_t core1;

    static bool end_task_on_core_0;

public:
	Taskhandler();
    ~Taskhandler();

    static void BIOSTask(void*parameters);
    static void Guitask(void*parameters);
    static void initTask(void*parameters);
    static void OtherTasks(void*parameters);


    void main();
};

#endif // TASKHANDLER_H