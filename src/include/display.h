#ifndef OCEANDEPTH_DISPLAY_H
#define OCEANDEPTH_DISPLAY_H

#include "map.h"
#include "monsters.h"
#include "player.h"

#define BORDER_CHAR "║"
#define INNER_WIDTH ( - 2)


// Affichage principal de l'interface de combat
void display_combat_interface(Diver* player, Monster creatures[], int creatureCount, int depth);

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
void display_combat_actions_menu(Diver* diver, int remainingAttacks);

// Affichage du menu d’exploration / navigation
void display_exploration_menu(void);

// Affichage d’un message centré dans une boîte (style interface)
void display_message_box(const char* title, const char* message);

// Affichage d’une barre de progression (ex: rechargement, attente)
void display_progress_bar(int current, int max, int width);

void display_header(int depth, int pearls);

void display_empty_line(void);
void display_titles(void);
void display_diver_box(Diver* player);
void display_diver_stats(Diver* player);
void display_diver_life(Diver* player);
void display_diver_oxygen(Diver* player);
void display_diver_oxygen_bar(Diver* player);
void display_diver_fatigue(Diver* player);
void display_diver_fatigue_bar(Diver* player);
void display_diver_box_bottom(void);
void display_separator(void);
void display_footer(void);
void display_action_menu_title(void);
void display_input(void);

// Fonctions utilitaires pour l'affichage dynamique
int calculate_text_width(const char* text);
int calculate_number_width(int number);
void print_centered_text(const char* text, int total_width);
void print_padded_text(const char* text, int width, char align);

#endif //OCEANDEPTH_DISPLAY_H
