#ifndef OCEANDEPTH_GAME_H
#define OCEANDEPTH_GAME_H

#include "../monster/monster.h"
#include "../player/player.h"
#include "../map/map.h"
#include "../inventory/inventory.h"

/**
 * @enum GameState
 * @brief Représente les différents états possibles du jeu.
 */
typedef enum {
    GAME_STATE_MENU,               /**< Menu principal */
    GAME_STATE_SAVE_MENU_CREATE,   /**< Menu de création de sauvegarde */
    GAME_STATE_SAVE_MENU_LOAD,     /**< Menu de chargement de sauvegarde */
    GAME_STATE_PLAYING,            /**< Jeu en cours */
    GAME_STATE_MAP,                /**< Affichage de la carte */
    GAME_STATE_SHOP,               /**< Boutique */
    GAME_STATE_INVENTORY,          /**< Inventaire */
    GAME_STATE_REWARD,             /**< Récompense */
    GAME_STATE_GAME_OVER,          /**< Fin de partie */
    GAME_STATE_COMBAT              /**< Combat */
} GameState;

/**
 * @brief État courant du jeu.
 */
extern GameState currentGameState;

/**
 * @brief Indique si le jeu est en cours d'exécution (1) ou non (0).
 */
extern int running;

/**
 * @brief Tableau des pointeurs vers les monstres présents dans le jeu (taille maximale : 4).
 */
extern Monster* monsters[4];

/**
 * @brief Pointeur vers le nombre de monstres actuellement présents.
 */
extern int* monstersCount;

/**
 * @brief Pointeur vers le joueur (plongeur).
 */
extern Diver* player;

/**
 * @brief Pointeur vers l'inventaire du joueur.
 */
extern Inventory* inventory;

/**
 * @brief Profondeur actuelle atteinte dans le jeu.
 */
extern int depth;

/**
 * @brief Structure représentant la carte du jeu.
 */
extern Map gameMap;
/**
 * Initialise le jeu, les variables globales et les ressources nécessaires.
 */
void init_game(void);

/**
 * Boucle principale du menu, gère l'affichage et les interactions utilisateur dans le menu.
 */
void menu_loop(void);

/**
 * Boucle principale du jeu, gère la progression et les événements du jeu.
 */
void game_loop(void);

/**
 * Boucle de combat, gère les interactions et la logique lors des combats.
 */
void combat_loop(void);

/**
 *
 */
void cleanup_game(void);
#endif //OCEANDEPTH_GAME_H
