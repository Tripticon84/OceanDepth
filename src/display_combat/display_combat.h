#ifndef OCEANDEPTH_DISPLAY_H
#define OCEANDEPTH_DISPLAY_H

#include "../map/map.h"
#include "../monster/monster.h"
#include "../player/player.h"

#define BORDER_CHAR "║"
#define INNER_WIDTH 78

/**
 * Affiche l'interface du combat, y compris les informations sur les attaques restantes.
 * @param remainingAttacks Pointeur vers le nombre d'attaques restantes.
 */
void display_combat_interface(const int* remainingAttacks);

/**
 * Affiche le menu de sélection de la cible lors d'un combat.
 */
void display_target_selection_menu();

/**
 * Affiche les informations des monstres présents dans le combat.
 */
void display_monsters_infos();
#endif //OCEANDEPTH_DISPLAY_H
