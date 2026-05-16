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
 * les broches utilisees par les LED et par le bus SPI1.
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
    //GPIOA->MODER &= ~GPIO_MODER_MODE5_1;        //green for everything right
    //GPIOA->MODER |= GPIO_MODER_MODE5_0;        //green for everything right

    /* Configure PA5 en fonction alternative SPI1_SCK. */
    GPIOA->AFR[0] &= ~(0xFUL<<(20U));
    GPIOA->AFR[0] |= (0x5UL<<(20U));

    GPIOA->MODER &= ~(0x3UL<<(10U)); //reset register
    GPIOA->MODER |=  (0x2UL<<(10U)); //set register

    /* Configure PA7 en fonction alternative SPI1_MOSI. */
    GPIOA->AFR[0] &= ~(0xFUL<<(28U));
    GPIOA->AFR[0] |= (0x5UL<<(28U));

    GPIOA->MODER &= ~(0x3UL<<(14U)); //reset register
    GPIOA->MODER |=  (0x2UL<<(14U)); //set register

    /* Configure PA3 comme sortie GPIO pour la ligne Data/Command. */
    GPIOA->MODER &= ~GPIO_MODER_MODE3_1; //reset register
    GPIOA->MODER |= GPIO_MODER_MODE3_0;  //set register

    /* Configure PA4 comme sortie GPIO pour la ligne Reset. */
    GPIOA->MODER &= ~GPIO_MODER_MODE4_1; //rest
    GPIOA->MODER |= GPIO_MODER_MODE4_0;  //set


    GPIOB->MODER &= ~GPIO_MODER_MODE14_1;       //dummy led at this moment
    GPIOB->MODER |= GPIO_MODER_MODE14_0;

    GPIOE->MODER &= ~GPIO_MODER_MODE3_1;
    GPIOE->MODER |= GPIO_MODER_MODE3_0;        //red led when instalation not finish

    //output type configuratino
    /* Les lignes SPI et de controle sont en sortie push-pull. */
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT5; //SCK
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT7; //MOSI
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT3; //DC
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT4; //RST

    GPIOB->OTYPER &= ~GPIO_OTYPER_OT14;
    GPIOE->OTYPER &= ~GPIO_OTYPER_OT3;

    //speed configuration
    /* Applique une vitesse faible aux lignes utilisees par SPI1 et le controle. */
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_0;
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_0;
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_0;
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_0;

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
 * @brief Met la ligne Reset PA4 a l'etat bas.
 */
void GPIO_PA4_OFF(){
    if(GPIOA == NULL)return;
    GPIOA->BSRR    &= ~GPIO_BSRR_BS4;
    GPIOA->BSRR    |= GPIO_BSRR_BR4;
}

/**
 * @brief Met la ligne Data/Command PA3 a l'etat bas.
 */
void GPIO_PA3_OFF(){
    if(GPIOA == NULL)return;
    GPIOA->BSRR    &= ~GPIO_BSRR_BS3;
    GPIOA->BSRR    |= GPIO_BSRR_BR3;
}

/**
 * @brief Met la ligne Reset PA4 a l'etat haut.
 */
void GPIO_PA4_ON(){
    if(GPIOA == NULL)return;
    //GPIOA->BSRR    |= GPIO_BSRR_BS5;
    //GPIOA->BSRR    &= ~GPIO_BSRR_BR5;
    GPIOA->ODR       |= GPIO_ODR_OD4;
}

/**
 * @brief Met la ligne Data/Command PA3 a l'etat haut.
 */
void GPIO_PA3_ON(){
    if(GPIOA == NULL)return;
    //GPIOA->BSRR    |= GPIO_BSRR_BS5;
    //GPIOA->BSRR    &= ~GPIO_BSRR_BR5;
    GPIOA->ODR       |= GPIO_ODR_OD3;
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
