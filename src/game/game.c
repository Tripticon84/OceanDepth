#include "game.h"
#include <stdlib.h>

#include "../menu/menu.h"
#include "../save/save.h"
#include "../utils/utils.h"

int running = 1;
GameState currentGameState = GAME_STATE_MENU;

int init_game(void) {
    return 0;
}

void menu_loop(void) {
    GameState previewGameState = currentGameState;

    while (running) {
        if (previewGameState != currentGameState) {
            // Menu principal -> Création de Sauvegarde
            if (previewGameState == GAME_STATE_MENU && currentGameState == GAME_STATE_SAVE_MENU_CREATE) {
                clear_terminal();
            }
            // Menu principal -> Liste des Sauvegardes
            if (previewGameState == GAME_STATE_MENU && currentGameState == GAME_STATE_SAVE_MENU_LOAD) {
                clear_terminal();
            }
            // Menu Sauvegardes -> Jeu
            if (previewGameState == GAME_STATE_SAVE_MENU_LOAD && currentGameState == GAME_STATE_PLAYING) {
                // Menu Save -> Jeu
                // Initialisation du jeu
                // ...
                clear_terminal();
            }
            // Jeu -> Menu principal
            if (previewGameState == GAME_STATE_PLAYING && currentGameState == GAME_STATE_MENU) {
                // Sortie du jeu
                // clear_terminal();
                // display_main_menu();
            }
            previewGameState = currentGameState;
        }
        clear_terminal();
        switch (currentGameState) {
            case GAME_STATE_MENU:
                display_main_menu();
                handle_menu_input();
                break;
            case GAME_STATE_SAVE_MENU_CREATE:
                // Créer une nouvelle sauvegarde
                display_saves_menu();
                handle_create_save_menu_input();
                break;
            case GAME_STATE_SAVE_MENU_LOAD:
                // Charger une sauvegarde existante
                display_saves_menu();
                handle_load_save_menu_input();
                break;
            case GAME_STATE_PLAYING:
                // Gérer les entrées du jeu
                break;
            case GAME_STATE_COMBAT:
                // Gérer les entrées du combat
                break;
        }
    }
    printf("Quitter le jeu. À bientôt !\n");
}
