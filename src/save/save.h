#ifndef OCEANDEPTH_SAVE_H
#define OCEANDEPTH_SAVE_H

#include "../monster/monsters.h"
#include "../player/player.h"
#include "../inventory/inventory.h"

int SaveGame(const char *filePath, Diver *player, Inventory *inv, int depth, const char *zone,
             Monster monsters[], int monstersCount);

int LoadGame(const char *filePath, Diver *player, Inventory *inv,
             int *depth, char *zone, Monster monsters[], int *monstersCount);

#endif //OCEANDEPTH_SAVE_H
