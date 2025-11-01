#include "monster.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../utils/utils.h"


const MonsterType MONSTER_TYPES[5] = {
    [MONSTER_TYPE_KRAKEN] = {.minHP = 120, .maxHP = 180, .minAttack = 25, .maxAttack = 40, .defense = 10, .speed = 5, .icon = "🦑"},
    [MONSTER_TYPE_SHARK] = {.minHP = 60, .maxHP = 100, .minAttack = 15, .maxAttack = 25, .defense = 5, .speed = 8, .icon = "🦈"},
    [MONSTER_TYPE_MEDUSA] = {.minHP = 20, .maxHP = 40, .minAttack = 8, .maxAttack = 15, .defense = 3, .speed = 10, .icon = "🪼"},
    [MONSTER_TYPE_SWORD_FISH] = {.minHP = 70, .maxHP = 90, .minAttack = 18, .maxAttack = 28, .defense = 7, .speed = 6, .icon = "🐟"},
    [MONSTER_TYPE_GIANT_CRAB] = {.minHP = 80, .maxHP = 120, .minAttack = 12, .maxAttack = 20, .defense = 12, .speed = 4, .icon = "🦀"}
};

const char* get_random_monster_name(int type) {
    static const char* names[][NUMBER_OF_MONSTER_TYPES] = {
        [MONSTER_TYPE_KRAKEN] = {"Kraken des Abysses", "Tentacule Geant", "Le Dévoreur des Mers", "Le Monstre des Profondeurs", "L'Etreinte du Kraken"},
        [MONSTER_TYPE_SHARK] = {"Requin Blanc", "Chasseur des Oceans", "Lame Aquatique", "Furie des Mers", "Seigneur des Vagues"},
        [MONSTER_TYPE_MEDUSA] = {"Meduse Lumineuse", "Danseuse des Profondeurs", "Lueur Mortelle", "Spectre des Mers", "Gardienne des Abysses"},
        [MONSTER_TYPE_SWORD_FISH] = {"Poisson-Epee Rapide", "Lame Aquatique", "Fendant les Vagues", "Chasseur des Profondeurs", "Eclaireur des Mers"},
        [MONSTER_TYPE_GIANT_CRAB] = {"Crabe Geant", "Pinces de Fer", "Le Colosse des Sables", "Gardien des Récifs", "Le Titan Cotier"}
    };

    int index = random(0, 4);
    return names[type][index];
}

void init_monster(Monster* monster, int type, int id) {
    strcpy(monster->icon, MONSTER_TYPES[type].icon);
    monster->id = id;
    strcpy(monster->name, get_random_monster_name(type));
    monster->health = random(MONSTER_TYPES[type].minHP, MONSTER_TYPES[type].maxHP);
    monster->maxHealth = monster->health;
    monster->minAttack = MONSTER_TYPES[type].minAttack;
    monster->maxAttack = MONSTER_TYPES[type].maxAttack;
    monster->defense = MONSTER_TYPES[type].defense;
    monster->speed = MONSTER_TYPES[type].speed;
    strcpy(monster->specialEffect, "PLACEHOLDER");
    monster->isAlive = true;
}

void display_monster(Monster* monster) {
    printf("\n%s\n", monster->name);
    printf("Icone : %s\n", monster->icon);
    printf("Santé : %d/%d\n", monster->health, monster->maxHealth);
    printf("Attaque : %d - %d\n", monster->minAttack, monster->maxAttack);
    printf("Défense : %d\n", monster->defense);
    printf("Vitesse : %d\n", monster->speed);
    printf("Effet Spécial : %s\n", monster->specialEffect);
}

void generate_monsters_in_zone(Monster list[], int depth, int* monstersCount) {
    // Détermine la difficulté de la zone en fonction de la profondeur

    // double difficulty = floor(depth / 30);
    // int count = random(1, 2 + floor(difficulty / 5));
    int count = 0;

    if (depth < 50) count = 1;
    else if (depth < 200) count = random(1, 2);
    else if (depth < 500) count = random(2, 3);
    else if (depth > 500) count = random(2, 4);

    if (count < 1) count = 1;
    if (count > 4) count = 4;

    int maxCount = count;
    int kraken_present = 0; // 0 = absent, 1 = présent

    for (int i = 0; i < maxCount; ++i) {
        int type;
        if (depth <= 50) {
            type = random(1, 3);
            // depth < 50 : Kraken et Crabe géant exclus
        } else if (depth <= 150) {
            // depth entre 50 et 150 : Kraken exclu
            type = random(1, 4);
        } else {
            // depth > 150 : Kraken possible
            if (kraken_present) {
                // Si un kraken est déjà présent, on ne peut plus en recréer
                type = random(1, 4);
            } else {
                type = random(0, 4);
                if (type == MONSTER_TYPE_KRAKEN) {
                    kraken_present = 1;
                    if (maxCount > 2) maxCount = 2; // limiter le nombre total si un kraken apparaît
                }
            }
        }
        init_monster(&list[i], type, i + 1);
    }

    *monstersCount = maxCount;
}
