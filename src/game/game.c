#include "game.h"
#include <stdlib.h>
#include <stdio.h>

#include "../combat/combat.h"
#include "../display_combat/display_combat.h"
#include "../menu/menu.h"
#include "../save/save.h"
#include "../utils/utils.h"
#include "../shop.h"

int running = 1;
GameState currentGameState = GAME_STATE_MENU;

Monster* monsters[4];
int* monstersCount = 0;
Diver* player;
Inventory* inventory;
int depth = 600;
Map gameMap;

void init_game(void) {
    player = malloc(sizeof(Diver));
    inventory = malloc(sizeof(Inventory));
    monstersCount = malloc(sizeof(int));
    for (int i = 0; i < 4; ++i) {
        monsters[i] = malloc(sizeof(Monster));
    }
    gameMap.zones = malloc(sizeof(Zone));
    if (!gameMap.zones) {
        fprintf(stderr, "Erreur d'allocation de la carte\n");
        return;
    }

    init_player(player);
    init_starting_inventory(inventory);
    first_init_zone();
    init_next_zone();
}

void menu_loop(void) {
    GameState previousGameState = currentGameState;

    while (running) {
        check_terminal_size();
        if (previousGameState != currentGameState) {
            if (previousGameState == GAME_STATE_MENU && currentGameState == GAME_STATE_SAVE_MENU_CREATE) {
                clear_terminal();
            }
            if (previousGameState == GAME_STATE_MENU && currentGameState == GAME_STATE_SAVE_MENU_LOAD) {
                clear_terminal();
            }
            if (previousGameState == GAME_STATE_SAVE_MENU_LOAD && currentGameState == GAME_STATE_PLAYING) {
                clear_terminal();
            }
            if (previousGameState == GAME_STATE_PLAYING && currentGameState == GAME_STATE_MENU) {
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
                display_saves_menu();
                handle_create_save_menu_input();
                break;
            case GAME_STATE_SAVE_MENU_LOAD:
                display_saves_menu();
                handle_load_save_menu_input();
                break;
            case GAME_STATE_PLAYING:
                currentGameState = GAME_STATE_MAP;
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
        if (previousGameState != currentGameState) {
            clear_terminal();
            previousGameState = currentGameState;
        }

        clear_terminal();
        switch (currentGameState) {
            case GAME_STATE_MAP:
                display_map();
                handle_map_input();
                break;
            case GAME_STATE_INVENTORY:
                display_inventory(&player->inventory);
                getchar();
                clear_input_buffer();
                currentGameState = GAME_STATE_MAP;
                break;
            case GAME_STATE_SHOP: {
                setup_shop(player, inventory);
                int depthMeters = map_get_selected_depth();
                showShop(depthMeters);
                currentGameState = GAME_STATE_MAP;
                break;
            }
            case GAME_STATE_SAVE_MENU_CREATE:
                display_saves_menu();
                handle_create_save_menu_input();
                // À la sortie du menu de sauvegarde, revenir à la carte sauf si retour menu demandé
                if (currentGameState == GAME_STATE_MENU) {
                    return;
                }
                if (currentGameState == GAME_STATE_SAVE_MENU_CREATE) {
                    currentGameState = GAME_STATE_MAP;
                }
                break;
            case GAME_STATE_SAVE_MENU_LOAD:
                display_saves_menu();
                handle_load_save_menu_input();
                if (currentGameState == GAME_STATE_MENU) {
                    return;
                }
                if (currentGameState == GAME_STATE_SAVE_MENU_LOAD) {
                    currentGameState = GAME_STATE_MAP;
                }
                break;
            case GAME_STATE_COMBAT:
                clear_terminal();
                combat_loop();
                break;
            case GAME_STATE_REWARD:
                // TODO : Afficher et générer les récompenses
                currentGameState = GAME_STATE_MAP;
                break;
            case GAME_STATE_GAME_OVER:
                currentGameState = GAME_STATE_MENU;
                return;
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
        finishTurn = false;
        remainingAttacks = max_attacks_per_turn();
        increase_fatigue();
        while (!finishTurn) {
            clear_terminal();
            display_combat_interface(&remainingAttacks);
            handle_combat_input(&remainingAttacks, &finishTurn);
        }
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
