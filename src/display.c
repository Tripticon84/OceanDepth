#include "include/display.h"
#include <stdio.h>
#include <string.h>
#include "include/utils.h"

void display_progress_bar(int current, int max, int width) {
    int filled = (current * width) / max;
    for (int i = 0; i < filled; i++) printf("█");
    for (int i = filled; i < width; i++) printf("▒");
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

void print_padded_text(const char* text, int width, char align) {}

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

void display_diver_box(Diver* player) {}

void display_diver_stats(Diver* player) {}

void display_diver_life(Diver* player) {}

void display_diver_oxygen(Diver* player) {}

void display_diver_oxygen_bar(Diver* player) {}
void display_diver_fatigue(Diver* player) {}

void display_diver_fatigue_bar(Diver* player) {}

void display_diver_box_bottom() {}

void display_creatures_in_combat(Monster creatures[], int count) {}

void display_separator() {
    printf("╠");
    print_chars("═", terminalSize.cols - 2);
    printf("╣\n");
}

void display_critical_oxygen_alert(int oxygenLevel) {}

void display_resource_bars(Diver* player) {}

void display_action_menu_title() {
    printf("%s ", BORDER_CHAR);
    // TODO: Intélligence pour le choix des messages d'alerte
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

void display_footer() {
    printf("╚");
    print_chars("═", terminalSize.cols - 2);
    printf("╝\n");
}

void display_input() {
    printf("> ");
}

void display_combat_interface(Diver* player, Monster creatures[], int creatureCount, int depth) {
    display_header(depth, creatureCount);
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
