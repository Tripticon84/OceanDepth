#ifndef OCEANDEPTH_GAME_H
#define OCEANDEPTH_GAME_H

#include "../monster/monster.h"
#include "../player/player.h"
#include "../map/map.h"
#include "../inventory/inventory.h"

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
extern Inventory* inventory;
extern int depth;
extern Map gameMap;

/**
 * Initialise le jeu, les variables globales et les ressources nécessaires.
 */
void init_game(void);

/**
 * Boucle principale du menu, gère l'affichage et les interactions utilisateur dans le menu.
 */
void menu_loop(void);

/**
 * Boucle principale du jeu, gère la progression et les événements du jeu.
 */
void game_loop(void);

/**
 * Boucle de combat, gère les interactions et la logique lors des combats.
 */
void combat_loop(void);

void cleanup_game(void);

#endif //OCEANDEPTH_GAME_H
