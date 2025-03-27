#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

const int configTICK_RATE_mHZ = configTICK_RATE_HZ/1000;

#define BUSY_WAIT(x) \
    TickType_t beforeTickCount; \
    TickType_t afterTickCount; \
    beforeTickCount = xTaskGetTickCount(); \
    do { \
        afterTickCount = xTaskGetTickCount(); \
    } while(afterTickCount - beforeTickCount < x * configTICK_RATE_HZ);

#define BUSY_WAIT_MS(x) \
    TickType_t beforeTickCount; \
    TickType_t afterTickCount; \
    beforeTickCount = xTaskGetTickCount(); \
    do { \
        afterTickCount = xTaskGetTickCount(); \
    } while(afterTickCount - beforeTickCount < x * configTICK_RATE_mHZ);
    

void vTask(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(7000);
    BaseType_t xWasDelayed;
    xLastWakeTime = xTaskGetTickCount ();
    for (;;)
    {
        xWasDelayed = xTaskDelayUntil(&xLastWakeTime, xFrequency);

        puts("Task relative deadline before work: ");
        printf("%u\n", (unsigned int) pdTICKS_TO_MS(xTaskGetAbsoluteDeadline(xTaskGetCurrentTaskHandle())));

        BUSY_WAIT_MS(4000);

        puts("Task relative deadline after work: ");
        printf("%u\n", (unsigned int) pdTICKS_TO_MS(xTaskGetRelativeDeadline(xTaskGetCurrentTaskHandle())));
    }
}

int main()
{
    TaskHandle_t task_handle = NULL;

    stdio_init_all();

    xTaskCreate(vTask, "Task", PICO_STACK_SIZE, NULL, 4, &task_handle);

    vTaskAttachDeadline(task_handle, pdMS_TO_TICKS(5000)); // 5 seconds

    vTaskStartScheduler();

    for (;;)
    {
    }

    return 0;
}