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

/* Definition des registres SysTick du coeur Cortex-M. */
#define SYSTICK_BASE        0xE000E010
typedef union
{
   uint32_t value;
   struct BIT_STK_CTRL{
        uint32_t ENABLE      :1;
        uint32_t TICKINT     :1;
        uint32_t CLKSOURCE   :1;
        uint32_t RESERVE1    :12;
        uint32_t COUNTFLAG   :1;
        uint32_t RESERVE2    :14;
   } Bit_Value;
}STK_CTRL_TypeDef;

typedef struct
{
   STK_CTRL_TypeDef STCK_CTRL;
   uint32_t         STCK_LOAD;
   uint32_t         STCK_VAL;
   uint32_t         STCK_CALIB;
}SYSTICK_TypeDef;

#define SYSTICK          ((SYSTICK_TypeDef *) SYSTICK_BASE)

/* Compteur milliseconde incremente par l'interruption SysTick. */
extern volatile uint32_t  GlobalSystick;
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

/**
 * @brief Attend un nombre de millisecondes en utilisant GlobalSystick.
 */
void timer_delay_ms(uint32_t delay_ms);

#endif /* DRIVERS_TIMER_H */
