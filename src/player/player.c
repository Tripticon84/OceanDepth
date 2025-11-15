#include "player.h"

#include <stdio.h>
#include <stdlib.h>


void init_player(Diver* player) {
    player->maxHealth = 100;
    player->health = player->maxHealth;
    player->maxOxygen = 100;
    player->oxygen = player->maxOxygen;
    player->maxTiredness = 5;
    player->tiredness = 0;
    player->pearls = 10;
    init_starting_inventory(&player->inventory);
    player->zoneIndex = 0;
    player->caseIndex = 0;
}

void clean_player(Diver* player) { free(player); }

void print_player(Diver* player) {
    printf("=== Plongeur ===\n");
    printf("Santé: %d/%d\n", player->health, player->maxHealth);
    printf("Oxygène: %d/%d\n", player->oxygen, player->maxOxygen);
    printf("Fatigue: %d/%d\n", player->tiredness, player->maxTiredness);
    printf("Perles: %d\n", player->pearls);
    printf("=== Équipement Équipé ===\n");
    printf("Arme: %s\n", player->inventory.equipedWeapon.name);
    printf("Arme: Aucune\n");

    printf("Casque: %s\n", player->inventory.equipedHelmet.name);
    printf("Casque: Aucun\n");
    printf("Combinaison: %s\n", player->inventory.equipedSuit.name);
    printf("Combinaison: Aucune\n");
    printf("Gants: %s\n", player->inventory.equipedGloves.name);
    printf("Gants: Aucun\n");
    printf("Bottes: %s\n", player->inventory.equipedBoots.name);
    printf("Bottes: Aucune\n");

    printf("=== Inventaire ===\n");
    for (int i = 0; i < player->inventory.nb_objets; i++) {
        Item* item = &player->inventory.objets[i];
        printf("%d. %s (x%d) - Rareté: %d\n", i + 1, item->name, item->quantity, item->rarity);
    }
}
