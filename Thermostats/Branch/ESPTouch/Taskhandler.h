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

#include "esp_task_wdt.h"
//#include "esp_int_wdt.h"

#include "MainTask.h"
#include "GuiTask.h"
#include "SerialTask.h"
#include "InitTask.h"
#include "wifiTask.h"
#include "HeatingCommunicationTask.h"
#include "MeasuringTask.h"

#define WDT_TIMEOUT_SECONDS 60 //sec

#define NUMBER_OF_TASKS_CORE1 3
#define NUMBER_OF_TASKS_CORE0 1
#define SCREENS 4
//#define DHTPIN 27
//#define DHTTYPE DHT21

class Taskhandler{
    static DataHandler data;
    QueueHandle_t myQueue1;
    TaskHandle_t core1;

    static bool end_task_on_core_0;

    static void BIOSTask(void*parameters);
    static void Guitask(void*parameters);
    static void initTask(void*parameters);
    static void OtherTasks(void*parameters);

    void switch_wdt(bool);

public:
	Taskhandler();
    ~Taskhandler();


    void main();
};

#endif // TASKHANDLER_H