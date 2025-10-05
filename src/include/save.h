#ifndef OCEANDEPTH_SAVE_H
#define OCEANDEPTH_SAVE_H

#include "monsters.h"
#include "player.h"
#include "inventory.h"

int SaveGame(const char *filePath, Diver *player, Inventory *inv, int depth, const char *zone,
             Monster monsters[], int monstersCount);

int LoadGame(const char *filePath, Diver *player, Inventory *inv,
             int *depth, char *zone, Monster monsters[], int *monstersCount);

#endif //OCEANDEPTH_SAVE_H
