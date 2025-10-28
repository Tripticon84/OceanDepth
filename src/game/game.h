#ifndef OCEANDEPTH_GAME_H
#define OCEANDEPTH_GAME_H

typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_SAVE_MENU_CREATE,
    GAME_STATE_SAVE_MENU_LOAD,
    GAME_STATE_PLAYING,
    GAME_STATE_COMBAT
} GameState;

extern GameState currentGameState;
extern int running;

int init_game(void);

void menu_loop(void);

#endif //OCEANDEPTH_GAME_H
