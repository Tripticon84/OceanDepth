#ifndef OCEANDEPTH_MAP_H
#define OCEANDEPTH_MAP_H

#include <stdbool.h>
#include "../player/player.h"

typedef enum {
    SURFACE,
    REEF,
    WRECK,
    ALGAE_FOREST,
    CAVE,
    SHOP
} ZoneKind;

typedef struct {
    char icon[10];
    char name[50];
    char description[50];
} ZoneType;

typedef struct {
    char icon[10];
    char name[50];
    ZoneKind type;
    char description[50];
    short minMonsterCount;
    short maxMonsterCount;
    bool isDiscovered;
    bool hasBeenDefeated;
} CaseZone;

typedef struct {
    int depth;
    CaseZone cases[4];
} Zone;

typedef struct {
    Zone* zones;
    int numZones;
} Map;

void first_init_zone();

void init_next_zone();

int move_to_zone(Diver* player, Zone* destination);

bool can_access_zone(CaseZone* caseZone);

bool is_case_zone_visible(int zoneIndex, int caseIndex);

void print_map();

const char* get_zone_type_name(ZoneKind type);

void handle_map_input();

#endif //OCEANDEPTH_MAP_H
