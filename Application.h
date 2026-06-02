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
#include "Application_def.h"
#include "stdint.h"
#include "timer_service.h"

typedef struct 
{
    uint8_t StepInit;           //!< step to do in initialisation
    uint8_t StepRun;            //!< step to do while the running is start
    timer_t ApplicationTimer;   //!< timer service for application 
    char    Message[100];
    char    Error[100];
    //TODO: CG
    //Prevoir peut-être un objet pour mes rectangle pour le chargement au demarrage
}Application_t;



