#include "rewards.h"

#include <stdio.h>
#include <string.h>
#include "../utils/utils.h"
#include "../inventory/inventory.h"

void display_reward_item(Item* item) {
    if (item == NULL) {
        return;
    }

    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║                    💎 TRÉSOR DÉCOUVERT ! 💎                      ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                  ║\n");
    printf("║    ⚓~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~⚓                   ║\n");
    printf("║   ╱                                                               ╲ ║\n");
    
    // Nom de l'objet centré
    int nameLen = calculate_text_width(item->name);
    int padding = (62 - nameLen) / 2;
    printf("║  ╱  ");
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", item->name);
    for (int i = 0; i < (62 - nameLen - padding); i++) printf(" ");
    printf("  ╲ ║\n");
    
    // Rareté
    char* rarity = get_item_rarity(item->rarity);
    int rarityLen = calculate_text_width(rarity);
    padding = (62 - rarityLen - 12) / 2;
    printf("║ ╱   ");
    for (int i = 0; i < padding; i++) printf(" ");
    printf("[QUALITÉ %s]", rarity);
    for (int i = 0; i < (62 - rarityLen - 12 - padding); i++) printf(" ");
    printf("   ╲ ║\n");
    
    printf("║ ║                                                              ║ ║\n");
    
    // Stats de l'objet
    if (item->minAttack > 0 && item->maxAttack > 0) {
        char attackLine[100];
        snprintf(attackLine, sizeof(attackLine), "⚡ Attaque: %d-%d", item->minAttack, item->maxAttack);
        int attackLen = calculate_text_width(attackLine);
        padding = (62 - attackLen) / 2;
        printf("║ ║  ");
        for (int i = 0; i < padding; i++) printf(" ");
        printf("%s", attackLine);
        for (int i = 0; i < (62 - attackLen - padding); i++) printf(" ");
        printf("  ║ ║\n");
    }
    
    if (item->defenseBonus > 0) {
        char defenseLine[100];
        snprintf(defenseLine, sizeof(defenseLine), "🛡️ Défense: +%d", item->defenseBonus);
        int defenseLen = calculate_text_width(defenseLine);
        padding = (62 - defenseLen) / 2;
        printf("║ ║  ");
        for (int i = 0; i < padding; i++) printf(" ");
        printf("%s", defenseLine);
        for (int i = 0; i < (62 - defenseLen - padding); i++) printf(" ");
        printf("  ║ ║\n");
    }
    
    if (item->oxygenCost > 0) {
        char oxygenLine[100];
        snprintf(oxygenLine, sizeof(oxygenLine), "💧 Consommation: %d oxygène/attaque", item->oxygenCost);
        int oxygenLen = calculate_text_width(oxygenLine);
        padding = (62 - oxygenLen) / 2;
        printf("║ ║  ");
        for (int i = 0; i < padding; i++) printf(" ");
        printf("%s", oxygenLine);
        for (int i = 0; i < (62 - oxygenLen - padding); i++) printf(" ");
        printf("  ║ ║\n");
    }
    
    if (strlen(item->effect) > 0 && strcmp(item->effect, "") != 0) {
        char effectLine[100];
        snprintf(effectLine, sizeof(effectLine), "⭐ Effet: %s", item->effect);
        int effectLen = calculate_text_width(effectLine);
        padding = (62 - effectLen) / 2;
        printf("║ ║  ");
        for (int i = 0; i < padding; i++) printf(" ");
        printf("%s", effectLine);
        for (int i = 0; i < (62 - effectLen - padding); i++) printf(" ");
        printf("  ║ ║\n");
    }
    
    if (item->quantity > 1) {
        char qtyLine[100];
        snprintf(qtyLine, sizeof(qtyLine), "📦 Quantité: x%d", item->quantity);
        int qtyLen = calculate_text_width(qtyLine);
        padding = (62 - qtyLen) / 2;
        printf("║ ║  ");
        for (int i = 0; i < padding; i++) printf(" ");
        printf("%s", qtyLine);
        for (int i = 0; i < (62 - qtyLen - padding); i++) printf(" ");
        printf("  ║ ║\n");
    }
    
    printf("║ ╲                                                              ╱ ║\n");
    printf("║  ╲____________________________________________________________╱  ║\n");
    printf("║                                                                  ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║           [Appuyez sur Entrée pour continuer]                    ║\n");
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
}

void display_reward_pearls(int pearls) {
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║                    💎 RÉCOMPENSE DÉCOUVERTE ! 💎                 ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                  ║\n");
    printf("║                          💎 PERLES 💎                            ║\n");
    printf("║                                                                  ║\n");
    
    char pearlsLine[100];
    snprintf(pearlsLine, sizeof(pearlsLine), "+%d perles", pearls);
    int pearlsLen = calculate_text_width(pearlsLine);
    int padding = (62 - pearlsLen) / 2;
    printf("║  ");
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", pearlsLine);
    for (int i = 0; i < (62 - pearlsLen - padding); i++) printf(" ");
    printf("  ║\n");
    
    printf("║                                                                  ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║           [Appuyez sur Entrée pour continuer]                    ║\n");
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
}

void display_rewards(Item items[], int itemCount, int pearls) {
    // Afficher les objets
    for (int i = 0; i < itemCount; i++) {
        display_reward_item(&items[i]);
        printf("\n");
    }
    
    // Afficher les perles si > 0
    if (pearls > 0) {
        display_reward_pearls(pearls);
    }
}

void add_pearls_to_player(Diver* player, int pearls) {
    if (player == NULL || pearls <= 0) {
        return;
    }
    player->pearls += pearls;
}

int add_rewards_to_player(Diver* player, Inventory* inv, Item items[], int itemCount, int pearls) {
    if (player == NULL || inv == NULL) {
        return 0;
    }
    
    // Ajouter les objets à l'inventaire
    for (int i = 0; i < itemCount; i++) {
        // Vérifier si l'inventaire est plein avant d'ajouter
        if (inv->nb_objets >= 8) {
            // Si c'est un consommable, on peut quand même essayer de l'ajouter
            // car add_item gère la fusion des consommables
            if (items[i].type.type != CONSUMABLE) {
                return 0; // Inventaire plein, impossible d'ajouter
            }
        }
        add_item(inv, items[i]);
    }
    
    // Ajouter les perles
    if (pearls > 0) {
        add_pearls_to_player(player, pearls);
    }
    
    return 1; // Succès
}

