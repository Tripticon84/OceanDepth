#ifndef OCEANDEPTH_MONSTERS_H
#define OCEANDEPTH_MONSTERS_H

#include <stdbool.h>

typedef enum {
    MONSTER_EFFECT_KRAKEN,
    MONSTER_EFFECT_SHARK,
    MONSTER_EFFECT_MEDUSA,
    MONSTER_EFFECT_SWORD_FISH,
    MONSTER_EFFECT_GIANT_CRAB,
    MONSTER_EFFECT_NONE
} SpecialEffect;

typedef struct {
    SpecialEffect type;
    char name[50];
    char description[200];
} MonsterSpecialEffect;

typedef struct {
    int minHP;
    int maxHP;
    int minAttack;
    int maxAttack;
    int defense;
    int speed;
    char icon[5];
    SpecialEffect specialEffect;
} MonsterType;

#define NUMBER_OF_MONSTER_TYPES 5

typedef enum {
    MONSTER_TYPE_KRAKEN,
    MONSTER_TYPE_SHARK,
    MONSTER_TYPE_MEDUSA,
    MONSTER_TYPE_SWORD_FISH,
    MONSTER_TYPE_GIANT_CRAB
} MonsterKind;

extern const MonsterType MONSTER_TYPES[NUMBER_OF_MONSTER_TYPES];

typedef struct {
    int id;
    char icon[5]; // Emoji représentant le monstre
    char name[100];
    int health;
    int maxHealth;
    int minAttack;
    int maxAttack;
    int defense;
    int speed;
    SpecialEffect specialEffect;
    bool isAlive; // 1 pour vivant, 0 pour mort
} Monster;

/**
 * @brief Obtient le nom d'un effet spécial de monstre.
 *
 * La chaîne retournée pointe vers des données statiques internes ;
 *
 * @param type Index de l'effet spécial (valeur de SpecialEffect).
 * @return char* Pointeur vers le nom de l'effet.
 */
const char* get_monster_effects_name(int type);

/**
 * @brief Obtient la description d'un effet spécial de monstre.
 *
 * La chaîne retournée pointe vers des données statiques internes ;
 *
 * @param type Index de l'effet spécial (valeur de SpecialEffect).
 * @return char* Pointeur vers la description de l'effet.
 */
const char* get_monster_effects_description(int type);


/**
 * @brief Obtient un nom aléatoire pour un type de monstre.
 *
 * La chaîne retournée pointe vers des données statiques internes ;
 *
 * @param type Index du type de monstre (valeur de MonsterKind).
 * @return char* Pointeur vers le nom choisi.
 */
const char* get_random_monster_name(int type);


/**
 * @brief Initialise un objet Monster avec des valeurs aléatoires/attribuées selon le type.
 *
 * Remplit les champs (icon, id, name, health, maxHealth, minAttack, maxAttack, defense,
 * speed, specialEffect, isAlive).
 *
 * @param monster Pointeur vers le Monster à initialiser (doit être non-NULL et alloué).
 * @param type Type de monstre à utiliser (valeur de MonsterKind).
 * @param id Identifiant unique à assigner au monstre.
 */
void init_monster(Monster* monster, int type, int id);

/**
 * @brief Trie un tableau de pointeurs vers Monster par vitesse (décroissant).
 *
 * @param list Tableau de pointeurs vers Monster (taille `count`).
 * @param count Nombre d'éléments dans `list`.
 */
void sort_monsters_by_speed(Monster* list[], int count);

/**
 * @brief Génère des monstres pour une zone donnée en fonction de la profondeur.
 *
 * Cette fonction remplit le tableau 'list' avec des Monster initialisés et écrit le nombre
 * de monstres générés dans '*monstersCount'.
 *
 * Comportement attendu :
 *  - 'list' doit être préalloué avec une capacité de 4 pour recevoir les monstres.
 *  - 'depth' influence le nombre et les types de monstres créés.
 *  - '*monstersCount' sera mis à jour avec le compteur réel de monstres.
 *
 * @param list Tableau préalloué de pointeurs vers Monster pour recevoir les monstres.
 * @param depth Profondeur utilisée pour déterminer la difficulté et les types.
 * @param monstersCount Pointeur vers un entier où sera écrit le nombre de monstres générés.
 */
void generate_monsters_in_zone(Monster* list[], int depth, int* monstersCount);

/**
 * @brief Vérifie si au moins un monstre est encore vivant.
 *
 * @return true Si au moins un monstre est vivant.
 * @return false Si tous les monstres sont morts.
 */
bool is_any_monster_alive();

/**
 * @brief Affiche les informations d'un monstre.
 *
 * Affiche : nom, icône, santé actuelle/max, attaque min-max, défense, vitesse, effet spécial.
 *
 * @param monster Pointeur vers le Monster à afficher (doit être non-NULL).
 */
void display_monster(Monster* monster);

#endif //OCEANDEPTH_MONSTERS_H
