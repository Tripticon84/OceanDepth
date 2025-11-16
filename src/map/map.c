#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../game/game.h"
#include "../utils/utils.h"

const ZoneType ZONE_TYPE[6] = {
    [SURFACE] = {.icon = "🌊", .name = "Ocean", .description = "Eaux calmes en surface"},
    [REEF] = {.icon = "🪸", .name = "Recif", .description = "Un recif vibrant de vie marine"},
    [WRECK] = {.icon = "🚢", .name = "Epave", .description = "Les restes d'un navire coule"},
    [ALGAE_FOREST] = {.icon = "🌿", .name = "Foret d'algues", .description = "Dense vegetation sous-marine"},
    [CAVE] = {.icon = "🕳️", .name = "Grotte", .description = "Une cavite sombre et mysterieuse"},
    [SHOP] = {.icon = "⛵", .name = "Magasin", .description = "Magasin du bateau"}
};

void first_init_zone() {
    gameMap.numZones = 0;

    Zone* surfaceZone = &gameMap.zones[0];
    surfaceZone->depth = 0; // 0m

    // Case 0: Base [SAUF]
    CaseZone* base = &surfaceZone->cases[0];
    strcpy(base->icon, "🏝️");
    strcpy(base->name, "Base");
    base->type = SURFACE;
    strcpy(base->description, "Zone de depart securisee");
    base->minMonsterCount = 0;
    base->maxMonsterCount = 0;
    base->isDiscovered = true;
    base->hasBeenDefeated = true;

    // Case 1: Ocean
    CaseZone* ocean1 = &surfaceZone->cases[1];
    strcpy(ocean1->icon, "🌊");
    strcpy(ocean1->name, "Ocean");
    ocean1->type = SURFACE;
    strcpy(ocean1->description, "Eaux calmes en surface");
    ocean1->minMonsterCount = 0;
    ocean1->maxMonsterCount = 0;
    ocean1->isDiscovered = true;
    ocean1->hasBeenDefeated = false;

    // Case 2: Ocean
    CaseZone* ocean2 = &surfaceZone->cases[2];
    strcpy(ocean2->icon, "🌊");
    strcpy(ocean2->name, "Ocean");
    ocean2->type = SURFACE;
    strcpy(ocean2->description, "Eaux calmes en surface");
    ocean2->minMonsterCount = 0;
    ocean2->maxMonsterCount = 0;
    ocean2->isDiscovered = true;
    ocean2->hasBeenDefeated = false;

    // Case 3: Bateau [SHOP]
    CaseZone* boat = &surfaceZone->cases[3];
    strcpy(boat->icon, "⛵");
    strcpy(boat->name, "Bateau");
    boat->type = SHOP;
    strcpy(boat->description, "Magasin du bateau");
    boat->minMonsterCount = 0;
    boat->maxMonsterCount = 0;
    boat->isDiscovered = true;
    boat->hasBeenDefeated = false;
}

