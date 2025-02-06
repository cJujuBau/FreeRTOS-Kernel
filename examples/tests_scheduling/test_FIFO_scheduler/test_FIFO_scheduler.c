#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "task.h"

// Taille de pile et priorité des tâches
#define STACK_SIZE configMINIMAL_STACK_SIZE
#define TASK_PRIORITY 1

// Prototypes des tâches
void Task1(void *pvParameters);
void Task2(void *pvParameters);
void Task3(void *pvParameters);

// Fonction principale
int main(void) {
    stdio_init_all();

    // Création des tâches avec la même priorité
    xTaskCreate(Task1, "Task1", STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(Task2, "Task2", STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(Task3, "Task3", STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    // Démarrer l'ordonnanceur
    vTaskStartScheduler();

    // Normalement, on ne doit jamais atteindre cette ligne
    for (;;);
    return 0;
}

void Task1(void *pvParameters) {
    while (1) {
        printf("Task1 exécutée\n");
        vTaskDelay(pdMS_TO_TICKS(500));  // Pause pour observer l'alternance
    }
}

void Task2(void *pvParameters) {
    while (1) {
        printf("Task2 exécutée\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void Task3(void *pvParameters) {
    while (1) {
        printf("Task3 exécutée\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
