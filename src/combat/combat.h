#ifndef OCEANDEPTH_COMBAT_H
#define OCEANDEPTH_COMBAT_H

#include "../monster/monster.h"


// Attaque du plongeur

/**
 * Effectue une attaque du joueur contre un monstre cible.
 * @param target Pointeur vers le monstre ciblé.
 */
void player_attack_monster(Monster* target);

/**
 * Calcule les dégâts infligés par le joueur à un monstre.
 * @param target Pointeur vers le monstre ciblé.
 * @return Dégâts infligés.
 */
int calculate_player_damage(Monster* target);

/**
 * Consomme une quantité d'oxygène spécifiée.
 * @param cost Quantité d'oxygène à consommer.
 */
void consume_oxygen(int cost);

/**
 * Augmente la fatigue du joueur.
 */
void increase_fatigue(void);

// Attaque d'un monstre

/**
 * Effectue une attaque d'un monstre contre le joueur, avec effet spécial éventuel.
 * @param monster Pointeur vers le monstre attaquant.
 * @param specialEffect Effet spécial appliqué lors de l'attaque.
 */
void monster_attacks_player(Monster* monster, SpecialEffect specialEffect);

/**
 * Calcule les dégâts infligés par un monstre au joueur.
 * @param monster Pointeur vers le monstre attaquant.
 * @return Dégâts infligés.
 */
int calculate_monster_damage(Monster* monster);

/**
 * Gère les entrées utilisateur lors d'un tour de combat.
 * @param remainingAttacks Pointeur vers le nombre d'attaques restantes.
 * @param finishTurn Pointeur vers le booléen indiquant la fin du tour.
 */
void handle_combat_input(int* remainingAttacks, bool* finishTurn);

/**
 * Retourne le nombre maximal d'attaques autorisées par tour.
 * @return Nombre maximal d'attaques.
 */
int max_attacks_per_turn(void);
#endif //OCEANDEPTH_COMBAT_H
