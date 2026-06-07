/**
 * @file Application.h
 * @brief Define Application object.
 *
 * Ce fichier represente le coeur de l'appliocation tetrice dedant doit etre implementer
 * toutes les fonction utiles pour une meilleur ergonomie de l'utilisateur elle est amener à grnadir
 *
 * @author GWETH Christian
 * @date 2026-06-02
 */
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Application_def.h"
#include "st7789.h"
#include "fonts.h"
#include "stdint.h"
#include "timer_service.h"

#define BAR_X      0
#define BAR_Y      221
#define BAR_W      240
#define BAR_H      18
#define BAR_BORDER WHITE
#define BAR_FILL   WHITE

typedef struct 
{
    uint8_t StepInit;           //!< step to do in initialisation
    uint8_t StepRun;            //!< step to do while the running is start
    timer_t ApplicationTimer;   //!< timer service for application 
    char    Message[100];
    char    Error[100];
    uint8_t rectPercentage;
    //TODO: CG
    //Prevoir peut-être un objet pour mes rectangle pour le chargement au demarrage
}Application_t;

/**
 * @brief Initialize the application object and startup display sequence.
 *
 * @param app Application object to initialize.
 * @param Tim Tick source used by the timer service.
 * @return 0 on success, -1 on error.
 */
int App_init(Application_t * app, volatile uint32_t * Tim ); 

/**
 * @brief Start the application after initialization.
 */
void App_start(void);

/**
 * @brief Execute the application runtime state machine.
 */
void App_run(void);


#endif /* APPLICATION_H */
