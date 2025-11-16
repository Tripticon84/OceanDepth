#include "combat.h"

#include <stdio.h>

#include "../display_combat/display_combat.h"
#include "../game/game.h"
#include "../player/player.h"
#include "../utils/utils.h"


void handle_select_target_input(int* selectedTarget) {
    char input = getchar();
    switch (input) {
        case '1':
            *selectedTarget = 0;
            break;
        case '2':
            *selectedTarget = 1;
            break;
        case '3':
            *selectedTarget = 2;
            break;
        case '4':
            *selectedTarget = 3;
            break;
        default:
            *selectedTarget = -1;
            break;
    }
}

int max_attacks_per_turn(void) {
    if (player->tiredness <= 1) return 3;
    if (player->tiredness <= 3) return 2;
    if (player->tiredness <= 5) return 1;
    return 3;
}

int calculate_player_damage(Monster* target) {
    int min_attack = player->inventory.equipedWeapon.minAttack;
    int max_attack = player->inventory.equipedWeapon.maxAttack;
    int base_damage = random_num(min_attack, max_attack) + min_attack;
    int final_damage = base_damage - target->defense;
    if (final_damage < 1) final_damage = 1;

    return final_damage;
}

void player_attack_monster(Monster* target) {
    int damage = calculate_player_damage(target);

    if (target->specialEffect == MONSTER_EFFECT_GIANT_CRAB)
        damage = (int)(damage * 0.8); // Réduction des dégâts de 20%

    target->health -= damage;
    consume_oxygen(random_num(2, 4));

    if (target->health <= 0) {
        target->health = 0;
        target->isAlive = false;
    }
}


void handle_combat_input(int* remainingAttacks, bool* finishTurn) {
    int selectedTarget = -1;

    char input = getchar();
    switch (input) {
        case '1':
            // Attaquer
            if (*remainingAttacks <= 0)
                break;

            clear_terminal();
            while (selectedTarget < 0 || selectedTarget >= *monstersCount) {
                clear_terminal();
                display_target_selection_menu();
                handle_select_target_input(&selectedTarget);
            }
            player_attack_monster(monsters[selectedTarget]);
            (*remainingAttacks)--;
            break;
        case '2':
            // Compétences Marines
            break;
        case '3':
            // Consommer objet
            break;
        case '4':
            clear_terminal();
            display_monsters_infos();
            while (getchar() != '\n');
            getchar();
            break;
        case '5':
            // Terminer le tour
            *finishTurn = true;
            break;
        default:
            break;
    }
}

void monster_attacks_player(Monster* monster, SpecialEffect specialEffect) {
    int damage = calculate_monster_damage(monster);

    if (monster->specialEffect == MONSTER_EFFECT_KRAKEN)
        damage += calculate_monster_damage(monster);

    player->health -= damage;
    consume_oxygen(random_num(1, 2));

    if (player->health < 0) player->health = 0;
}

int calculate_monster_damage(Monster* monster) {
    int base_damage = random_num(monster->minAttack, monster->maxAttack);

    int suit_defense = player->inventory.equipedSuit.defenseBonus;
    int helmet_defense = player->inventory.equipedHelmet.defenseBonus;
    int final_damage = base_damage - (suit_defense + helmet_defense);

    if (final_damage < 1) final_damage = 1;

    if (monster->specialEffect == MONSTER_EFFECT_SWORD_FISH) {
        final_damage += 2; // Ignore 2 points de défense
    }
    if (monster->specialEffect == MONSTER_EFFECT_SHARK && monster->health < (monster->maxHealth / 2)) {
        final_damage = (int)(final_damage * 1.3); // +30% dégâts si PV < 50%
    }
    return final_damage;
}

void consume_oxygen(int cost) {
    player->oxygen -= cost;
    if (player->oxygen < 0) player->oxygen = 0;
}

void increase_fatigue() {
    if (player->tiredness + 1 > 5) {
        player->tiredness = 5;
    } else {
        player->tiredness += 1;
    }
}
