#ifndef OCEANDEPTH_MAP_H
#define OCEANDEPTH_MAP_H

#include <stdbool.h>
#include "../player/player.h"

typedef enum {
    SURFACE,
    REEF,
    WRECK,
    ALGAE_FOREST,
    CAVE,
    SHOP,
    EMPTY
} ZoneKind;

typedef struct {
    char icon[10];
    char name[50];
    char description[50];
} ZoneType;

typedef struct {
    char icon[10];
    char name[50];
    ZoneKind type;
    char description[50];
    short minMonsterCount;
    short maxMonsterCount;
    bool isDiscovered;
    bool hasBeenDefeated;
} CaseZone;

typedef struct {
    int depth;
    CaseZone cases[4];
} Zone;

typedef struct {
    Zone* zones;
    int numZones;
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

// Affiche la carte (zone actuelle et sélection)
void display_map(void);

// Gère les entrées utilisateur liées à la carte (ZQSD ou flèches, E pour entrer)
void handle_map_input(void);

/**
 * Retourne le nom d'un type de zone.
 * @param type Type de zone (ZoneKind).
 * @return Chaîne de caractères représentant le nom du type.
 */
const char* get_zone_type_name(ZoneKind type);

/**
 * Gère les entrées utilisateur liées à la carte.
 */
void handle_map_input();

// Retourne la profondeur (m) de la zone actuellement sélectionnée dans l'UI carte
int map_get_selected_depth(void);

#endif //OCEANDEPTH_MAP_H
