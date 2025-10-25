#include "player.h"

#include <stdlib.h>


void init_player(Diver* player) {
    player->maxHealth = 100;
    player->health = player->maxHealth;
    player->maxOxygen = 100;
    player->oxygen = player->maxOxygen;
    player->maxTiredness = 5;
    player->tiredness = 1;
    player->pearls = 10;
    // player->inventory = inv;
}

void clean_player(Diver* player) { free(player); }

