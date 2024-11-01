// modulo_luces.c

#include "modulo_luces.h"

// Variables globales
static EstadoLuces_t estado_actual = ESTADO_INICIAL;
static uint32_t startTime = 0;
static int cont = 0;

void luces_init(void) {
    // Configuración inicial de las luces
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);  // Luz verde encendida
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);    // Luz roja apagada
    estado_actual = ESTADO_INICIAL;
}

void luces_update(void) {
    uint32_t currentTime = HAL_GetTick();

    switch (estado_actual) {
        case ESTADO_INICIAL:
        	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);  // Luz verde encendida
        	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_SET) {  // Botón presionado
                estado_actual = ESTADO_ALTERNAR_VERDE;
                cont = 0;
                startTime = currentTime;
            }
            break;

        case ESTADO_ALTERNAR_VERDE:
            if (currentTime - startTime >= 200) {
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);  // Alterna la luz verde
                cont++;
                startTime = currentTime;
            }
            if (cont >= 5) {
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);  // Apaga la luz verde
                estado_actual = ESTADO_ESPERA_ROJO;
                cont = 0;
                startTime = currentTime;
            }
            break;

        case ESTADO_ESPERA_ROJO:
            if (currentTime - startTime >= 200) {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  // Enciende la luz roja
                cont++;
                startTime = currentTime;
            }
            if (cont >= 15) {  // 3 segundos = 15 ciclos de 200 ms
                estado_actual = ESTADO_ALTERNAR_ROJO;
                cont = 0;
                startTime = currentTime;
            }
            break;

        case ESTADO_ALTERNAR_ROJO:
            if (currentTime - startTime >= 200) {
                HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);  // Alterna la luz roja
                cont++;
                startTime = currentTime;
            }
            if (cont >= 5) {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  // Apaga la luz roja
                estado_actual = ESTADO_INICIAL;
            }
            break;

        default:
            estado_actual = ESTADO_INICIAL;
            break;
    }
}
