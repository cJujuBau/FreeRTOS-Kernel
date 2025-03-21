#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

void vTask1(void *pvParameters)
{
    for (;;)
    {
        puts("Task 1 deadline: ");
        //printf("%u\n", (unsigned int) pdTICKS_TO_MS(xTaskGetRelativeDeadline(xTaskGetCurrentTaskHandle())));
        vTaskDelay(pdMS_TO_TICKS(4000));
    }
}

void vTask2(void *pvParameters)
{
    for (;;)
    {
        puts("Task 2 deadline: ");
        //printf("%u\n", (unsigned int) pdTICKS_TO_MS(xTaskGetRelativeDeadline(xTaskGetCurrentTaskHandle())));
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void vTask3(void *pvParameters)
{    
    for (;;)
    {
        puts("Task 3 deadline: ");
        //printf("%u\n", (unsigned int) pdTICKS_TO_MS(xTaskGetRelativeDeadline(xTaskGetCurrentTaskHandle())));
        vTaskDelay(pdMS_TO_TICKS(6000));
    }
}

int main()
{
    TaskHandle_t task_handle1 = NULL;
    TaskHandle_t task_handle2 = NULL;
    TaskHandle_t task_handle3 = NULL;

    stdio_init_all();

    xTaskCreate(vTask1, "Task 1", PICO_STACK_SIZE, NULL, 4, &task_handle1);
    xTaskCreate(vTask2, "Task 2", PICO_STACK_SIZE, NULL, 2, &task_handle2);
    xTaskCreate(vTask3, "Task 3", PICO_STACK_SIZE, NULL, 2, &task_handle3);

    vTaskAttachDeadline(task_handle1, pdMS_TO_TICKS(1000)); // 1 second
    vTaskAttachDeadline(task_handle2, pdMS_TO_TICKS(2000)); // 2 seconds
    vTaskAttachDeadline(task_handle3, pdMS_TO_TICKS(3000)); // 3 seconds

    vTaskStartScheduler();

    for (;;)
    {
    }

    return 0;
}