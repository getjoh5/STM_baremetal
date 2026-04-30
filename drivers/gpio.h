/**
 * @file gpio.h
 * @brief Interface du driver GPIO pour STM32L4.
 *
 * Ce fichier regroupe les types, constantes et prototypes publics
 * permettant de configurer et piloter les broches GPIO sans utiliser
 * la HAL STM32.
 *
 * @author GWETH Christian
 * @date 2026-04-29
 */

#ifndef DRIVERS_GPIO_H
#define DRIVERS_GPIO_H

#include <stdint.h>
#include "stm32l4xx.h"

/* Types publics ------------------------------------------------------------ */
typedef struct {
    GPIO_TypeDef *port;
    uint8_t pin;
    uint8_t mode;
    uint8_t pull;
    uint8_t output_type;
    uint8_t speed;
} GPIO_Config;


/* Constantes publiques ----------------------------------------------------- */

/* Prototypes publics ------------------------------------------------------- */
void GPIO_int();
#endif /* DRIVERS_GPIO_H */
