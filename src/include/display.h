#ifndef OCEANDEPTH_DISPLAY_H
#define OCEANDEPTH_DISPLAY_H

#include <stdio.h>

#include "inventory.h"
#include "map.h"
#include "monsters.h"
#include "player.h"

// Affichage principal de l'interface de combat
void display_game_interface(Diver* player, Monster creatures[], int creatureCount, int depth);

// Affichage des barres de ressources (vie, oxygène, fatigue)
void display_resource_bars(Diver* player);

// Affichage des créatures présentes dans la zone
void display_creatures_in_combat(Monster creatures[], int count);

// Affichage de l'inventaire sous-marin
void display_inventory(Inventory* inv, int pearls);

// Affichage de la carte océanique
void display_ocean_map(Zone map[][5], int currentDepth, const char* currentZoneName);

// Affichage d'une récompense découverte
void display_treasure_found(Item item);

// Affichage du menu des compétences marines
void display_marine_skills_menu(void);

// Affichage d'un message d'alerte critique (oxygène faible)
void display_critical_oxygen_alert(int oxygenLevel);

// Affichage d'un combat (animation textuelle simplifiée)
void display_combat_sequence(const char* attackerName, const char* targetName, int damage, const char* weaponName);

// Affichage du menu principal d’actions en combat
void display_combat_actions_menu(int remainingAttacks);

// Affichage du menu d’exploration / navigation
void display_exploration_menu(void);

// Affichage d’un message centré dans une boîte (style interface)
void display_message_box(const char* title, const char* message);

// Affichage d’une barre de progression (ex: rechargement, attente)
void display_progress_bar(int current, int max, int width);


#endif //OCEANDEPTH_DISPLAY_H
