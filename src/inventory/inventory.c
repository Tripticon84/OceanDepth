#include "inventory.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils.h"


void init_inventory(Inventory* inv) {
    inv->nb_objets = 0;
    inv->equipedWeapon = (Item){0};
    inv->equipedHelmet = (Item){0};
    inv->equipedSuit = (Item){0};
    inv->equipedGloves = (Item){0};
    inv->equipedBoots = (Item){0};
}

void init_starting_inventory(Inventory* inv) {
    if (inv == NULL) {
        return;
    }

    // Initialiser l'inventaire vide
    init_inventory(inv);

    // Créer le Trident Rouillé (arme de contact)
    Item trident;
    memset(&trident, 0, sizeof(Item));
    strcpy(trident.name, "Trident Rouillé");
    trident.rarity = COMMUN;
    trident.type.type = WEAPON_CONTACT;
    strcpy(trident.type.name, "Arme de contact");
    trident.minAttack = 10;
    trident.maxAttack = 15;
    trident.quantity = 1;
    trident.defenseBonus = 0;
    trident.oxygenCost = 3;
    strcpy(trident.effect, "");

    // Créer l'Armure Basique (combinaison)
    Item armor;
    memset(&armor, 0, sizeof(Item));
    strcpy(armor.name, "Combinaison Néoprène Basique");
    armor.rarity = COMMUN;
    armor.type.type = SUIT;
    strcpy(armor.type.name, "Combinaison");
    armor.minAttack = 0;
    armor.maxAttack = 0;
    armor.quantity = 1;
    armor.defenseBonus = 5;
    armor.oxygenCost = 0;
    strcpy(armor.effect, "");

    // Ajouter les items à l'inventaire
    add_item(inv, trident);
    add_item(inv, armor);

    // Équiper automatiquement le trident et l'armure
    inv->equipedWeapon = inv->objets[0];
    inv->equipedSuit = inv->objets[1];
}

void clean_inventory(Inventory* inv) { free(inv); }

void add_item(Inventory* inv, Item newItem) {
    if (inv == NULL) {
        return;
    }

    // Vérifier si l'inventaire est plein
    if (inv->nb_objets >= 8) {
        return; // Inventaire plein
    }

    // Si c'est un consommable, vérifier s'il existe déjà dans l'inventaire
    if (newItem.type.type == CONSUMABLE) {
        for (int i = 0; i < inv->nb_objets; i++) {
            if (strcmp(inv->objets[i].name, newItem.name) == 0 &&
                inv->objets[i].type.type == CONSUMABLE) {
                // Ajouter la quantité à l'objet existant
                inv->objets[i].quantity += newItem.quantity;
                return;
            }
        }
    }

    // Ajouter le nouvel objet
    inv->objets[inv->nb_objets] = newItem;
    inv->nb_objets++;
}

char* get_item_type(enum type t) {
    switch (t) {
        case CONSUMABLE:
            return "Consommable";
        case WEAPON_CONTACT:
            return "Arme de contact";
        case WEAPON_DISTANCE:
            return "Arme à distance";
        case WEAPON_SPECIAL:
            return "Arme spéciale";
        case HELMET:
            return "Casque";
        case SUIT:
            return "Combinaison";
        case GLOVES:
            return "Gants";
        case BOOTS:
            return "Bottes";
        default:
            return "Inconnu";
    }
}

char* get_item_rarity(enum rarity r) {
    switch (r) {
        case COMMUN:
            return "COMMUN";
        case UNCOMMUN:
            return "PEU COMMUN";
        case RARE:
            return "RARE";
        case EPIC:
            return "ÉPIQUE";
        case LEGENDARY:
            return "LÉGENDAIRE";
        case MYTHIC:
            return "MYTHIQUE";
        default:
            return "INCONNU";
    }
}

