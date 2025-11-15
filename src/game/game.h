#ifndef OCEANDEPTH_GAME_H
#define OCEANDEPTH_GAME_H

#include "../monster/monster.h"
#include "../player/player.h"
#include "../map/map.h"

typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_SAVE_MENU_CREATE,
    GAME_STATE_SAVE_MENU_LOAD,
    GAME_STATE_PLAYING,
    GAME_STATE_MAP,
    GAME_STATE_SHOP,
    GAME_STATE_INVENTORY,
    GAME_STATE_REWARD,
    GAME_STATE_GAME_OVER,
    GAME_STATE_COMBAT
} GameState;

extern GameState currentGameState;
extern int running;

extern Monster* monsters[4];
extern int* monstersCount;
extern Diver* player;
extern int depth;
extern Map gameMap;

void init_game(void);

void menu_loop(void);

void game_loop(void);

void combat_loop(void);

#endif //OCEANDEPTH_GAME_H
