#ifndef OCEANDEPTH_SHOP_H
#define OCEANDEPTH_SHOP_H

#include "../inventory/inventory.h"
#include "../player/player.h"

/**
 * Configure le contexte de la boutique.
 * @param player Pointeur vers le joueur actuel.
 * @param inventory Pointeur vers l'inventaire du joueur.
 */
void setup_shop(Diver* player, Inventory* inventory);

/**
 * Affiche la boutique et permet d'acheter des objets.
 * @param maxDepth Profondeur maximale atteinte (1 à 5). Plus profonde = meilleurs objets.
 */
void showShop(int maxDepth);

#endif // OCEANDEPTH_SHOP_H
