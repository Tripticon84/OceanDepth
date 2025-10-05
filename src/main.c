#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "include/player.h"
#include "include/display.h"


int main(void) {
    SetConsoleOutputCP(CP_UTF8);

    Diver* player = malloc(sizeof(Diver));;
    init_player(player);

    printf("Infos du joueur :\n");
    printf("Santé : %d/%d\n", player->health, player->maxHealth);
    printf("Oxygène : %d/%d\n", player->oxygen, player->maxOxygen);
    printf("Fatigue : %d/%d\n", player->tiredness, player->maxTiredness);
    printf("Perles : %d\n", player->pearls);

    printf("Oxygène : [");
    display_progress_bar(20, player->maxOxygen, 5);
    printf("]\n");

    clean_player(player);

    return 0;
}
