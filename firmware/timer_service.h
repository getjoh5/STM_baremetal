/**
 * @file timer_service.h
 * @brief Service applicatif de temporisation base sur un compteur materiel.
 *
 * Le service memorise une valeur de capture et verifie ensuite si une duree
 * donnee s'est ecoulee. Il ne configure pas le timer materiel lui-meme :
 * il lit seulement une source de ticks fournie par le driver bas niveau.
 */

#ifndef TIMER_SERVICE_H
#define TIMER_SERVICE_H

#include <stdint.h>

/**
 * @brief Objet timer applicatif.
 *
 * sourceTimer pointe vers un registre compteur materiel volatile, par exemple
 * TIM2->CNT. CaptureValue memorise la valeur du compteur au dernier reset.
 * ResetValue contient la duree attendue, exprimee dans la meme unite que
 * la source de ticks.
 */
typedef struct{
    volatile uint32_t *sourceTimer;
    uint32_t CaptureValue;
    uint32_t ResetValue;
}timer_t;

extern timer_t oTimer;

/**
 * @brief Associe un timer applicatif a une source de ticks.
 *
 * @param timer Timer applicatif a initialiser.
 * @param src Adresse du compteur materiel utilise comme source de ticks.
 * @return 0 si l'initialisation reussit, -1 si un pointeur est nul.
 */
int timer_init_serv(timer_t* timer, volatile uint32_t* src);

/**
 * @brief Redemarre une temporisation depuis la valeur courante du compteur.
 *
 * @param timer Timer applicatif a redemarrer.
 * @param value Duree a attendre, exprimee en ticks de sourceTimer.
 */
void timer_reset_serv(timer_t* timer, uint32_t value);

/**
 * @brief Indique si la temporisation est expiree.
 *
 * La soustraction unsigned permet de rester robuste lorsque le compteur
 * 32 bits deborde et revient a zero.
 *
 * @param timer Timer applicatif a tester.
 * @return 1 si la duree est ecoulee, 0 sinon.
 */
uint32_t timer_expired_serv(timer_t* timer);

#endif /* TIMER_SERVICE_H */
