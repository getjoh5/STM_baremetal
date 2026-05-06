/**
 * @file Timer.h
 * @brief Interface du driver bas niveau TIM2.
 *
 * Ce driver configure TIM2 comme compteur libre 32 bits. Avec une horloge
 * timer a 4 MHz et un prescaler a 3999, le compteur avance a 1 kHz :
 * un tick TIM2 correspond donc a 1 ms.
 */

#ifndef DRIVERS_TIMER_H
#define DRIVERS_TIMER_H

#include <stdint.h>

/**
 * @brief Initialise TIM2 comme base de temps en millisecondes.
 *
 * @return 0 si l'initialisation reussit, -1 si les registres RCC ou TIM2
 *         ne sont pas accessibles.
 */
int timer_init(void);

/**
 * @brief Lit la valeur courante du compteur TIM2.
 *
 * @return Valeur actuelle de TIM2->CNT.
 */
uint32_t timer_get_counter(void);

#endif /* DRIVERS_TIMER_H */
