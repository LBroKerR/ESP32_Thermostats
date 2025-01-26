#pragma once
#ifndef BOOL_MUTEX_H
#define BOOL_MUTEX_H

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>


#define MUTEX_WAIT_TIME_MS 5
#define MUTEX_WAIT_TICKS pdMS_TO_TICKS(MUTEX_WAIT_TIME_MS)

class bool_mutex{
    bool variable;
    SemaphoreHandle_t variable_mutex;
public:
    bool_mutex();

    bool set_variable(bool const);
    bool get_variable(bool*);
};

#endif //BOOL_MUTEX_H