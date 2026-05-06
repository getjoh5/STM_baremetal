/**
 * @file gpio.c
 * @brief Implementation du driver GPIO pour STM32L4.
 *
 * Ce fichier contient les fonctions permettant de configurer et de
 * piloter les broches GPIO en acces direct aux registres, sans utiliser
 * la HAL STM32.
 *
 * @author GWETH Christian
 * @date 2026-04-30
 */

#include "gpio.h"
#include "stddef.h"
#include "stm32l4xx.h"

#define ENABLE_REG_BIT(A,B) (A|(0x1UL<<B))
#define DESABLE_REG_BIT(A,B)(A&(~(0x1UL<<B)))



/* Fonctions publiques ------------------------------------------------------ */

/**
 * @brief Initialise les ports GPIO utilises par les LED.
 *
 * Active les horloges des ports GPIOA, GPIOB, GPIOC et GPIOE, puis configure
 * les broches PA5, PB14 et PE3 en sortie push-pull avec une vitesse faible.
 *
 * @return 0 si l'initialisation reussit, -1 si un pointeur de registre est nul.
 */
int GPIO_int(){
    int res = 0;
    if(RCC == NULL || GPIOA == NULL || GPIOB == NULL || GPIOE == NULL ){
        return -1;
    }

    //initialisation of clock
    RCC->AHB2ENR = ENABLE_REG_BIT(RCC->AHB2ENR,RCC_AHB2SMENR_GPIOASMEN_Pos);
    RCC->AHB2ENR = ENABLE_REG_BIT(RCC->AHB2ENR,RCC_AHB2SMENR_GPIOBSMEN_Pos);
    RCC->AHB2ENR = ENABLE_REG_BIT(RCC->AHB2ENR,RCC_AHB2SMENR_GPIOCSMEN_Pos);
    RCC->AHB2ENR = ENABLE_REG_BIT(RCC->AHB2ENR,RCC_AHB2SMENR_GPIOESMEN_Pos);

    //initialisation of GPIO
    //Mode

    //output mode for led
    GPIOA->MODER &= ~GPIO_MODER_MODE5_1;        //green for everything right
    GPIOA->MODER |= GPIO_MODER_MODE5_0;        //green for everything right

    GPIOB->MODER &= ~GPIO_MODER_MODE14_1;       //dummy led at this moment
    GPIOB->MODER |= GPIO_MODER_MODE14_0;

    GPIOE->MODER &= ~GPIO_MODER_MODE3_1;
    GPIOE->MODER |= GPIO_MODER_MODE3_0;        //red led when instalation not finish

    //output type configuratino
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT5;
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT14;
    GPIOE->OTYPER &= ~GPIO_OTYPER_OT3;

    //speed configuration
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_0;
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14_0;
    GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_0;

    return res;
}

/**
 * @brief Allume la LED LD1.
 *
 * Met la broche PA5 a l'etat haut via le registre BSRR.
 */
void GPIO_LD1_ON(){
    if(GPIOA == NULL)return;
    //GPIOA->BSRR    |= GPIO_BSRR_BS5;
    //GPIOA->BSRR    &= ~GPIO_BSRR_BR5;
    GPIOA->ODR       |= GPIO_ODR_OD5;
}

/**
 * @brief Eteint la LED LD1.
 *
 * Met la broche PA5 a l'etat bas via le registre BSRR.
 */
void GPIO_LD1_OFF(){
    if(GPIOA == NULL)return;
    GPIOA->BSRR    &= ~GPIO_BSRR_BS5;
    GPIOA->BSRR    |= GPIO_BSRR_BR5;
}

/**
 * @brief Allume la LED LD2.
 *
 * Met la broche PB14 a l'etat haut via le registre BSRR.
 */
void GPIO_LD2_ON(){
    if(GPIOB == NULL)return;
    GPIOB->BSRR    |= GPIO_BSRR_BS14;
    GPIOB->BSRR    &= ~GPIO_BSRR_BR14;
}

/**
 * @brief Eteint la LED LD2.
 *
 * Met la broche PB14 a l'etat bas via le registre BSRR.
 */
void GPIO_LD2_OFF(){
    if(GPIOB == NULL)return;
    GPIOB->BSRR    &= ~GPIO_BSRR_BS14;
    GPIOB->BSRR    |= GPIO_BSRR_BR14;
}

/**
 * @brief Allume la LED LD8.
 *
 * Met la broche PE3 a l'etat haut via le registre BSRR.
 */
void GPIO_LD8_ON(){
    if(GPIOE == NULL)return;
    GPIOE->BSRR    |= GPIO_BSRR_BS3;
    GPIOE->BSRR    &= ~GPIO_BSRR_BR3;
}

/**
 * @brief Eteint la LED LD8.
 *
 * Met la broche PE3 a l'etat bas via le registre BSRR.
 */
void GPIO_LD8_OFF(){
    if(GPIOE == NULL)return;
    GPIOE->BSRR    &= ~GPIO_BSRR_BS3;
    GPIOE->BSRR    |= GPIO_BSRR_BR3;
}
