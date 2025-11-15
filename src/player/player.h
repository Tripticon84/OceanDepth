#ifndef OCEANDEPTH_PLAYER_H
#define OCEANDEPTH_PLAYER_H

#include "../inventory/inventory.h"

typedef struct {
    int health;
    int maxHealth;
    int oxygen;
    int maxOxygen;
    short tiredness;
    short maxTiredness; // 1 (peu fatigué) à 5 (très fatigué)
    int pearls;
    Inventory inventory;
    int zoneIndex;
    int caseIndex;
} Diver;

/**
 * Initialise un joueur (Diver) avec les valeurs par défaut.
 * @param player Pointeur vers la structure Diver à initialiser.
 */
void init_player(Diver* player);

/**
 * Libère les ressources associées au joueur (Diver).
 * @param player Pointeur vers la structure Diver à nettoyer.
 */
void clean_player(Diver* player);

/**
 * Affiche les informations du joueur (Diver) sur la sortie standard.
 * @param player Pointeur vers la structure Diver à afficher.
 */
void print_player(Diver* player);

#endif //OCEANDEPTH_PLAYER_H
