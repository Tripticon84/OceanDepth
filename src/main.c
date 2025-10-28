#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "player/player.h"
#include "utils/utils.h"

#include <locale.h>

#include "game/game.h"
#include "save/save.h"


int main(void) {
    SetConsoleOutputCP(CP_UTF8); // Fix les problèmes d'affichage des accents
    setlocale(LC_ALL, ".UTF8");


    // Setup terminal
    get_terminal_size(&terminalSize);
    // while (terminalSize.cols <= 80 || terminalSize.rows <= 27) {
    //     get_terminal_size(&terminalSize);
    //     clear_terminal();
    //     printf(
    //         "Veuillez agrandir la fenêtre du terminal (min 80x27)\n"
    //         "Taille actuelle : %dx%d\n", terminalSize.cols, terminalSize.rows);
    //     Sleep(100);
    // }

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

    Monster monster1, monster2, monster3, monster4;
    monster1.id = 1;
    strcpy(monster1.icon, "🐙");
    strcpy(monster1.name, "Poulpe Géantttee Monstre 2");
    monster1.health = 80;
    monster1.maxHealth = 80;
    monster1.minAttack = 10;
    monster1.maxAttack = 20;
    monster1.defense = 5;
    monster1.speed = 8;
    strcpy(monster1.specialEffect, "paralysiehjkdsadqs");
    monster1.isAlive = 1;
    monster2.id = 2;
    strcpy(monster2.icon, "🐙");
    strcpy(monster2.name, "Monstre 2fdsfsdfsdfsdfds");
    monster2.health = 250;
    monster2.maxHealth = 320;
    monster2.minAttack = 30;
    monster2.maxAttack = 50;
    monster2.defense = 15;
    monster2.speed = 4;
    strcpy(monster2.specialEffect, "paralysieezaezae");
    monster2.isAlive = 1;
    monster3.id = 3;
    strcpy(monster3.icon, "🐙");
    strcpy(monster3.name, "Monstre 3eeeeefdsfsdfdsfsd");
    monster3.health = 400;
    monster3.maxHealth = 500;
    monster3.minAttack = 60;
    monster3.maxAttack = 90;
    monster3.defense = 25;
    monster3.speed = 2;
    strcpy(monster3.specialEffect, "paralysie Monstre 2uy");
    monster3.isAlive = 1;
    strcpy(monster4.icon, "🐙");
    strcpy(monster4.name, "Mnt 4 Monstre 2hjbuhbhujfdsfds");
    monster4.id = 4;
    monster4.health = 600;
    monster4.maxHealth = 800;
    monster4.minAttack = 80;
    monster4.maxAttack = 120;
    monster4.defense = 35;
    monster4.speed = 1;
    strcpy(monster4.specialEffect, "Aucun");
    monster4.isAlive = 1;

    // display_combat_interface(player, (Monster[]){monster1, monster2, monster3, monster4}, 4, 500, player->pearls);
    // display_main_menu();

    // save_game(1, player, NULL, 100, "Zone Test 1", (Monster[]){monster1, monster2, monster3, monster4}, 4);
    // save_game(2, player, NULL, 200, "Zone Test 22", (Monster[]){monster1, monster2, monster3, monster4}, 4);
    // save_game(3, player, NULL, 300, "Zone Test 333", (Monster[]){monster1, monster2, monster3, monster4}, 4);

    // get_saves_infos(1);
    // display_saves_menu();

    menu_loop();


    clean_player(player);
    // clean_inventory(inv);

    return 0;
}