Item generate_random_item(int rarity) {
    Item item = {0};

    // Limiter la rareté aux valeurs valides
    if (rarity < 0) rarity = 0;
    if (rarity > 5) rarity = 5;

    item.rarity = (enum rarity)rarity;
    item.quantity = 1;

    // Déterminer le type d'objet aléatoirement
    int itemTypeRoll = random_num(0, 100);

    if (itemTypeRoll < 30) {
        // 30% chance : Consommable
        item.type.type = CONSUMABLE;
        int consumableType = random_num(0, 3);
        switch (consumableType) {
            case 0:
                strcpy(item.name, "Capsule d'oxygène");
                strcpy(item.effect, "boost_oxygene");
                item.quantity = random_num(1, 3);
                break;
            case 1:
                strcpy(item.name, "Trousse de soin");
                strcpy(item.effect, "soin");
                item.quantity = random_num(1, 2);
                break;
            case 2:
                strcpy(item.name, "Stimulant marin");
                strcpy(item.effect, "boost_vitesse");
                item.quantity = random_num(1, 2);
                break;
            case 3:
                strcpy(item.name, "Antidote");
                strcpy(item.effect, "cure_poison");
                item.quantity = 1;
                break;
        }
        item.minAttack = 0;
        item.maxAttack = 0;
        item.defenseBonus = 0;
        item.oxygenCost = 0;
    } else if (itemTypeRoll < 60) {
        // 30% chance : Arme
        int weaponType = random_num(0, 2);
        switch (weaponType) {
            case 0:
                item.type.type = WEAPON_CONTACT;
                strcpy(item.type.name, "Arme de contact");
                break;
            case 1:
                item.type.type = WEAPON_DISTANCE;
                strcpy(item.type.name, "Arme à distance");
                break;
            case 2:
                item.type.type = WEAPON_SPECIAL;
                strcpy(item.type.name, "Arme spéciale");
                break;
        }

        // Index 0 = Trident (arme de contact), Index 1 = Harpon (arme à distance)
        const char* weaponNames[][2] = {
            {"Trident Rouillé", "Harpon Basique"},
            {"Trident Renforcé", "Harpon Acier"},
            {"Trident de Corail", "Harpon Électrique"},
            {"Trident Légendaire", "Harpon Laser"},
            {"Trident Mythique", "Harpon Quantique"},
            {"Trident Ultime", "Harpon Cosmique"}
        };

        // Sélectionner le nom selon le type d'arme
        int nameIndex = 0; // Par défaut Trident (arme de contact)
        if (item.type.type == WEAPON_DISTANCE) {
            nameIndex = 1; // Harpon pour arme à distance
        }
        // Pour WEAPON_SPECIAL, on utilise aussi Trident (index 0)

        strcpy(item.name, weaponNames[rarity][nameIndex]);

        // Stats d'attaque selon la rareté
        int baseMinAttack[] = {10, 15, 25, 35, 45, 60};
        int baseMaxAttack[] = {18, 25, 40, 55, 70, 90};
        int variance = 3 + (rarity * 2);

        item.minAttack = baseMinAttack[rarity] + random_num(-variance, variance);
        item.maxAttack = baseMaxAttack[rarity] + random_num(-variance, variance);
        if (item.minAttack < 1) item.minAttack = 1;
        if (item.maxAttack <= item.minAttack) item.maxAttack = item.minAttack + 1;

        // Coût en oxygène selon la rareté (plus rare = moins de coût)
        item.oxygenCost = random_num(2, 6 - rarity);
        if (item.oxygenCost < 1) item.oxygenCost = 1;

        // Effets spéciaux pour les armes rares
        if (rarity >= RARE) {
            int effectRoll = random_num(0, 3);
            switch (effectRoll) {
                case 0:
                    strcpy(item.effect, "ignore_defense");
                    break;
                case 1:
                    strcpy(item.effect, "electrique");
                    break;
                case 2:
                    strcpy(item.effect, "poison");
                    break;
                case 3:
                    strcpy(item.effect, "critique");
                    break;
            }
        } else {
            strcpy(item.effect, "");
        }

        item.defenseBonus = 0;
    } else {
        // 40% chance : Armure
        int armorType = random_num(0, 3);
        switch (armorType) {
            case 0:
                item.type.type = HELMET;
                strcpy(item.type.name, "Casque");
                break;
            case 1:
                item.type.type = SUIT;
                strcpy(item.type.name, "Combinaison");
                break;
            case 2:
                item.type.type = GLOVES;
                strcpy(item.type.name, "Gants");
                break;
            case 3:
                item.type.type = BOOTS;
                strcpy(item.type.name, "Bottes");
                break;
        }

        // Générer le nom selon la rareté et le type
        const char* armorPrefixes[] = {"Basique", "Renforcé", "Abyssal", "Légendaire", "Mythique", "Divin"};
        const char* armorNames[] = {"Néoprène", "Acier", "Titanium", "Cristal", "Éther", "Cosmique"};
        char armorName[100];
        snprintf(armorName, sizeof(armorName), "%s %s", armorNames[rarity], get_item_type(item.type.type));
        strcpy(item.name, armorName);

        // Bonus de défense selon la rareté
        int baseDefense[] = {3, 7, 12, 18, 25, 35};
        int variance = 2 + rarity;
        item.defenseBonus = baseDefense[rarity] + random_num(-variance, variance);
        if (item.defenseBonus < 1) item.defenseBonus = 1;

        item.minAttack = 0;
        item.maxAttack = 0;
        item.oxygenCost = 0;

        // Effets spéciaux pour les armures rares
        if (rarity >= RARE) {
            int effectRoll = random_num(0, 2);
            switch (effectRoll) {
                case 0:
                    strcpy(item.effect, "boost_defense");
                    break;
                case 1:
                    strcpy(item.effect, "resistance");
                    break;
                case 2:
                    strcpy(item.effect, "regeneration");
                    break;
            }
        } else {
            strcpy(item.effect, "");
        }
    }

    return item;
}

