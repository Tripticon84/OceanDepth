
#include "save.h"
#include <windows.h>

#include "../display_combat/display_combat.h"
#include "../utils/utils.h"
#include "../game/game.h"


int save_game(int slot, int depth, const char* zone) {
    char filePath[50];
    snprintf(filePath, sizeof(filePath), "save_slot_%d.dat", slot);
    FILE* file = fopen(filePath, "wb");
    if (file == NULL) {
        return -1; // Erreur lors de l'ouverture du fichier
    }
    fwrite(player, sizeof(Diver), 1, file);
    fwrite(&depth, sizeof(int), 1, file);
    fwrite(zone, sizeof(char) * 50, 1, file);
    fwrite(&monstersCount, sizeof(int), 1, file);
    fwrite(monsters, sizeof(Monster), *monstersCount, file);

    fclose(file);
    return 0; // Succès
}

int load_game(int slot, int* depth, char* zone) {
    char filePath[50];
    snprintf(filePath, sizeof(filePath), "save_slot_%d.dat", slot);
    FILE* file = fopen(filePath, "rb");
    if (file == NULL) {
        return -1; // Erreur lors de l'ouverture du fichier
    }

    fread(player, sizeof(Diver), 1, file);
    fread(depth, sizeof(int), 1, file);
    fread(zone, sizeof(char) * 50, 1, file);
    fread(monstersCount, sizeof(int), 1, file);
    fread(monsters, sizeof(Monster), *monstersCount, file);

    fclose(file);
    return 0;
}

int is_slot_used(int slot) {
    char filePath[50];
    snprintf(filePath, sizeof(filePath), "save_slot_%d.dat", slot);
    FILE* file = fopen(filePath, "rb");
    if (file == NULL) {
        return 0; // Slot non utilisé
    }
    fclose(file);
    return 1; // Slot utilisé
}

void get_saves_infos(int slot) {
    char filePath[50];
    snprintf(filePath, sizeof(filePath), "save_slot_%d.dat", slot);
    FILE* file = fopen(filePath, "rb");
    if (file == NULL) {
        printf("Slot %d : Vide", slot);
        print_chars(" ", INNER_WIDTH - 30);
        printf("║\n");
        return;
    }

    Diver player;
    Inventory inv;
    int depth;
    char zone[50];
    int monstersCount;

    fread(&player, sizeof(Diver), 1, file);
    // fread(&inv, sizeof(Inventory), 1, file);
    fread(&depth, sizeof(int), 1, file);
    fread(zone, sizeof(char) * 50, 1, file);
    fread(&monstersCount, sizeof(int), 1, file);

    printf("Slot %d :", slot);
    print_chars(" ", INNER_WIDTH - 25);
    printf("║\n");

    printf("║   Profondeur : %dm", depth);
    print_chars(" ", INNER_WIDTH - calculate_number_width(depth) - 29);
    printf("║\n");

    printf("║   Zone : %s", zone);
    print_chars(" ", INNER_WIDTH - calculate_text_width(zone) - 22);
    printf("║\n");

    printf("║   Santé : %d/%d", player.health, player.maxHealth);
    print_chars(" ", INNER_WIDTH - calculate_number_width(player.health) - calculate_number_width(player.maxHealth) - 24);
    printf("║\n");

    printf("║   Oxygène : %d/%d", player.oxygen, player.maxOxygen);
    print_chars(" ", INNER_WIDTH - calculate_number_width(player.oxygen) - calculate_number_width(player.maxOxygen) - 26);
    printf("║\n");

    printf("║   Perles : %d", player.pearls);
    print_chars(" ", INNER_WIDTH - calculate_number_width(player.pearls) - 24);
    printf("║\n");

    fclose(file);
}

void display_saves_menu(void) {
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║                          ⚙️ SAUVEGARDES                          ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                  ║\n");
    for (int i = 1; i < 4; i++) {
        printf("║ [%d] ", i);
        get_saves_infos(i);
        printf("║");
        print_chars(" ", INNER_WIDTH - 12);
        printf("║\n");
    }

    printf("║ ");
    printf("[R] Retour au menu principal");
    print_chars(" ", INNER_WIDTH - 41);
    printf("║\n");

    printf("║                                                                  ║\n");

    printf("╚");
    print_chars("═", INNER_WIDTH - 12);
    printf("╝\n");
    printf("> ");
}

void handle_load_save_menu_input(void) {
    char input = getchar();
    switch (input) {
        case '1':
        case '2':
        case '3': {
            int slot = input - '0';

            // Charger la partie depuis le slot choisi
            Diver player;
            Inventory inv;
            int depth;
            char zone[50];
            Monster monsters[10]; // Supposons un maximum de 10 monstres
            int monstersCount;

            if (load_game(slot, &depth, zone) == 0) {
                // Succès du chargement
                currentGameState = GAME_STATE_PLAYING;
            } else {
                // Échec du chargement
                printf("Erreur lors du chargement de la sauvegarde %d.\n", slot);
                sleep_ms(1000);
            }
            break;
        }
        case 'R':
        case 'r':
        case 'q':
        case 'Q':
            // Retour au menu principal
            currentGameState = GAME_STATE_MENU;
            break;
        default:
            printf("Entrée invalide. Veuillez réessayer.");
            // sleep_ms(1000);
            break;
    }
}

void handle_create_save_menu_input(void) {
    char input = getchar();
    switch (input) {
        case '1':
        case '2':
        case '3': {
            int slot = input - '0';

            if (is_slot_used(slot)) {
                printf("Slot %d déjà utilisé. Écraser ? (y/N) ", slot);
                int confirm = getchar();
                while (confirm == '\n') confirm = getchar();
                if (confirm != 'y' && confirm != 'Y') {
                    printf("Opération annulée.\n");
                    sleep_ms(1000);
                    break;
                }
            }

            // Sauvegarder la partie dans le slot choisi
            int depth = 0;
            const char* zone = "Corail Bleu";

            if (save_game(slot, depth, zone) == 0) {
                // Succès de la sauvegarde
                printf("Sauvegarde %d créée avec succès.\n", slot);
                sleep_ms(1000);
            } else {
                // Échec de la sauvegarde
                printf("Erreur lors de la création de la sauvegarde %d.\n", slot);
                sleep_ms(1000);
            }
            break;
        }
        case 'q':
        case 'Q':
        case 'r':
        case 'R':
            // Retour au menu principal
            currentGameState = GAME_STATE_MENU;
            break;
        default:
            printf("Entrée invalide. Veuillez réessayer.");
            // sleep_ms(1000);
            break;
    }
}
