#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "task.h"


/* Tester le fonctionnement en modifiant configUSE_TASK_PRIORITIES dans FreeRTOSConfig.h */
void TaskFunction(void *pvParameters);

int main() {
    TaskHandle_t task1 = NULL, task2 = NULL, task3 = NULL;

    stdio_init_all();

    xTaskCreate(TaskFunction, "Task1", PICO_STACK_SIZE, NULL, 2, &task1);
    xTaskCreate(TaskFunction, "Task2", PICO_STACK_SIZE, NULL, 1, &task2);
    xTaskCreate(TaskFunction, "Task3", PICO_STACK_SIZE, NULL, 0, &task3);

    vTaskStartScheduler();

    while (1){
    };

    return 0;
}

void TaskFunction(void *pvParameters) {
    while(1){
        UBaseType_t priority = uxTaskPriorityGet(NULL);
        printf("%s running with priority %lu\n", pcTaskGetName(NULL), (unsigned long)priority);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}