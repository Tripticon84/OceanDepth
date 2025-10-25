#include "include/display.h"
#include <stdio.h>
#include <string.h>
#include "include/utils.h"

void display_progress_bar(int current, int max, int width) {
    int filled = (current * width) / max;
    printf("[");
    for (int i = 0; i < filled; i++) printf("█");
    for (int i = filled; i < width; i++) printf("▒");
    printf("]");
}

int calculate_number_width(int number) {
    if (number == 0)
        return 1;
    int width = 0;
    if (number < 0) {
        width = 1; // pour le signe moins
        number = -number;
    }
    while (number > 0) {
        width++;
        number /= 10;
    }
    return width;
}

void display_empty_line() {
    printf("║");
    print_chars(" ", terminalSize.cols - 2);
    printf("║\n");
}

////

void display_header(int depth, int pearls) {
    int pearlsTextSize = calculate_number_width(pearls);
    int deepthTextSize = calculate_number_width(depth);

    printf("╔");
    print_chars("═", terminalSize.cols - 2);
    printf("╗\n");

    printf("║");
    printf(" 🌊 Ocean Depth - Profondeur : -%dm", depth);

    for (int i = 0; i < 32 - (deepthTextSize + pearlsTextSize); i++) printf(" ");

    char pearlsText[] = "💎 Perles :";

    printf("%s %d ", pearlsText, pearls);
    printf("║\n");
}


void display_separator() {
    printf("╠");
    print_chars("═", terminalSize.cols - 2);
    printf("╣\n");
}

void display_action_menu_title() {
    printf("%s ", BORDER_CHAR);
    // TODO: Intelligence pour le choix des messages d'alerte
    char message[] = "💬 [BULLE] Oxygène faible ! Vous sentez la pression monter...";
    printf("%s", message);


    print_chars(" ", terminalSize.cols - 1 - calculate_text_width(message));
    printf(" %s", BORDER_CHAR);
    printf("\n");
}

void display_combat_actions_menu(Diver* diver, int remainingAttacks) {
    printf("%s", BORDER_CHAR);

    // Titre
    char title[] = "🔧 ACTIONS DISPONIBLES :";
    printf(" %s", title);
    print_chars(" ", terminalSize.cols - 1 - calculate_text_width(title));
    printf("%s\n", BORDER_CHAR);

    printf("%s", BORDER_CHAR);


    // Option 1
    printf(" [1] ");
    char opt1[] = "Attaquer avec %s (%d attaques restantes)";
    char weaponName[] = "PLACEHOLDER";

    printf(opt1, weaponName, remainingAttacks);
    print_chars(" ", terminalSize.cols - 4 - calculate_text_width(opt1) - strlen(weaponName));
    printf("%s\n", BORDER_CHAR);
    // printf("Attaquer avec %s (%d attaques restantes)\n", diver->inventory.equipedWeapon->name, remainingAttacks);

    // Option 2
    printf("%s", BORDER_CHAR);
    printf(" [2] ");
    char opt2[] = "Compétences Marines";

    printf("%s", opt2);
    print_chars(" ", terminalSize.cols - 6 - calculate_text_width(opt2));
    printf("%s\n", BORDER_CHAR);

    // Option 3
    printf("%s", BORDER_CHAR);
    printf(" [3] ");
    char opt3[] = "Consommer objet";

    printf("%s", opt3);
    print_chars(" ", terminalSize.cols - 7 - calculate_text_width(opt3));
    printf("%s\n", BORDER_CHAR);

    // Option 4
    printf("%s", BORDER_CHAR);
    printf(" [4] ");
    char opt4[] = "Terminer le tour";

    printf("%s", opt4);
    print_chars(" ", terminalSize.cols - 7 - calculate_text_width(opt4));
    printf("%s\n", BORDER_CHAR);
}

