#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <conio.h>
#endif

#include "../game/game.h"
#include "../utils/utils.h"
#include "../shop/shop.h"
#include "../combat/combat.h"
#include "../rewards/rewards.h"

static int read_input_key_map(void) {
#ifdef _WIN32
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        int arrow = _getch();
        switch (arrow) {
            case 72:
                return 1000; // up
            case 80:
                return 1001; // down
            case 75:
                return 1002; // left
            case 77:
                return 1003; // right
            default:
                return 0;
        }
    }
    if (ch == '\r') return '\n';
    return ch;
#else
    int ch = getchar();
    if (ch == '\033') {
        int next = getchar();
        if (next == '[') {
            int arrow = getchar();
            switch (arrow) {
                case 'A':
                    return 1000;
                case 'B':
                    return 1001;
                case 'D':
                    return 1002;
                case 'C':
                    return 1003;
                default:
                    return 0;
            }
        }
    }
    return ch;
#endif
}

const ZoneType ZONE_TYPE[7] = {
    [SURFACE] = {.icon = "🌊", .name = "Ocean", .description = "Eaux calmes en surface"},
    [REEF] = {.icon = "🪸", .name = "Recif Coralien", .description = "Un recif vibrant de vie marine"},
    [WRECK] = {.icon = "🚢", .name = "Epave", .description = "Les restes d'un navire coule"},
    [ALGAE_FOREST] = {.icon = "🌿", .name = "Foret d'algues", .description = "Dense vegetation sous-marine"},
    [CAVE] = {.icon = "🕳️", .name = "Grotte", .description = "Une cavite sombre et mysterieuse"},
    [SHOP] = {.icon = "⛵", .name = "Magasin", .description = "Magasin du bateau"},
    [EMPTY] = {.icon = "❌", .name = "Vide", .description = "Rien à signaler"}
};

void first_init_zone() {
    gameMap.numZones = 0;
    gameMap.zones[0].depth = 0;

    CaseZone* base = &gameMap.zones[0].cases[0];
    strcpy(base->icon, "🏝️");
    strcpy(base->name, "Base");
    base->type = SURFACE;
    strcpy(base->description, "Zone de depart securisee");
    base->minMonsterCount = 0;
    base->maxMonsterCount = 0;
    base->isDiscovered = true;
    base->hasBeenDefeated = true;

    CaseZone* ocean1 = &gameMap.zones[0].cases[1];
    strcpy(ocean1->icon, "🌊");
    strcpy(ocean1->name, "Ocean");
    ocean1->type = SURFACE;
    strcpy(ocean1->description, "Eaux calmes en surface");
    ocean1->minMonsterCount = 0;
    ocean1->maxMonsterCount = 0;
    ocean1->isDiscovered = true;
    ocean1->hasBeenDefeated = true;

    CaseZone* ocean2 = &gameMap.zones[0].cases[2];
    strcpy(ocean2->icon, "🌊");
    strcpy(ocean2->name, "Ocean");
    ocean2->type = SURFACE;
    strcpy(ocean2->description, "Eaux calmes en surface");
    ocean2->minMonsterCount = 0;
    ocean2->maxMonsterCount = 0;
    ocean2->isDiscovered = true;
    ocean2->hasBeenDefeated = true;

    CaseZone* boat = &gameMap.zones[0].cases[3];
    strcpy(boat->icon, "⛵");
    strcpy(boat->name, "Bateau");
    boat->type = SHOP;
    strcpy(boat->description, "Magasin du bateau");
    boat->minMonsterCount = 0;
    boat->maxMonsterCount = 0;
    boat->isDiscovered = true;
    boat->hasBeenDefeated = true;

    player->zoneIndex = 0;
    player->caseIndex = 0;
}

