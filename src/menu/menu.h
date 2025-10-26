#ifndef OCEANDEPTH_DISPLAY_MENU_H
#define OCEANDEPTH_DISPLAY_MENU_H

#include <stdio.h>


/**
 * @brief Affiche le menu principal et gère la sélection de l'utilisateur.
 * @return int Code de l'action choisie (1 à 8) ou -1 en cas d'erreur.
 */
void display_main_menu(void);

/**
 * @brief Affiche l'écran "Nouvelle Plongée" (initialise un nouveau jeu).
 * @return int 0 si succès, -1 si échec.
 */
int start_new_game(void);

/**
 * @brief Affiche les compétences marines débloquées.
 */
void display_skills(void);

/**
 * @brief Ouvre l'inventaire sous-marin avec gestion des objets.
 */
void display_inventory(void);

/**
 * @brief Menu des options (langue, effets, sauvegarde auto, etc.).
 */
void display_options(void);

#endif //OCEANDEPTH_DISPLAY_MENU_H