void display_combat_main(Diver* player, Monster monsters[], int nbMonsters) {
    // Ligne 1 : Titres
    printf("%s  ", BORDER_CHAR);

    char diverTitle[] = "🤿 PLONGEUR";
    char monstersTitle[] = "🐙 CRÉATURES MARINES";

    printf("%s", diverTitle);
    print_chars(" ", 23);
    printf("%s", monstersTitle);
    print_chars(" ", terminalSize.cols - 24 - 11 - calculate_text_width(monstersTitle));
    printf("%s\n", BORDER_CHAR);


    // Ligne 2 : Cadres Joueur + créatures ligne 1
    printf("%s", BORDER_CHAR);
    printf("  ┌───────────────────────┐");
    print_chars(" ", 8);
    for (int i = 0; i < nbMonsters && i < 2; i++) {
        print_chars(" ", 1);
        printf("┌──────────────────┐");
    }

    if (nbMonsters == 0) print_chars(" ", 43);
    if (nbMonsters == 1) print_chars(" ", 22);
    if (nbMonsters >= 2) print_chars(" ", 1);
    printf("%s\n", BORDER_CHAR);

    // Ligne 3 : Vie du joueur + noms des créatures (ligne 1)
    printf("%s", BORDER_CHAR);
    printf("  │ Vie 💚                │");
    print_chars(" ", 8);
    for (int i = 0; i < nbMonsters && i < 2; i++) {
        printf(" ");
        printf("│ %s ", monsters[i].icon);
        printf("%.*s", i == 0 ? 14 : 13, monsters[i].name);
        if (strlen(monsters[i].name) < 13)
            print_chars(" ", 13 - calculate_text_width(monsters[i].name));
        printf(" │");
    }

    if (nbMonsters == 0) print_chars(" ", 43);
    if (nbMonsters == 1) print_chars(" ", 22);
    if (nbMonsters >= 2) print_chars(" ", 1);

    printf("%s\n", BORDER_CHAR);

    // Ligne 4 : Barre de vie + PV des créatures (ligne 1)
    printf("%s", BORDER_CHAR);
    printf("  │ ");
    display_progress_bar(player->health, player->maxHealth, 12);
    printf("%3d/%-3d │", player->health, player->maxHealth);
    print_chars(" ", 8);
    for (int i = 0; i < nbMonsters && i < 2; i++) {
        printf(" ");
        printf("│ PV:%4d/%-4d     │", monsters[i].health, monsters[i].maxHealth);
    }
    if (nbMonsters == 0) print_chars(" ", 43);
    if (nbMonsters == 1) print_chars(" ", 22);
    if (nbMonsters >= 2) print_chars(" ", 1);
    printf("%s\n", BORDER_CHAR);

    // Ligne 5 : Oxygène + effets (ligne 1)
    printf("%s", BORDER_CHAR);
    printf("  │ O₂ 💧                 │");
    print_chars(" ", 8);
    for (int i = 0; i < nbMonsters && i < 2; i++) {
        printf(" ");
        printf("│ Effet: %.9s", strcmp(monsters[i].specialEffect, "aucun") == 0 ? "Aucun" : monsters[i].specialEffect);
        if (strlen(monsters[i].specialEffect) < 9)
            print_chars(" ", 9 - calculate_text_width(monsters[i].specialEffect));
        printf(" │");
    }
    if (nbMonsters == 0) print_chars(" ", 43);
    if (nbMonsters == 1) print_chars(" ", 22);
    if (nbMonsters >= 2) print_chars(" ", 1);
    printf("%s\n", BORDER_CHAR);

    // Ligne 6 : Barre d'oxygène + fermeture cadres (ligne 1)
    printf("%s", BORDER_CHAR);
    printf("  │ ");
    display_progress_bar(player->oxygen, player->maxOxygen, 12);
    printf("%3d/%-3d │", player->oxygen, player->maxOxygen);
    print_chars(" ", 8);
    for (int i = 0; i < nbMonsters && i < 2; i++) {
        printf(" ");
        printf("└──────────────────┘");
    }

    if (nbMonsters == 0) print_chars(" ", 43);
    if (nbMonsters == 1) print_chars(" ", 22);
    if (nbMonsters >= 2) print_chars(" ", 1);
    printf("%s\n", BORDER_CHAR);

    // Ligne 7 : Fatigue + cadres monstres (ligne 2)
    printf("%s", BORDER_CHAR);
    printf("  │ ");
    printf("Fatigue ⚠️            │");
    print_chars(" ", 8);
    if (nbMonsters > 2) {
        for (int i = 2; i < nbMonsters && i < 4; i++) {
            print_chars(" ", 1);
            printf("┌──────────────────┐");
        }

        if (nbMonsters == 3) print_chars(" ", 22);
        if (nbMonsters >= 4) print_chars(" ", 1);
    } else {
        print_chars(" ", 43);
    }
    printf("%s\n", BORDER_CHAR);

    // Ligne 8 : Barre de fatigue + noms monstres (ligne 2)
    printf("%s", BORDER_CHAR);
    printf("  │ ");

    display_progress_bar(player->tiredness, player->maxTiredness, 12);
    printf(" %d/%d    │", player->tiredness, player->maxTiredness);
    print_chars(" ", 8);
    if (nbMonsters > 2) {
        for (int i = 2; i < nbMonsters && i < 4; i++) {
            printf(" ");
            printf("│ %s ", monsters[i].icon);
            printf("%.*s", 13, monsters[i].name);
            if (strlen(monsters[i].name) < 13)
                print_chars(" ", 13 - calculate_text_width(monsters[i].name));
            printf(" │");
        }

        if (nbMonsters == 3) print_chars(" ", 22);
        if (nbMonsters >= 4) print_chars(" ", 1);
    } else {
        print_chars(" ", 43);
    }
    printf("%s\n", BORDER_CHAR);

    // Ligne 9 : Fermeture cadre joueur + PV monstres (ligne 2)
    printf("%s", BORDER_CHAR);
    printf("  └───────────────────────┘");
    print_chars(" ", 8);
    if (nbMonsters > 2) {
        for (int i = 2; i < nbMonsters && i < 4; i++) {
            printf(" ");
            printf("│ PV: %3d/%-3d      │", monsters[i].health, monsters[i].maxHealth);
        }
        if (nbMonsters == 3) print_chars(" ", 22);
        if (nbMonsters >= 4) print_chars(" ", 1);
    } else {
        print_chars(" ", 43);
    }
    printf("%s\n", BORDER_CHAR);

    // Ligne 10 : Effets monstres (ligne 2)
    printf("%s", BORDER_CHAR);
    print_chars(" ", 35);
    if (nbMonsters > 2) {
        for (int i = 2; i < nbMonsters && i < 4; i++) {
            printf(" ");
            printf("│ Effet: %.9s", strcmp(monsters[i].specialEffect, "aucun") == 0 ? "Aucun" : monsters[i].specialEffect);
            if (strlen(monsters[i].specialEffect) < 9)
                print_chars(" ", 9 - calculate_text_width(monsters[i].specialEffect));
            printf(" │");
        }
        if (nbMonsters == 3) print_chars(" ", 22);
        if (nbMonsters >= 4) print_chars(" ", 1);
    } else {
        print_chars(" ", 43);
    }
    printf("%s\n", BORDER_CHAR);

    // Ligne 11 : Fermeture cadres monstres (ligne 2)
    printf("%s", BORDER_CHAR);
    print_chars(" ", 35);
    if (nbMonsters > 2) {
        for (int i = 2; i < nbMonsters && i < 4; i++) {
            printf(" ");
            printf("└──────────────────┘");
        }
        if (nbMonsters == 3) print_chars(" ", 22);
        if (nbMonsters >= 4) print_chars(" ", 1);
    } else {
        print_chars(" ", 43);
    }
    printf("%s\n", BORDER_CHAR);
}

void display_footer() {
    printf("╚");
    print_chars("═", terminalSize.cols - 2);
    printf("╝\n");
}

void display_input() {
    printf("> ");
}

void display_combat_interface(Diver* player, Monster creatures[], int creatureCount, int depth, int pearls) {
    display_header(depth, pearls);
    display_separator();

    // Main
    display_empty_line();

    display_combat_main(player, creatures, creatureCount);

    display_empty_line();
    display_separator();
    // Footer
    display_action_menu_title();
    display_empty_line();

    display_combat_actions_menu(player, 3);
    display_empty_line();
    display_footer();

    // Input
    display_input();
}
