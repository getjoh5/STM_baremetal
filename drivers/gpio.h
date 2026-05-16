/**
 * @file gpio.h
 * @brief Interface du driver GPIO pour STM32L4.
 *
 * Ce fichier regroupe les types, constantes et prototypes publics
 * permettant de configurer et piloter les broches GPIO sans utiliser
 * la HAL STM32.
 *
 * @author GWETH Christian
 * @date 2026-04-29
 */

#ifndef DRIVERS_GPIO_H
#define DRIVERS_GPIO_H

#include <stdint.h>




/* Types publics ------------------------------------------------------------ */

/* Constantes publiques ----------------------------------------------------- */

/* Prototypes publics ------------------------------------------------------- */

/**
 * @brief Initialise les ports GPIO utilises par les LED.
 *
 * @return 0 si l'initialisation reussit, -1 si un pointeur de registre est nul.
 */
int GPIO_int(void);

/**
 * @brief Allume la LED LD1.
 */
void GPIO_LD1_ON(void);

/**
 * @brief Eteint la LED LD1.
 */
void GPIO_LD1_OFF(void);

/**
 * @brief Met la ligne Reset PA4 a l'etat haut.
 */
void GPIO_PA4_ON(void);

/**
 * @brief Met la ligne Reset PA4 a l'etat bas.
 */
void GPIO_PA4_OFF(void);

/**
 * @brief Met la ligne Data/Command PA3 a l'etat haut.
 */
void GPIO_PA3_ON(void);

/**
 * @brief Met la ligne Data/Command PA3 a l'etat bas.
 */
void GPIO_PA3_OFF(void);

/**
 * @brief Allume la LED LD2.
 */
void GPIO_LD2_ON(void);

/**
 * @brief Eteint la LED LD2.
 */
void GPIO_LD2_OFF(void);

/**
 * @brief Allume la LED LD8.
 */
void GPIO_LD8_ON(void);

/**
 * @brief Eteint la LED LD8.
 */
void GPIO_LD8_OFF(void);

#endif /* DRIVERS_GPIO_H */
