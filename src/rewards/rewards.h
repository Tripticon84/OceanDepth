#ifndef OCEANDEPTH_REWARDS_H
#define OCEANDEPTH_REWARDS_H

#include "../inventory/inventory.h"
#include "../player/player.h"

/**
 * @brief Affiche l'interface de récompense pour un objet
 * @param item L'objet à afficher comme récompense
 */
void display_reward_item(Item* item);

/**
 * @brief Affiche l'interface de récompense pour des perles
 * @param pearls Le nombre de perles gagnées
 */
void display_reward_pearls(int pearls);

/**
 * @brief Affiche l'interface de récompense complète (objets + perles)
 * @param items Tableau d'objets récompensés
 * @param itemCount Nombre d'objets dans le tableau
 * @param pearls Nombre de perles gagnées
 */
void display_rewards(Item items[], int itemCount, int pearls);

/**
 * @brief Ajoute des perles au joueur
 * @param player Pointeur vers le joueur
 * @param pearls Nombre de perles à ajouter
 */
void add_pearls_to_player(Diver* player, int pearls);

/**
 * @brief Ajoute une récompense complète (objets + perles) au joueur
 * @param player Pointeur vers le joueur
 * @param inv Pointeur vers l'inventaire du joueur
 * @param items Tableau d'objets à ajouter
 * @param itemCount Nombre d'objets dans le tableau
 * @param pearls Nombre de perles à ajouter
 * @return 1 si succès, 0 si échec (inventaire plein)
 */
int add_rewards_to_player(Diver* player, Inventory* inv, Item items[], int itemCount, int pearls);

#endif //OCEANDEPTH_REWARDS_H

