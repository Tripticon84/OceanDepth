#ifndef OCEANDEPTH_DISPLAY_H
#define OCEANDEPTH_DISPLAY_H

#include "../map/map.h"
#include "../monster/monster.h"
#include "../player/player.h"

#define BORDER_CHAR "║"
#define INNER_WIDTH 78

// Affichage de l'interface du combat
void display_combat_interface(const int* remainingAttacks);

void display_target_selection_menu();

void display_monsters_infos();


// Affichage de la partie principale du combat (joueur + monstres)
// void display_combat_main(Diver* player, Monster monsters[], int nbMonsters);

// Affichage du menu principal d’actions en combat
// void display_combat_actions_menu(Diver* diver, int remainingAttacks);

// Affichage d’une barre de progression (ex: rechargement, attente)
// void display_progress_bar(int current, int max, int width);
//
// void display_header(int depth, int pearls);
//
// // Affiche une ligne vide avec bordures
// void display_empty_line(void);
//
// // Affiche une ligne séparatrice
// void display_separator(void);
//
// // Affiche le pied de page (Message et actions possibles)
// void display_footer(void);
//
// // Affiche le Message du menu d’actions
// void display_action_menu_title(void);
//
// // Affiche l’invite de saisie
// void display_input(void);

#endif //OCEANDEPTH_DISPLAY_H
