#ifndef OCEANDEPTH_SAVE_H
#define OCEANDEPTH_SAVE_H

#include "../monster/monsters.h"
#include "../player/player.h"
#include "../inventory/inventory.h"
#include <stdio.h>

int save_game(int slot, Diver* player, Inventory* inv, int depth, const char* zone, Monster monsters[], int monstersCount);

int load_game(int slot, Diver* player, Inventory* inv, int* depth, char* zone, Monster monsters[], int* monstersCount);

void display_saves(void);

void get_saves_infos(int slot);


#endif //OCEANDEPTH_SAVE_H
