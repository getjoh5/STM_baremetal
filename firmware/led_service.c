/**
 * @file led_service.c
 * @brief Implementation du service applicatif de pilotage des LED.
 *
 * Ce fichier contient les fonctions de haut niveau permettant d'allumer et
 * d'eteindre les LED de la carte via le driver GPIO.
 *
 * @author GWETH Christian
 * @date 2026-05-01
 */

#include "led_service.h"
#include "gpio.h"

/* Fonctions publiques ------------------------------------------------------ */

/**
 * @brief Allume une LED selon son identifiant applicatif.
 *
 * @param oLed Identifiant de la LED a allumer.
 */
void LED_TurnOn(int oLed)
{
    int ledType = oLed;

    switch(ledType) {
        case LED_START_FINISH_GOOD:
            //GPIO_LD1_ON();
            break;

        case LED_START_FINISH_BAD:
            GPIO_LD8_ON();
            break;

        case LED_USER:
            GPIO_LD2_ON();
            break;

        default:
            break;
    }
}

/**
 * @brief Eteint une LED selon son identifiant applicatif.
 *
 * @param oLed Identifiant de la LED a eteindre.
 */
void LED_TurnOff(int oLed)
{
    int ledType = oLed;

    switch(ledType) {
        case LED_START_FINISH_GOOD:
            //GPIO_LD1_OFF();
            break;

        case LED_START_FINISH_BAD:
            GPIO_LD8_OFF();
            break;

        case LED_USER:
            GPIO_LD2_OFF();
            break;

        default:
            break;
    }
}

/* Fonctions privees -------------------------------------------------------- */
