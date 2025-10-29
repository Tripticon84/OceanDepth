#ifndef OCEANDEPTH_COMBAT_H
#define OCEANDEPTH_COMBAT_H

#include "../player/player.h"
#include "../monster/monster.h"
#include "../inventory/inventory.h"


// Attaque du plongeur


int can_attack(Diver *player);

void attack_monster(Diver *player, Monster *target, Item *weapon);

int calculate_player_damage(Diver *player, Item *weapon, Monster *target);

void consume_oxygen(Diver *player, int cost);

void increase_fatigue(Diver *player);

// Attaque d'un monstre

void sort_monster_by_speed(Monster list[], int count);

void monster_attacks_player(Monster *monster, Diver *player);

void apply_special_effect(Monster *monster, Diver *player, int *fatigueModifier);

int calculate_monster_damage(Monster *monster, Diver *player, Item *wetsuit);

// Compétences

#endif //OCEANDEPTH_COMBAT_H