void display_inventory(Inventory* inv) {
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║                        🧰 INVENTAIRE 🤿                           ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                  ║\n");

    // Affichage des équipements portés
    printf("║  🛡️  ÉQUIPEMENT PORTÉ :                                          ║\n");
    printf("║                                                                  ║\n");

    if (inv && inv->equipedWeapon.name[0] != '\0') {
        printf("║  ⚔️  Arme : %-50s ║\n", inv->equipedWeapon.name);
    } else {
        printf("║  ⚔️  Arme : Aucune                                            ║\n");
    }

    if (inv && inv->equipedHelmet.name[0] != '\0') {
        printf("║  🪖 Casque : %-48s ║\n", inv->equipedHelmet.name);
    } else {
        printf("║  🪖 Casque : Aucun                                            ║\n");
    }

    if (inv && inv->equipedSuit.name[0] != '\0') {
        printf("║  🦺 Combinaison : %-44s ║\n", inv->equipedSuit.name);
    } else {
        printf("║  🦺 Combinaison : Aucune                                       ║\n");
    }

    if (inv && inv->equipedGloves.name[0] != '\0') {
        printf("║  🧤 Gants : %-50s ║\n", inv->equipedGloves.name);
    } else {
        printf("║  🧤 Gants : Aucuns                                            ║\n");
    }

    if (inv && inv->equipedBoots.name[0] != '\0') {
        printf("║  👢 Bottes : %-49s ║\n", inv->equipedBoots.name);
    } else {
        printf("║  👢 Bottes : Aucunes                                          ║\n");
    }

    printf("║                                                                  ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                  ║\n");
    printf("║  📦 OBJETS EN POSSESSION :                                       ║\n");
    printf("║                                                                  ║\n");
    if (inv && inv->nb_objets > 0) {
        for (int i = 0; i < inv->nb_objets && i < 8; i++) {
            char itemLine[122];
            snprintf(
                itemLine, sizeof(itemLine), "  [%d] %s (x%d)",
                i + 1, inv->objets[i].name, inv->objets[i].quantity);
            printf("║ %-64s ║\n", itemLine);
        }
    } else {
        printf("║  Inventaire vide...                                            ║\n");
    }

    printf("║                                                                  ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║  💡 Utilisez les numéros pour équiper ou consommer des objets    ║\n");
    printf("║  🔙 Appuyez sur [x] pour retourner au menu principal             ║\n");
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
    printf("> ");
}
