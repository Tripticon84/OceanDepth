#ifndef OCEANDEPTH_COMBAT_H
#define OCEANDEPTH_COMBAT_H

#include "../monster/monster.h"


// Attaque du plongeur

void player_attack_monster(Monster* target);

int calculate_player_damage(Monster* target);

void consume_oxygen(int cost);

void increase_fatigue();

// Attaque d'un monstre

void monster_attacks_player(Monster* monster, SpecialEffect specialEffect);

int calculate_monster_damage(Monster* monster);

void handle_combat_input(int* remainingAttacks, bool* finishTurn);

int max_attacks_per_turn(void);

#endif //OCEANDEPTH_COMBAT_H
