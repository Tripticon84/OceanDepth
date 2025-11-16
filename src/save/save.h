#ifndef OCEANDEPTH_SAVE_H
#define OCEANDEPTH_SAVE_H

#include "../map/map.h"
#include "../monster/monster.h"
#include "../player/player.h"

// Structure d'une save
typedef struct {
    Diver player;
    int depth;
    Zone zone;
    int monstersCount;
    Monster monsters[100];
} SaveData;

extern SaveData saveData;


/**
 * Sauvegarde la partie actuelle dans le slot spécifié.
 * @param slot Le numéro du slot de sauvegarde.
 * @return 0 en cas de succès, une valeur négative en cas d'erreur.
 */
int save_game(int slot);

/**
 * Charge la partie depuis le slot spécifié.
 * @param slot Le numéro du slot à charger.
 * @return 0 en cas de succès, une valeur négative en cas d'erreur.
 */
int load_game(int slot);

/**
 * Affiche le menu des sauvegardes disponibles.
 */
void display_saves_menu(void);

/**
 * Récupère et affiche les informations d'une sauvegarde pour un slot donné.
 * @param slot Le numéro du slot à inspecter.
 */
void get_saves_infos(int slot);

/**
 * Gère les entrées utilisateur dans le menu de chargement de sauvegarde.
 */
void handle_load_save_menu_input(void);

/**
 * Gère les entrées utilisateur dans le menu de création de sauvegarde.
 */
void handle_create_save_menu_input(void);
#endif //OCEANDEPTH_SAVE_H
