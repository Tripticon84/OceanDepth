#include "monster.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../game/game.h"
#include "../utils/utils.h"


const MonsterType MONSTER_TYPES[5] = {
    [MONSTER_TYPE_KRAKEN] = {.minHP = 120, .maxHP = 180, .minAttack = 25, .maxAttack = 40, .defense = 10, .speed = 5, .icon = "🦑", .specialEffect = MONSTER_EFFECT_KRAKEN},
    [MONSTER_TYPE_SHARK] = {.minHP = 60, .maxHP = 100, .minAttack = 15, .maxAttack = 25, .defense = 5, .speed = 8, .icon = "🦈", .specialEffect = MONSTER_EFFECT_SHARK},
    [MONSTER_TYPE_MEDUSA] = {.minHP = 20, .maxHP = 40, .minAttack = 8, .maxAttack = 15, .defense = 3, .speed = 10, .icon = "🪼", .specialEffect = MONSTER_EFFECT_MEDUSA},
    [MONSTER_TYPE_SWORD_FISH] = {.minHP = 70, .maxHP = 90, .minAttack = 18, .maxAttack = 28, .defense = 7, .speed = 6, .icon = "🐟", .specialEffect = MONSTER_EFFECT_SWORD_FISH},
    [MONSTER_TYPE_GIANT_CRAB] = {.minHP = 80, .maxHP = 120, .minAttack = 12, .maxAttack = 20, .defense = 12, .speed = 4, .icon = "🦀", .specialEffect = MONSTER_EFFECT_GIANT_CRAB}
};

const MonsterSpecialEffect MONSTER_SPECIAL_EFFECTS[6] = {
    [MONSTER_EFFECT_KRAKEN] = {.type = MONSTER_EFFECT_KRAKEN, .name = "Etreinte tentaculaire", .description = "Le Kraken effectue 2 attaques consecutives."},
    [MONSTER_EFFECT_SHARK] = {.type = MONSTER_EFFECT_SHARK, .name = "Frenesie sanguinaire", .description = "Le Requin inflige +30% de degats si ses PV sont inferieurs a 50%."},
    [MONSTER_EFFECT_MEDUSA] = {.type = MONSTER_EFFECT_MEDUSA, .name = "Piqure paralysante", .description = "La Meduse reduit les attaques du joueur de 1 au prochain tour."},
    [MONSTER_EFFECT_SWORD_FISH] = {.type = MONSTER_EFFECT_SWORD_FISH, .name = "Charge perforante", .description = "Le Poisson-Epee ignore 2 points de defense lors de son attaque."},
    [MONSTER_EFFECT_GIANT_CRAB] = {.type = MONSTER_EFFECT_GIANT_CRAB, .name = "Carapace durcie", .description = "Le Crabe Geant reduit les degats subis de 20%."},
    [MONSTER_EFFECT_NONE] = {.type = MONSTER_EFFECT_NONE, .name = "Aucun", .description = "Pas d'effet special."}
};

const char* get_monster_effects_name(int type) {
    return MONSTER_SPECIAL_EFFECTS[type].name;
}

const char* get_monster_effects_description(int type) {
    return MONSTER_SPECIAL_EFFECTS[type].description;
}


const char* get_random_monster_name(int type) {
    static const char* names[][NUMBER_OF_MONSTER_TYPES] = {
        [MONSTER_TYPE_KRAKEN] = {"Kraken des Abysses", "Tentacule Geant", "Le Devoreur des Mers", "Le Monstre des Profondeurs", "L'Etreinte du Kraken"},
        [MONSTER_TYPE_SHARK] = {"Requin Blanc", "Chasseur des Oceans", "Lame Aquatique", "Furie des Mers", "Seigneur des Vagues"},
        [MONSTER_TYPE_MEDUSA] = {"Meduse Lumineuse", "Danseuse des Profondeurs", "Lueur Mortelle", "Spectre des Mers", "Gardienne des Abysses"},
        [MONSTER_TYPE_SWORD_FISH] = {"Poisson-Epee Rapide", "Lame Aquatique", "Fendant les Vagues", "Chasseur des Profondeurs", "Eclaireur des Mers"},
        [MONSTER_TYPE_GIANT_CRAB] = {"Crabe Geant", "Pinces de Fer", "Le Colosse des Sables", "Gardien des Recifs", "Le Titan Cotier"}
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
    monster->specialEffect = MONSTER_TYPES[type].specialEffect;
    monster->isAlive = true;
}

void display_monster(Monster* monster) {
    printf("\n%s\n", monster->name);
    printf("ID : %d\n", monster->id);
    printf("Icone : %s\n", monster->icon);
    printf("Santé : %d/%d\n", monster->health, monster->maxHealth);
    printf("Attaque : %d - %d\n", monster->minAttack, monster->maxAttack);
    printf("Défense : %d\n", monster->defense);
    printf("Vitesse : %d\n", monster->speed);
    printf("Effet Spécial : %s\n", get_monster_effects_name(monster->specialEffect));
}

void sort_monsters_by_speed(Monster* list[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (list[j]->speed < list[j + 1]->speed) {
                Monster* temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

void generate_monsters_in_zone(Monster* list[], int depth, int* monstersCount) {
    // Détermine la difficulté de la zone en fonction de la profondeur

    // double difficulty = floor(depth / 30);
    // int count = random(1, 2 + floor(difficulty / 5));
    int count = 0;

    if (depth < 50) count = 1;
    else if (depth < 200) count = random(1, 2);
    else if (depth < 500) count = random(2, 3);
    else if (depth > 500) count = random(3, 4);

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
        init_monster(list[i], type, i + 1);
    }

    *monstersCount = maxCount;
}

bool is_any_monster_alive() {
    for (int i = 0; i < *monstersCount; i++) {
        if (monsters[i]->isAlive == true)
            return true;
    }
    return false;
}
