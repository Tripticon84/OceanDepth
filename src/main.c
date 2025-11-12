#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "game/game.h"
#include "player/player.h"


int main(void) {
    SetConsoleOutputCP(CP_UTF8); // Fix les problèmes d'affichage des accents
    setlocale(LC_ALL, ".UTF8");
    srand((unsigned int)time(NULL));

    init_game();
    // print_player(player);


    menu_loop();
    // combat_loop();

    // Pour la boutique:
    // setup_shop(player, inventory);
    // showShop(150); // 150 m = palier 3 de rareté (j'ai fait par multiples de 50m)

    // save_game(1, player, NULL, 100, "Zone Test 1", (Monster[]){monster1, monster2, monster3, monster4}, 4);
    // save_game(2, player, NULL, 200, "Zone Test 22", (Monster[]){monster1, monster2, monster3, monster4}, 4);
    // save_game(3, player, NULL, 300, "Zone Test 333", (Monster[]){monster1, monster2, monster3, monster4}, 4);

    // get_saves_infos(1);
    // display_saves_menu();

    clean_player(player);
    for (int i = 0; i < 4; ++i) {
        free(monsters[i]);
    }
    free(monstersCount);
    // clean_inventory(inv);

    return 0;
}
