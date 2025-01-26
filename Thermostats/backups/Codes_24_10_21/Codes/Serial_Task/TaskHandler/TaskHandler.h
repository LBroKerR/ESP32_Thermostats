#pragma once
#ifndef TASKHANDLER_H
#define TASKHANDLER_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

//include all the tasks
//upload them to the queue
//think about the sequence in each core, or how to work the task separatly from each other. in 2 proccesor core.
// interupts? to load tasks to a free core?

#define NUMBER_OF_TASKS 2

class TaskHandler{

    QueueHandle_t myQueue;

public:

TaskHandler();
~TaskHandler();

void InitTasks();

void main(void*parameters, unsigned* size);

};
#endif // TASKHANDLER_H