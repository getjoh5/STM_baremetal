/**
 * @file spi.c
 * @brief Debut du driver SPI1 bas niveau.
 *
 * Ce fichier contient l'initialisation minimale du peripherique SPI1 en acces
 * direct aux registres. La configuration des broches associees est faite dans
 * le driver GPIO.
 */

#include "spi.h"
#include "gpio.h"
#include "stm32l4xx.h"
#include "stddef.h"

void spi_init(void){
    if(SPI1 == NULL || RCC == NULL)return;

    /* Active l'horloge du peripherique SPI1 sur le bus APB2. */
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

}
