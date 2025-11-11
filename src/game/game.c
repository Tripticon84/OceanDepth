#include "game.h"
#include <stdlib.h>

#include "../combat/combat.h"
#include "../display_combat/display_combat.h"
#include "../menu/menu.h"
#include "../save/save.h"
#include "../utils/utils.h"

int running = 1;
GameState currentGameState = GAME_STATE_MENU;

Monster* monsters[4];
int* monstersCount = 0;
Diver* player;
int depth = 600;

void init_game(void) {
    player = malloc(sizeof(Diver));
    monstersCount = malloc(sizeof(int));
    for (int i = 0; i < 4; ++i) {
        monsters[i] = malloc(sizeof(Monster));
    }

    init_player(player);
}

void menu_loop(void) {
    GameState previousGameState = currentGameState;

    while (running) {
        check_terminal_size();
        if (previousGameState != currentGameState) {
            // Menu principal -> Création de Sauvegarde
            if (previousGameState == GAME_STATE_MENU && currentGameState == GAME_STATE_SAVE_MENU_CREATE) {
                clear_terminal();
            }
            // Menu principal -> Liste des Sauvegardes
            if (previousGameState == GAME_STATE_MENU && currentGameState == GAME_STATE_SAVE_MENU_LOAD) {
                clear_terminal();
            }
            // Menu Sauvegardes -> Jeu
            if (previousGameState == GAME_STATE_SAVE_MENU_LOAD && currentGameState == GAME_STATE_PLAYING) {
                // Menu Save -> Jeu
                // Initialisation du jeu
                clear_terminal();
            }
            // Jeu -> Menu principal
            if (previousGameState == GAME_STATE_PLAYING && currentGameState == GAME_STATE_MENU) {
                // Sortie du jeu
                // clear_terminal();
                // display_main_menu();
            }
            previousGameState = currentGameState;
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
                currentGameState = GAME_STATE_COMBAT;
                game_loop();
                break;
            default:
                break;
        }
    }
    printf("Quitter le jeu. À bientôt !\n");
}

void game_loop(void) {
    GameState previousGameState = currentGameState;

    while (running) {
        check_terminal_size();
        // Map -> Menu principal
        if (previousGameState == GAME_STATE_MAP && currentGameState == GAME_STATE_MENU) {
            clear_terminal();
        }
        // Map -> Boutique
        if (previousGameState == GAME_STATE_MAP && currentGameState == GAME_STATE_SHOP) {
            clear_terminal();
        }
        // Boutique -> Map
        if (previousGameState == GAME_STATE_SHOP && currentGameState == GAME_STATE_MAP) {
            clear_terminal();
        }
        // Map -> Combat
        if (previousGameState == GAME_STATE_MAP && currentGameState == GAME_STATE_COMBAT) {
            clear_terminal();
        }
        // Combat -> Récompense
        if (previousGameState == GAME_STATE_COMBAT && currentGameState == GAME_STATE_REWARD) {
            clear_terminal();
        }
        // Récompense -> Map
        if (previousGameState == GAME_STATE_REWARD && currentGameState == GAME_STATE_MAP) {
            clear_terminal();
        }
        // Combat -> Game Over
        if (previousGameState == GAME_STATE_COMBAT && currentGameState == GAME_STATE_GAME_OVER) {
            clear_terminal();
        }
        // Game Over -> Menu principal
        if (previousGameState == GAME_STATE_GAME_OVER && currentGameState == GAME_STATE_MENU) {
            clear_terminal();
            return;
        }

        previousGameState = currentGameState;
        clear_terminal();

        switch (currentGameState) {
            case GAME_STATE_MAP:
                //
                break;
            case GAME_STATE_INVENTORY:
                break;
            case GAME_STATE_SHOP:
                //
                break;
            case GAME_STATE_COMBAT:
                //
                clear_terminal();
                combat_loop();
                break;
            case GAME_STATE_REWARD:
                // TODO : Afficher et générer les récompenses
                break;
            case GAME_STATE_GAME_OVER:
                //
                currentGameState = GAME_STATE_MENU;
                break;
            default:
                break;
        }
    }
}

void combat_loop(void) {
    bool inCombat = true;
    int remainingAttacks = 3;
    bool finishTurn = false;

    generate_monsters_in_zone(monsters, 550, monstersCount);
    sort_monsters_by_speed(monsters, *monstersCount);
    printf("%d", *monstersCount);
    sleep_ms(1000);
    SpecialEffect special_effect = MONSTER_EFFECT_NONE;


    while (inCombat) {
        clear_terminal();

        // Boucle du joueur
        finishTurn = false;
        remainingAttacks = max_attacks_per_turn();
        increase_fatigue();
        while (!finishTurn) {
            clear_terminal();
            display_combat_interface(&remainingAttacks);
            handle_combat_input(&remainingAttacks, &finishTurn);
        }

        // Boucle des créatures
        for (int i = 0; i < *monstersCount; ++i) {
            if (monsters[i]->isAlive) {
                monster_attacks_player(monsters[i], special_effect);

                printf("%s attaque...\n", monsters[i]->name);
                sleep_ms(2000);
                clear_terminal();
                display_combat_interface(&remainingAttacks);
                sleep_ms(2000);
            }
        }

        if (player->oxygen <= 0) player->health -= 5;

        // Vérification de la fin du combat
        if (is_any_monster_alive() == false) {
            inCombat = false;
            printf("Vous avez vaincu toutes les créatures !\n");
            sleep_ms(2500);
            currentGameState = GAME_STATE_REWARD;
        } else if (player->health <= 0) {
            inCombat = false;
            printf("Vous avez été vaincu...\n");
            sleep_ms(3000);
            currentGameState = GAME_STATE_GAME_OVER;
            return;
        }
    }
}
