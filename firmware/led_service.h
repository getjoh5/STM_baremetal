/**
 * @file led_service.h
 * @brief Interface du service applicatif de pilotage des LED.
 *
 * Ce fichier regroupe les prototypes publics du service LED. Le service LED
 * s'appuie sur le driver GPIO pour piloter les LED de la carte sans exposer
 * directement les registres materiels au reste de l'application.
 *
 * @author GWETH Christian
 * @date 2026-05-01
 */

#ifndef FIRMWARE_LED_SERVICE_H
#define FIRMWARE_LED_SERVICE_H

#define LED_START_FINISH_GOOD   1
#define LED_START_FINISH_BAD    2
#define LED_USER                3

void    LED_TurnOn(int oLed);
void    LED_TurnOff(int oLed);

#endif /* FIRMWARE_LED_SERVICE_H */
