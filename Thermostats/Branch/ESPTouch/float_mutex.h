#pragma once
#ifndef FLOAT_MUTEX_H
#define FLOAT_MUTEX_H

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#define USE_MUTEX 1

#define MUTEX_WAIT_TIME_MS 5//portMAX_DELAY
#define MUTEX_WAIT_TICKS pdMS_TO_TICKS(MUTEX_WAIT_TIME_MS)

class float_mutex{
    float variable;
    SemaphoreHandle_t variable_mutex;
public:
    float_mutex();

    bool set_variable(float const);
    bool get_variable(float*);
};

#endif //FLOAT_MUTEX_H