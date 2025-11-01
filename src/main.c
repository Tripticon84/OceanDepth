#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "player/player.h"
#include "utils/utils.h"

#include <locale.h>
#include <math.h>

#include "display_combat/display_combat.h"
#include "game/game.h"
#include "menu/menu.h"
#include "save/save.h"


int main(void) {
    SetConsoleOutputCP(CP_UTF8); // Fix les problèmes d'affichage des accents
    setlocale(LC_ALL, ".UTF8");
    srand((unsigned int)time(NULL));


    // Setup terminal
    get_terminal_size(&terminalSize);
    while (terminalSize.cols <= 80 || terminalSize.rows <= 27) {
        get_terminal_size(&terminalSize);
        clear_terminal();
        printf(
            "Veuillez agrandir la fenêtre du terminal (min 80x27)\n"
            "Taille actuelle : %dx%d\n", terminalSize.cols, terminalSize.rows);
        Sleep(100);
    }

    // while (true) {
    //     get_terminal_size(&TerminalSize);
    //     printf("%d %d\n", TerminalSize.rows, TerminalSize.cols);
    //     Sleep(100);
    //     clear_terminal();
    // }

    // Inventory* inv = malloc(sizeof(Inventory));
    // init_inventory(inv);
    Diver* player = malloc(sizeof(Diver));;
    init_player(player);


    player->health = 30;
    player->oxygen = 70;
    player->pearls = 222332;

    // Monster monster1, monster2, monster3, monster4, monster5;
    Monster monsters[4];
    // display_combat_interface(player, (Monster[]){monster1, monster2, monster3, monster4}, 4, 500, player->pearls);
    // display_main_menu();

    // save_game(1, player, NULL, 100, "Zone Test 1", (Monster[]){monster1, monster2, monster3, monster4}, 4);
    // save_game(2, player, NULL, 200, "Zone Test 22", (Monster[]){monster1, monster2, monster3, monster4}, 4);
    // save_game(3, player, NULL, 300, "Zone Test 333", (Monster[]){monster1, monster2, monster3, monster4}, 4);

    // get_saves_infos(1);
    // display_saves_menu();

    // menu_loop();
    // display_combat_interface(player, (Monster[]){monster1, monster2, monster3, monster4}, 4, 500, player->pearls);

    int* monstersCount = malloc(sizeof(int));
    generate_monsters_in_zone(monsters, 250, monstersCount);

    for (int i = 0; i < *monstersCount; ++i) {
        display_monster(&monsters[i]);
    }

    clean_player(player);
    // clean_inventory(inv);

    return 0;
}
