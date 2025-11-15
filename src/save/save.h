#ifndef OCEANDEPTH_SAVE_H
#define OCEANDEPTH_SAVE_H

#include "../map/map.h"
#include "../monster/monster.h"
#include "../player/player.h"

// Structure d'une save
typedef struct {
    Diver player;
    int depth;
    Zone zone;
    int monstersCount;
    Monster monsters[100];
} SaveData;

extern SaveData saveData;


int save_game(int slot);

int load_game(int slot);

void display_saves_menu(void);

void get_saves_infos(int slot);

void handle_load_save_menu_input(void);

void handle_create_save_menu_input(void);

#endif //OCEANDEPTH_SAVE_H
