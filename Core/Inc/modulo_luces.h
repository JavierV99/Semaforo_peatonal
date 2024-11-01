// modulo_luces.h

#ifndef MODULO_LUCES_H
#define MODULO_LUCES_H

#include "stm32f1xx_hal.h"

// Definición de estados para la FSM
typedef enum {
    ESTADO_INICIAL,
    ESTADO_ALTERNAR_VERDE,
    ESTADO_ESPERA_ROJO,
    ESTADO_ALTERNAR_ROJO,
} EstadoLuces_t;

// Funciones de inicialización y actualización
void luces_init(void);
void luces_update(void);

#endif // MODULO_LUCES_H
