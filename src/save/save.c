
#include "save.h"

#include "../display_combat/display_combat.h"
#include "../utils/utils.h"


int save_game(int slot, Diver* player, Inventory* inv, int depth, const char* zone, Monster monsters[], int monstersCount) {
    char filePath[50];
    snprintf(filePath, sizeof(filePath), "save_slot_%d.dat", slot);
    FILE* file = fopen(filePath, "wb");
    if (file == NULL) {
        return -1; // Erreur lors de l'ouverture du fichier
    }
    fwrite(player, sizeof(Diver), 1, file);
    // fwrite(inv, sizeof(Inventory), 1, file);
    fwrite(&depth, sizeof(int), 1, file);
    fwrite(zone, sizeof(char) * 50, 1, file); // Supposons que la zone a une taille maximale de 50 caractères
    fwrite(&monstersCount, sizeof(int), 1, file);
    fwrite(monsters, sizeof(Monster), monstersCount, file);

    fclose(file);
    return 0; // Succès
}

int load_game(int slot, Diver* player, Inventory* inv, int* depth, char* zone, Monster monsters[], int* monstersCount) {
    char filePath[50];
    snprintf(filePath, sizeof(filePath), "save_slot_%d.dat", slot);
    FILE* file = fopen(filePath, "rb");
    if (file == NULL) {
        return -1; // Erreur lors de l'ouverture du fichier
    }

    fread(player, sizeof(Diver), 1, file);
    // fread(inv, sizeof(Inventory), 1, file);
    fread(depth, sizeof(int), 1, file);
    fread(zone, sizeof(char) * 50, 1, file); // Supposons que la zone a une taille maximale de 50 caractères
    fread(monstersCount, sizeof(int), 1, file);
    fread(monsters, sizeof(Monster), *monstersCount, file);

    fclose(file);
    return 0;
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

void display_saves(void) {
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
    printf("╚");
    print_chars("═", INNER_WIDTH - 12);
    printf("╝\n");
    printf("> ");
}
