#ifndef OCEANDEPTH_MAP_H
#define OCEANDEPTH_MAP_H

#include <stdbool.h>
#include "../player/player.h"

/**
 * @enum ZoneKind
 * Types de zones possibles sur la carte.
 */
typedef enum {
    SURFACE,        /**< Surface de l'océan */
    REEF,           /**< Récif corallien */
    WRECK,          /**< Épave */
    ALGAE_FOREST,   /**< Forêt d'algues */
    CAVE,           /**< Grotte sous-marine */
    SHOP,           /**< Boutique */
    EMPTY           /**< Zone vide */
} ZoneKind;

/**
 * @struct ZoneType
 * Définit un type de zone avec son icône, son nom et sa description.
 */
typedef struct {
    char icon[10];          /**< Icône représentant la zone */
    char name[50];          /**< Nom du type de zone */
    char description[50];   /**< Description du type de zone */
} ZoneType;

/**
 * @struct CaseZone
 * Représente une case individuelle dans une zone, avec ses propriétés.
 */
typedef struct {
    char icon[10];              /**< Icône de la case */
    char name[50];              /**< Nom de la case */
    ZoneKind type;              /**< Type de la case (ZoneKind) */
    char description[50];       /**< Description de la case */
    short minMonsterCount;      /**< Nombre minimum de monstres */
    short maxMonsterCount;      /**< Nombre maximum de monstres */
    bool isDiscovered;          /**< Indique si la case a été découverte */
    bool hasBeenDefeated;       /**< Indique si la case a été vaincue */
} CaseZone;

/**
 * @struct Zone
 * Représente une zone du jeu, composée de plusieurs cases et d'une profondeur.
 */
typedef struct {
    int depth;              /**< Profondeur de la zone (en mètres) */
    CaseZone cases[4];      /**< Tableau de cases composant la zone */
} Zone;

/**
 * @struct Map
 * Structure principale représentant la carte du jeu.
 */
typedef struct {
    Zone* zones;        /**< Tableau dynamique de zones */
    int numZones;       /**< Nombre total de zones */
} Map;
/**
 * Initialise la première zone du jeu.
 */
void first_init_zone();

/**
 * Initialise la zone suivante lors de la progression du joueur.
 */
void init_next_zone();

/**
 * Déplace le joueur vers une zone donnée.
 * @param player Pointeur vers le joueur (Diver).
 * @param destination Pointeur vers la zone de destination.
 * @return 0 en cas de succès, autre valeur en cas d'échec.
 */
int move_to_zone(Diver* player, Zone* destination);

/**
 * Vérifie si une case de zone est accessible.
 * @param caseZone Pointeur vers la case de zone à vérifier.
 * @return true si accessible, false sinon.
 */
bool can_access_zone(CaseZone* caseZone);

/**
 * Indique si une case de zone est visible pour le joueur.
 * @param zoneIndex Index de la zone.
 * @param caseIndex Index de la case dans la zone.
 * @return true si visible, false sinon.
 */
bool is_case_zone_visible(int zoneIndex, int caseIndex);

/**
 * Affiche la carte du jeu, incluant la zone actuelle et la sélection du joueur.
 */
void display_map(void);

/**
 * Gère les entrées utilisateur liées à la carte.
 */
void handle_map_input(void);

/**
 * Retourne le nom d'un type de zone.
 * @param type Type de zone (ZoneKind).
 * @return Chaîne de caractères représentant le nom du type.
 */
const char* get_zone_type_name(ZoneKind type);

/**
 * Retourne la profondeur (en mètres) de la zone actuellement sélectionnée dans l'interface utilisateur de la carte.
 * @return Profondeur de la zone sélectionnée (int, en mètres).
 */
int map_get_selected_depth(void);
#endif //OCEANDEPTH_MAP_H
