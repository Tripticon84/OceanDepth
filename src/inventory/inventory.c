#include "inventory.h"

#include <stddef.h>
#include <stdlib.h>


void init_inventory(Inventory* inv) {
    inv->nb_objets = 0;
    inv->equipedWeapon = NULL;
    inv->equipedHelmet = NULL;
    inv->equipedSuit = NULL;
    inv->equipedGloves = NULL;
    inv->equipedBoots = NULL;
}

void clean_inventory(Inventory* inv) { free(inv); }