void init_next_zone() {
    gameMap.numZones++;
    // gameMap.zones = realloc(gameMap.zones, sizeof(Zone) * (gameMap.numZones + 1));
    // if (gameMap.zones == NULL) {
    //     fprintf(stderr, "Erreur d'allocation de la carte\n");
    //     exit(-10);
    // }
    // int newDepth = gameMap.zones[gameMap.numZones - 1].depth + 50;
    // Zone* newZone = &gameMap.zones[gameMap.numZones];
    // newZone->depth = newDepth;

    Zone* temp = realloc(gameMap.zones, sizeof(Zone) * (gameMap.numZones + 1));
    if (temp == NULL) {
        fprintf(stderr, "Erreur d'allocation de la carte\n");
        gameMap.numZones--;
        return;
    }
    gameMap.zones = temp;
    int newDepth = gameMap.zones[gameMap.numZones - 1].depth + 50;

    Zone* newZone = &gameMap.zones[gameMap.numZones];
    newZone->depth = newDepth;


    bool needShop = newDepth % 200 == 0 ? true : false;
    int numAvailableTypes = 5; // inclut EMPTY
    ZoneKind availableTypes[] = {REEF, WRECK, ALGAE_FOREST, CAVE, EMPTY};
    ZoneKind availableNonCaveTypes[] = {REEF, WRECK, ALGAE_FOREST, EMPTY};

    int prevCaveIdx1 = -1;
    for (int zoneIndex = 1; zoneIndex <= 2; zoneIndex++) {
        if (gameMap.numZones >= zoneIndex) {
            Zone* prevZone = &gameMap.zones[gameMap.numZones - zoneIndex];
            for (int k = 0; k < 4; k++) {
                if (prevZone->cases[k].type == CAVE) {
                    if (zoneIndex == 1) prevCaveIdx1 = k;
                    break;
                }
            }
        }
    }
    bool cavePlaced = prevCaveIdx1 != -1 ? true : false;
    bool shopPlaced = false;
    for (int i = 0; i < 4; i++) {
        CaseZone* caseZone = &newZone->cases[i];
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
        ZoneKind selectedType = availableTypes[random_num(0, numAvailableTypes - 1)];
        bool allowCaveInZone = !cavePlaced;
        if (selectedType == CAVE && !allowCaveInZone) {
            selectedType = availableNonCaveTypes[random_num(0, 3)];
        }
        if (selectedType == CAVE) cavePlaced = true;
        caseZone->type = selectedType;
        strcpy(caseZone->icon, ZONE_TYPE[selectedType].icon);
        strcpy(caseZone->name, ZONE_TYPE[selectedType].name);
        strcpy(caseZone->description, ZONE_TYPE[selectedType].description);
        if (selectedType == SHOP || selectedType == CAVE || selectedType == EMPTY) {
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

bool is_case_zone_visible(int zoneIndex, int caseIndex) {
    int zoneStart = zoneIndex - 1 >= 0 ? zoneIndex - 1 : 0;
    int zoneEnd = zoneIndex + 1 >= gameMap.numZones ? gameMap.numZones : zoneIndex + 1;
    for (int z = zoneStart; z <= zoneEnd; z++) {
        for (int c = 0; c < 4; c++) {
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
        case EMPTY:
            return "Vide";
        default:
            return "Inconnu";
    }
}

int map_get_selected_depth(void) {
    if (player->zoneIndex < 0) player->zoneIndex = 0;
    if (player->zoneIndex > gameMap.numZones) player->zoneIndex = gameMap.numZones;
    return gameMap.zones[player->zoneIndex].depth;
}

void handle_map_input(void) {
    int key = read_input_key_map();
    if (key == 0) return;

    if (key == 'x' || key == 'X') {
        currentGameState = GAME_STATE_MENU;
        return;
    }

    CaseZone* cz = &gameMap.zones[player->zoneIndex].cases[player->caseIndex];
    if (key == 'e' || key == 'E' || key == '\n') {
        if (!cz->isDiscovered && !is_case_zone_visible(player->zoneIndex, player->caseIndex)) {
            return;
        }
        cz->isDiscovered = true;
        // Mettre à jour la profondeur globale
        depth = gameMap.zones[player->zoneIndex].depth;
        if (cz->type == SHOP) {
            player->oxygen += player->oxygen + 30 > player->maxOxygen ? player->maxOxygen - player->oxygen : 30;
            currentGameState = GAME_STATE_SHOP;
            return;
        }
        // Zone vide: rien à explorer
        if (cz->type == EMPTY) {
            return;
        }
        // Zone sûre: donner une récompense simple (20 perles)
        if (cz->type == CAVE || cz->type == SURFACE) {
            add_pearls_to_player(player, 20);
            display_reward_pearls(20);
            return;
        }
        if (cz->type != EMPTY && cz->type != SURFACE) {
            // // Ajuster le nombre de monstres au min/max de la case
            // int desired = cz->minMonsterCount;
            // if (cz->maxMonsterCount > cz->minMonsterCount) {
            //     desired = random_num(cz->minMonsterCount, cz->maxMonsterCount);
            // }
            // if (desired < 1) desired = 1;
            // if (desired > 4) desired = 4;
            // Générer les monstres pour ce combat à la profondeur courante
            // generate_monsters_in_zone(monsters, depth, monstersCount);
            // Compléter ou réduire pour correspondre au "desired"
            // if (*monstersCount < desired) {
            //     for (int i = *monstersCount; i < desired; ++i) {
            //         int type = (depth <= 50) ? random_num(1, 3) : ((depth <= 150) ? random_num(1, 4) : random_num(0, 4));
            //         init_monster(monsters[i], type, i + 1);
            //     }
            // }
            // if (desired < *monstersCount) {
            //     // Rien à faire: on tronque simplement en mettant le compteur cible
            // }
            // *monstersCount = desired;
            if (!cz->hasBeenDefeated) {
                currentGameState = GAME_STATE_COMBAT;
            }
        }
        // Débloquer la zone suivante si on est sur la dernière connue
        if (player->zoneIndex == gameMap.numZones) {
            init_next_zone();
        }
        return;
    }

    if (key == 'r' || key == 'R') {
        player->zoneIndex = 0;
        player->caseIndex = 0;
        return;
    }

    if (key == 'i' || key == 'I') {
        currentGameState = GAME_STATE_INVENTORY;
        return;
    }

    if (key == 's' || key == 'S') {
        if (player->zoneIndex == 0 && player->caseIndex == 0 || cz->type == CAVE) {
            currentGameState = GAME_STATE_SAVE_MENU_CREATE;
        }
        return;
    }

    int newZone = player->zoneIndex;
    int newCase = player->caseIndex;

    switch (key) {
        case 'z':
        case 'Z':
        case 1000:
            if (player->zoneIndex > 0) {
                newZone = player->zoneIndex - 1;
                // newCase = 0;
            }
            break;
        case 1001:
            if (player->zoneIndex < gameMap.numZones) {
                newZone = player->zoneIndex + 1;
                // newCase = 0;
            }
            break;
        case 'q':
        case 'Q':
        case 1002:
            if (player->caseIndex > 0) newCase = player->caseIndex - 1;
            break;
        case 'd':
        case 'D':
        case 1003:
            if (player->caseIndex < 3) newCase = player->caseIndex + 1;
            break;
        default:
            return;
    }

    if (is_case_zone_visible(newZone, newCase) || gameMap.zones[newZone].cases[newCase].isDiscovered) {
        // Consomme de l'oxygène lorsqu'on descend d'une zone (coût croissant avec la profondeur)
        if (newZone > player->zoneIndex) {
            int newDepthMeters = gameMap.zones[newZone].depth;
            int cost = 4 + 3 * (newDepthMeters / 100); // Base 10, +5 par palier de 100 m
            consume_oxygen(cost);
            // if (player->oxygen <= 0) {
            //     currentGameState = GAME_STATE_GAME_OVER;
            //     return;
            // }
        }
        player->zoneIndex = newZone;
        player->caseIndex = newCase;
    }
}
