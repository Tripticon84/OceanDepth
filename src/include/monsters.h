#ifndef OCEANDEPTH_MONSTERS_H
#define OCEANDEPTH_MONSTERS_H

#include <stdbool.h>


typedef struct {
    int id;
    char name[100];
    int health;
    int maxHealth;
    int minAttack;
    int maxAttack;
    int defense;
    int speed;
    char specialEffect[20]; // "paralysie", "poison", "aucun"
    bool isAlive;           // 1 pour vivant, 0 pour mort
} Monster;


void init_monster(Monster* monster, int type, int id);

void generate_monsters_in_zone(Monster list[], int depth, int* monstersCount);

int get_monster_type_by_depth(int depth);

void display_monsters(Monster list[], int count);

#endif //OCEANDEPTH_MONSTERS_H
