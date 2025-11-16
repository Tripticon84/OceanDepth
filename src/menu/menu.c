#include "menu.h"

#include "../save/save.h"
#include "../utils/utils.h"
#include "../game/game.h"
#include "../inventory/inventory.h"
#include <string.h>

void display_main_menu(void) {
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                🌊 O C E A N D E P T H S 🤿                         ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                                    ║\n");
    printf("║            ~~~~~~~~        ~~~~~~~~        ~~~~~~~~        ~~~~~~~~                ║\n");
    printf("║         ~~~~~~~~~~~~~   ~~~~~~~~~~~~~   ~~~~~~~~~~~~~   ~~~~~~~~~~~~~              ║\n");
    printf("║       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~             ║\n");
    printf("║    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~           ║\n");
    printf("║                                                                                    ║\n");
    printf("║        🐟         🐠            🐡                         🐙                      ║\n");
    printf("║                                                                                    ║\n");
    printf("║                     ⛵    ⛵                                                       ║\n");
    printf("║                  ~~~~~~~~  ~~~~                                                    ║\n");
    printf("║                                                                                    ║\n");
    printf("║        ┌──────────────────────────────────────────────────────────────────────┐    ║\n");
    printf("║        │  « Sous la surface, chaque mètre vous rapproche de l'inconnu... »   │     ║\n");
    printf("║        └──────────────────────────────────────────────────────────────────────┘    ║\n");
    printf("║                                                                                    ║\n");
    printf("║        💧 Santé: ██████████  💨 Oxygène: ████████  ⚠️ Fatigue: ██                  ║\n");
    printf("║                                                                                    ║\n");
    printf("║        [1] JOUER        [2] CHARGER PARTIE        [X] QUITTER                      ║\n");
    printf("║                                                                                    ║\n");
    printf("║        Astuces:                                                                    ║\n");
    printf("║        - Z/Q/S/D ou flèches pour naviguer                                          ║\n");
    printf("║        - Chaque 50 m, la pression augmente… et les trésors aussi                   ║\n");
    printf("║        - Surveillez vos perles pour la boutique du bateau ⛵                       ║\n");
    printf("║                                                                                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("> ");
}


int start_new_game(void) {
    printf("Démarrage d'une nouvelle plongée...\n");

    return 1;
}



void handle_menu_input(void) {
    char input = getchar();
    switch (input) {
        case '1':
            // Jouer -> (ré)initialiser une nouvelle partie puis lancer la carte
            init_game();
            currentGameState = GAME_STATE_PLAYING;
            break;
        case '2':
            // Charger une Partie
            currentGameState = GAME_STATE_SAVE_MENU_LOAD;
            break;
        case 'X':
        case 'x':
            // Quitter le Jeu
            running = 0;
            break;
        default:
            printf("Entrée invalide. Veuillez réessayer.");
            break;
    }
}
