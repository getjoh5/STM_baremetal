/**
 * @file Timer.c
 * @brief Driver bas niveau pour TIM2 sur STM32L475.
 *
 * TIM2 est utilise comme compteur libre 32 bits. Le projet suppose une
 * horloge timer de 4 MHz. Le prescaler 3999 divise cette horloge par 4000,
 * ce qui produit une base de temps de 1 kHz, soit 1 tick par milliseconde.
 */

#include "Timer.h"
#include "stddef.h"
#include "stm32l4xx.h"
#include "stm32l475xx.h"

/* Configuration timer ------------------------------------------------------ */

#define TIM2_PRESCALER_1MS     3999U
#define TIM2_MAX_RELOAD        0xFFFFFFFFU

/* Base de temps partagee avec le service timer. */
volatile uint32_t  GlobalSystick;

/* Fonctions publiques ------------------------------------------------------ */

int timer_init(void){
    if(RCC == NULL || TIM2 == NULL)return -1;

    /* Active l'horloge du peripherique TIM2 sur le bus APB1. */
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

    /* Configure TIM2 comme compteur libre, sans interruption. */
    TIM2->CR1 = 0;
    TIM2->PSC = TIM2_PRESCALER_1MS;
    TIM2->ARR = TIM2_MAX_RELOAD;
    TIM2->CNT = 0;

    /* Force le chargement immediat du prescaler dans le timer. */
    TIM2->EGR = TIM_EGR_UG;
    TIM2->CR1 = TIM_CR1_CEN;

    /* Configure SysTick pour generer une interruption periodique. */
    SYSTICK->STCK_LOAD                      = TIM2_PRESCALER_1MS;
    SYSTICK->STCK_CTRL.Bit_Value.CLKSOURCE  = 1U;
    SYSTICK->STCK_CTRL.Bit_Value.TICKINT    = 1U;
    SYSTICK->STCK_CTRL.Bit_Value.ENABLE     = 1U;

    return 0;
}

uint32_t timer_get_counter(void){
    return (uint32_t)TIM2->CNT;
}

void timer_delay_ms(uint32_t delay_ms){
    uint32_t start = GlobalSystick;

    while((uint32_t)(GlobalSystick - start) < delay_ms){
    }
}

void SysTick_Handler(){
    /* Incremente la base de temps a chaque interruption SysTick. */
    GlobalSystick++;
}
