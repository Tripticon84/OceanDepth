#ifndef OCEANDEPTH_MAP_H
#define OCEANDEPTH_MAP_H

#include "../inventory/inventory.h"
#include "../player/player.h"

enum ZONE_TYPE {
    SURFACE = 0,
    REEF    = 1,
    WRECK   = 2,
};

typedef struct {
    char name[30];
    int depth;
    char icon;
    char description[50];
    int monstersCount;
    int isDiscovered;
    char zoneType[20]; // "surface", "reef", "wreck", etc.
} Zone;

void initialize_zones(Zone map[][5]);

void display_map(Zone map[][5], int currentDepth, const char* currentZoneName);

int move_to_zone(Diver* player, Zone* destination);

int can_access_zone(Zone* zone, Item* wetsuit);

#endif //OCEANDEPTH_MAP_H