void init_next_zone() {
    gameMap.numZones++;

    gameMap.zones = realloc(gameMap.zones, sizeof(Zone) * (gameMap.numZones + 1));
    if (gameMap.zones == NULL) {
        fprintf(stderr, "Erreur d\'allocation de la carte\n");
        exit(-10);
    }

    int newDepth = gameMap.zones[gameMap.numZones - 1].depth + 50;

    Zone* newZone = &gameMap.zones[gameMap.numZones];
    newZone->depth = newDepth;

    // Vérification shop tous les 200m
    bool needShop = newDepth % 200 == 0 ? true : false;

    // Types de zones disponibles (exclure SURFACE et SHOP)
    int numAvailableTypes = 4;
    ZoneKind availableTypes[] = {REEF, WRECK, ALGAE_FOREST, CAVE};
    ZoneKind availableNonCaveTypes[] = {REEF, WRECK, ALGAE_FOREST};

    // Trouver l'index de la grotte dans les deux zones précédentes (s'il en existe)
    int prevCaveIdx1 = -1; // zone juste au-dessus
    int prevCaveIdx2 = -1; // deux zones au-dessus
    for (int zoneIndex = 1; zoneIndex <= 2; zoneIndex++) {
        if (gameMap.numZones >= zoneIndex) {
            Zone* prevZone = &gameMap.zones[gameMap.numZones - zoneIndex];
            for (int k = 0; k < 4; k++) {
                if (prevZone->cases[k].type == CAVE) {
                    if (zoneIndex == 1) prevCaveIdx1 = k;
                    else prevCaveIdx2 = k;
                    break;
                }
            }
        }
    }
    bool cavePlaced = prevCaveIdx1 != -1 ? true : false; // 1 zone au-dessus
    // bool cavePlaced = prevCaveIdx1 != -1 || prevCaveIdx2 != -1 ? true : false; // 2 zones au-dessus
    bool shopPlaced = false;
    for (int i = 0; i < 4; i++) {
        CaseZone* caseZone = &newZone->cases[i];

        // Si on doit placer un shop et qu'il n'est pas encore placé, on le place ici
        if (needShop && !shopPlaced) {
            caseZone->type = SHOP;
            strcpy(caseZone->icon, ZONE_TYPE[SHOP].icon);
            strcpy(caseZone->name, ZONE_TYPE[SHOP].name);
            strcpy(caseZone->description, ZONE_TYPE[SHOP].description);
            caseZone->minMonsterCount = 0;
            caseZone->maxMonsterCount = 0;
            caseZone->isDiscovered = false;
            shopPlaced = true;
            continue;
        }

        // Sélectionner un type aléatoire
        ZoneKind selectedType = availableTypes[random(0, numAvailableTypes - 1)];

        // Vérifie si une grotte peut être placée à cet emplacement
        bool allowCaveInZone = !cavePlaced;

        // Si on a tiré une grotte mais qu'elle n'est pas autorisée ici, retomber sur un type non-grotte
        if (selectedType == CAVE && allowCaveInZone == false) {
            selectedType = availableNonCaveTypes[random(0, numAvailableTypes - 2)];
        }

        // Si on prend une grotte et qu'elle est autorisée, marquer qu'on a placé la grotte
        if (selectedType == CAVE) {
            cavePlaced = true;
        }

        caseZone->type = selectedType;

        strcpy(caseZone->icon, ZONE_TYPE[selectedType].icon);
        strcpy(caseZone->name, ZONE_TYPE[selectedType].name);
        strcpy(caseZone->description, ZONE_TYPE[selectedType].description);

        if (selectedType == SHOP || selectedType == CAVE) {
            caseZone->minMonsterCount = 0;
            caseZone->maxMonsterCount = 0;
        } else {
            if (newDepth <= 100) {
                caseZone->minMonsterCount = 1;
                caseZone->maxMonsterCount = 1;
            } else if (newDepth <= 200) {
                caseZone->minMonsterCount = 1;
                caseZone->maxMonsterCount = 2;
            } else if (newDepth <= 500) {
                caseZone->minMonsterCount = 2;
                caseZone->maxMonsterCount = 3;
            } else {
                caseZone->minMonsterCount = 3;
                caseZone->maxMonsterCount = 4;
            }
        }
        caseZone->hasBeenDefeated = false;
        caseZone->isDiscovered = false;
    }
}

void print_map() {
    printf("=== MAP DEBUG ===\n");
    printf("Nombre total de zones: %d\n\n", gameMap.numZones);

    for (int i = 0; i < gameMap.numZones + 1; i++) {
        printf("--- Zone de profondeur %d ---\n\n", gameMap.zones[i].depth);
        for (int j = 0; j < 4; j++) {
            CaseZone zone = gameMap.zones[i].cases[j];

            printf("  [%s] %s\n", zone.icon, zone.name);
            printf("    Type: %s\n", get_zone_type_name(zone.type));
            printf("    Description: %s\n", zone.description);
            printf("    Monstres: %d-%d\n", zone.minMonsterCount, zone.maxMonsterCount);
            printf("    Decouverte: %s\n", zone.isDiscovered ? "Oui" : "Non");
            printf("\n");
        }
    }

    printf("=================\n");
}

// bool can_access_zone(CaseZone* caseZone) {
//     // Vérifie si la zone est une grotte
//     if (caseZone->type == CAVE) {}
//     // Autorise l'accès si le joueur a une lampe torche
//     if (has_item(player->inventory, ITEM_TORCH)) {
//         return true;
//     } else {
//         return false;
//     }
// }

bool is_case_zone_visible(int zoneIndex, int caseIndex) {
    // Vérifier qu'une case voisine a été découverte
    int zoneStart = zoneIndex - 1 >= 0 ? zoneIndex - 1 : 0;
    int zoneEnd = zoneIndex + 1 >= gameMap.numZones ? gameMap.numZones : zoneIndex + 1;
    for (int z = zoneStart; z <= zoneEnd; z++) {
        for (int c = 0; c < 4; c++) {
            // Sauter la case actuelle
            if (z == zoneIndex && c == caseIndex) continue;

            CaseZone* neighborCase = &gameMap.zones[z].cases[c];
            if (neighborCase->isDiscovered) {
                return true;
            }
        }
    }
    return false;
}


const char* get_zone_type_name(ZoneKind type) {
    switch (type) {
        case SURFACE:
            return "Surface";
        case REEF:
            return "Recif";
        case WRECK:
            return "Epave";
        case ALGAE_FOREST:
            return "Forêt d'algues";
        case CAVE:
            return "Grotte";
        case SHOP:
            return "Magasin";
        default:
            return "Inconnu";
    }
}

void handle_map_input() {
    char input = getchar();
    switch (input) {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            clear_terminal();
            break;
        default:
            break;
    }
}
