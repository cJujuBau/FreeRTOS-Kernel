#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

const int configTICK_RATE_mHZ = configTICK_RATE_HZ/1000;

const int T1_PERIOD = 2000;
const int T2_PERIOD = 3000;
const int T3_PERIOD = 6000;

const int T1_COMPUTATION_TIME = 1000;
const int T2_COMPUTATION_TIME = 1250;
const int T3_COMPUTATION_TIME = 2000;


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

void vTask1(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(T1_PERIOD);
    BaseType_t xWasDelayed;
    int iteration = 0; // Track the iteration count
    xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        iteration++;

        // Display the time at wake and the iteration
        printf("Task 1 Iteration %d - Time at wake: %u ms\n", iteration, (unsigned int) pdTICKS_TO_MS(xTaskGetTickCount()));

        BUSY_WAIT_MS(T1_COMPUTATION_TIME);

        // Display the time when work is done and the iteration
        printf("Task 1 Iteration %d - Time after work: %u ms\n", iteration, (unsigned int) pdTICKS_TO_MS(xTaskGetTickCount()));

        xWasDelayed = xTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void vTask2(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(T2_PERIOD);
    BaseType_t xWasDelayed;
    int iteration = 0; // Track the iteration count
    xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        iteration++;

        // Display the time at wake and the iteration
        printf("Task 2 Iteration %d - Time at wake: %u ms\n", iteration, (unsigned int) pdTICKS_TO_MS(xTaskGetTickCount()));

        BUSY_WAIT_MS(T2_COMPUTATION_TIME);

        // Display the time when work is done and the iteration
        printf("Task 2 Iteration %d - Time after work: %u ms\n", iteration, (unsigned int) pdTICKS_TO_MS(xTaskGetTickCount()));

        xWasDelayed = xTaskDelayUntil(&xLastWakeTime, xFrequency);
        //vTaskDelay(xFrequency);
    }
}

void vTask3(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(T3_PERIOD);
    BaseType_t xWasDelayed;
    xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        puts("Task 3 relative deadline before work: ");
        printf("%u\n", (unsigned int) pdTICKS_TO_MS(xTaskGetRelativeDeadline(xTaskGetCurrentTaskHandle())));

        BUSY_WAIT_MS(T3_COMPUTATION_TIME);

        puts("Task 3 relative deadline after work: ");
        printf("%u\n", (unsigned int) pdTICKS_TO_MS(xTaskGetRelativeDeadline(xTaskGetCurrentTaskHandle())));

        xWasDelayed = xTaskDelayUntil(&xLastWakeTime, xFrequency);
        //vTaskDelay(xFrequency);
    }
}

int main()
{
    TaskHandle_t task_handle1 = NULL;
    TaskHandle_t task_handle2 = NULL;
    TaskHandle_t task_handle3 = NULL;

    stdio_init_all();

    xTaskCreate(vTask1, "Task 1", PICO_STACK_SIZE, NULL, 2, &task_handle1);
    xTaskCreate(vTask2, "Task 2", PICO_STACK_SIZE, NULL, 2, &task_handle2);

    //xTaskCreate(vTask3, "Task 3", PICO_STACK_SIZE, NULL, 2, &task_handle3);

    vTaskAttachDeadline(task_handle1, pdMS_TO_TICKS(T1_PERIOD));
    vTaskAttachDeadline(task_handle2, pdMS_TO_TICKS(T2_PERIOD));

    //vTaskAttachDeadline(task_handle3, pdMS_TO_TICKS(T3_PERIOD));

    vTaskStartScheduler();

    for (;;)
    {
    }

    return 0;
}