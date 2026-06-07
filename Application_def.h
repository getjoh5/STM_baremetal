/**
 * @file Application_def.h
 * @brief Define Macro that will be use in application.c.
 *
 * Ce fichier définit l'ensemble des messages et macro utilies dans la partie application
 *
 * @author GWETH Christian
 * @date 2026-06-02
 */
#ifndef APP_DEF_H
#define APP_DEF_H


//Message to Display
//Error
#define SIZE_ERROR_MESSAGE  100
#define ERROR_000   "Error_000: Problème survenue Lors de l'installation des périphérique"
#define ERROR_001   "Error_001: Un problème est survenue Merci de re-éssayer"
#define ERROR_002   "Error_002: Un problème est survenue L'or de l'initialisation du temp"


//Message
#define SIZE_MESSAGE        100
#define BIENVENUE   "Bienvenue dans \n le Projet GWETH"
#define CHARGEMENT  "Chargement des ressources nécessaires ...."
#define PATIENCE    "Veuillez patienter un instant"

//step initialisation
#define STEP_INIT_DISPLAY_FIRST_IMAGE       0
#define STEP_INIT_DISPLAY_CHGMNT_MESSAGE    1
#define STEP_INIT_DISPLAY_DELAY             2

//Step Runing
//CG TODO


#endif