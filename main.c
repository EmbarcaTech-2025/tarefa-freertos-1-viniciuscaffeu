#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

// Definições dos pinos da BitDogLab
#define PIN_LED_R 13
#define PIN_LED_G 11
#define PIN_LED_B 12
#define PIN_BUZZER 10
#define PIN_BTN_A 5
#define PIN_BTN_B 6

// Handles das tarefas
TaskHandle_t ledTaskHandle;
TaskHandle_t buzzerTaskHandle;

// Tarefa do LED RGB
void led_task(void *params) {
    while (1) {
        // Vermelho
        gpio_put(PIN_LED_R, 1);
        gpio_put(PIN_LED_G, 0);
        gpio_put(PIN_LED_B, 0);
        vTaskDelay(pdMS_TO_TICKS(500));

        // Verde
        gpio_put(PIN_LED_R, 0);
        gpio_put(PIN_LED_G, 1);
        gpio_put(PIN_LED_B, 0);
        vTaskDelay(pdMS_TO_TICKS(500));

        // Azul
        gpio_put(PIN_LED_R, 0);
        gpio_put(PIN_LED_G, 0);
        gpio_put(PIN_LED_B, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// Tarefa do Buzzer
void buzzer_task(void *params) {
    while (1) {
        gpio_put(PIN_BUZZER, 1);
        vTaskDelay(pdMS_TO_TICKS(100)); // Beep curto
        gpio_put(PIN_BUZZER, 0);
        vTaskDelay(pdMS_TO_TICKS(900));
    }
}

// Tarefa dos botões
void button_task(void *params) {
    bool ledSuspenso = false;
    bool buzzerSuspenso = false;

    while (1) {
        // Botão A
        if (gpio_get(PIN_BTN_A) == 0) { // Pressionado (ativo em 0)
            if (!ledSuspenso) {
                vTaskSuspend(ledTaskHandle);
                ledSuspenso = true;
            }
        } else {
            if (ledSuspenso) {
                vTaskResume(ledTaskHandle);
                ledSuspenso = false;
            }
        }

        // Botão B
        if (gpio_get(PIN_BTN_B) == 0) {
            if (!buzzerSuspenso) {
                vTaskSuspend(buzzerTaskHandle);
                buzzerSuspenso = true;
            }
        } else {
            if (buzzerSuspenso) {
                vTaskResume(buzzerTaskHandle);
                buzzerSuspenso = false;
            }
        }

        vTaskDelay(pdMS_TO_TICKS(100)); // Polling a cada 100ms
    }
}

int main() {
    stdio_init_all();

    // Inicializa GPIOs
    gpio_init(PIN_LED_R);
    gpio_init(PIN_LED_G);
    gpio_init(PIN_LED_B);
    gpio_init(PIN_BUZZER);
    gpio_init(PIN_BTN_A);
    gpio_init(PIN_BTN_B);

    gpio_set_dir(PIN_LED_R, GPIO_OUT);
    gpio_set_dir(PIN_LED_G, GPIO_OUT);
    gpio_set_dir(PIN_LED_B, GPIO_OUT);
    gpio_set_dir(PIN_BUZZER, GPIO_OUT);
    gpio_set_dir(PIN_BTN_A, GPIO_IN);
    gpio_set_dir(PIN_BTN_B, GPIO_IN);

    gpio_pull_up(PIN_BTN_A);
    gpio_pull_up(PIN_BTN_B);

    // Cria tarefas
    xTaskCreate(led_task, "LED Task", 256, NULL, 1, &ledTaskHandle);
    xTaskCreate(buzzer_task, "Buzzer Task", 256, NULL, 1, &buzzerTaskHandle);
    xTaskCreate(button_task, "Button Task", 256, NULL, 2, NULL);

    // Inicia o scheduler
    vTaskStartScheduler();

    while (true) {}
}
