#include "display_map.h"

#include <stdio.h>
#include <string.h>

#include "../game/game.h"
#include "../utils/utils.h"

void display_map() {
    // En-tête
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║");
    print_centered("🗺️ CARTOGRAPHIE OCÉANIQUE", 84);
    printf("║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                              ║\n");

    // Coordonnées X
    printf("║   X→       1            2            3            4            5             ║\n");
    printf("║  Y↓ ┌────────────┬────────────┬────────────┬────────────┬────────────┐       ║\n");

    // Afficher chaque zone (ligne)
    for (int zoneIdx = 0; zoneIdx <= gameMap.numZones + 1; zoneIdx++) {
        bool isUnknownRow = (zoneIdx == gameMap.numZones + 1);
        Zone* zone = (!isUnknownRow && zoneIdx <= gameMap.numZones) ? &gameMap.zones[zoneIdx] : NULL;
        int depthVal = (zone ? zone->depth : gameMap.zones[gameMap.numZones].depth + 50);

        // Ligne 1 : Icônes et nom de zone
        printf("║     │");
        for (int caseIdx = 0; caseIdx < 4; caseIdx++) {
            if (isUnknownRow) {
                printf("     ❓     │");
                continue;
            }
            CaseZone* caseZone = &zone->cases[caseIdx];
            if (is_case_zone_visible(zoneIdx, caseIdx)) {
                if (player->zoneIndex == zoneIdx && player->caseIndex == caseIdx)
                    printf("     🤿     │");
                else
                    printf("     %s     │", caseZone->icon);
            } else {
                printf("     ❓     │");
            }
        }
        print_chars(" ", 12);
        printf("│       ║\n");

        // Ligne 2 : Noms
        printf("║");
        print_chars(" ", 4 - calculate_number_width(zoneIdx + 1));
        printf("%d │", zoneIdx + 1);

        for (int caseIdx = 0; caseIdx < 4; caseIdx++) {
            if (isUnknownRow) {
                printf("  Inconnu   │");
                continue;
            }
            CaseZone* caseZone = &zone->cases[caseIdx];
            if (is_case_zone_visible(zoneIdx, caseIdx)) {
                print_centered(caseZone->name, 12);
                printf("│");
            } else {
                printf("  Inconnu   │");
            }
        }
        printf(" ZONE %d", zoneIdx + 1);
        print_chars(" ", 6 - calculate_number_width(zoneIdx + 1));

        printf("│ %dm", -depthVal);
        print_chars(" ", 5 - calculate_number_width(-depthVal));
        printf("║\n");

        // Ligne 3 : Informations (ennemis, type)
        printf("║     │");
        for (int caseIdx = 0; caseIdx < 4; caseIdx++) {
            if (isUnknownRow) {
                printf("            │");
                continue;
            }
            CaseZone* caseZone = &zone->cases[caseIdx];
            if (is_case_zone_visible(zoneIdx, caseIdx)) {
                if (caseZone->type == SHOP) {
                    printf("   [SHOP]   │");
                } else if (caseZone->type == CAVE) {
                    printf("   [SAUF]   │");
                } else if (caseZone->type == EMPTY) {
                    // Ne pas réimprimer l'icône ❌ ici pour éviter le doublon, laisser vide
                    printf("            │");
                } else if (caseZone->hasBeenDefeated == true) {
                    printf("   [BATTU]  │");
                } else if (caseZone->maxMonsterCount > 0) {
                    if (caseZone->minMonsterCount == caseZone->maxMonsterCount) {
                        printf("  [%d ENM]   │", caseZone->maxMonsterCount);
                    } else {
                        printf("  [%d-%d ENM] │", caseZone->minMonsterCount, caseZone->maxMonsterCount);
                    }
                } else {
                    printf("            │");
                }
            } else {
                printf("            │");
            }
        }
        printf("            │       ║\n");

        // Séparateur ou fin
        if (!isUnknownRow) {
            printf("║     ├────────────┼────────────┼────────────┼────────────┼────────────┤       ║\n");
        } else {
            printf("║     └────────────┴────────────┴────────────┴────────────┴────────────┘       ║\n");
        }
    }

    printf("║                                                                              ║\n");
    // Barre Santé/Oxygène centrée
    printf("║");
    char statusLine[84];
    snprintf(
        statusLine, sizeof(statusLine), "💧 Santé: %d/%d  💨 Oxygène: %d/%d  💎 Perles: %d",
        player->health, player->maxHealth, player->oxygen, player->maxOxygen, player->pearls);
    print_centered(statusLine, 84);
    printf(" ║\n");

    printf("╠══════════════════════════════════════════════════════════════════════════════╣\n");

    printf("║                                                                              ║\n");

    // Position actuelle du joueur
    CaseZone* currentCase = &gameMap.zones[player->zoneIndex].cases[player->caseIndex];
    printf(
        "║  Position actuelle : [%-4s] X%d-Y%d %s (%dm)",
        currentCase->icon,
        player->caseIndex + 1, player->zoneIndex + 1,
        currentCase->name,
        -gameMap.zones[player->zoneIndex].depth);
    print_chars(
        " ", 46
        - calculate_text_width(currentCase->icon)
        - calculate_number_width(player->caseIndex + 1)
        - calculate_number_width(player->zoneIndex + 1)
        - calculate_text_width(currentCase->name)
        - calculate_number_width(gameMap.zones[player->zoneIndex].depth)
    );
    printf("║\n");

    printf("║                                                                              ║\n");

    // Menu // TODO : ACTION DYNAMIQUE en fonction de la case
    printf("╠══════════════════════════════════════════════════════════════════════════════╣\n");
    if (player->zoneIndex == 0 && player->caseIndex == 0) {
        printf("║  E-Explorer  R-Retour surface  I-Inventaire  S-Sauvegarder  X-Retour menu    ║\n");
    } else {
        printf("║  E-Explorer  R-Retour surface  I-Inventaire  X-Retour menu                   ║\n");
    }
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
}
