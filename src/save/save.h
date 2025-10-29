#ifndef OCEANDEPTH_SAVE_H
#define OCEANDEPTH_SAVE_H

#include "../monster/monster.h"
#include "../player/player.h"
#include "../inventory/inventory.h"
#include <stdio.h>

int save_game(int slot, Diver* player, Inventory* inv, int depth, const char* zone, Monster monsters[], int monstersCount);

int load_game(int slot, Diver* player, Inventory* inv, int* depth, char* zone, Monster monsters[], int* monstersCount);

void display_saves_menu(void);

void get_saves_infos(int slot);

void handle_load_save_menu_input(void);

void handle_create_save_menu_input(void);

#endif //OCEANDEPTH_SAVE_H
