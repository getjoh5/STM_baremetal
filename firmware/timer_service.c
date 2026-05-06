/**
 * @file timer_service.c
 * @brief Implementation du service applicatif de temporisation.
 *
 * Ce module fournit une temporisation non bloquante : l'application peut
 * tester regulierement l'expiration d'un delai sans arreter le processeur
 * dans une boucle d'attente.
 */

#include "timer_service.h"
#include "stddef.h"

/* Variables publiques ------------------------------------------------------ */

timer_t oTimer;

/* Fonctions publiques ------------------------------------------------------ */

int timer_init_serv(timer_t* timer, volatile uint32_t* src){
    if(src == NULL || timer == NULL)return -1;

    timer->sourceTimer = src;
    timer->CaptureValue = 0;
    timer->ResetValue = 0;

    return 0;
}

void timer_reset_serv(timer_t* timer, uint32_t value){
    if(timer == NULL || timer->sourceTimer == NULL)return;

    timer->CaptureValue = *timer->sourceTimer;
    timer->ResetValue   = value;
}

uint32_t timer_expired_serv(timer_t* timer){
    if(timer == NULL || timer->sourceTimer == NULL)return 0;

    /* Soustraction unsigned : correcte meme si le compteur 32 bits wrap. */
    return ((*timer->sourceTimer - timer->CaptureValue) >= timer->ResetValue) ? 1U : 0U;
}
