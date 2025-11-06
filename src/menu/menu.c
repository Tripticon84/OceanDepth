#include "menu.h"

#include "../save/save.h"
#include "../utils/utils.h"
#include "../game/game.h"
#include "../inventory/inventory.h"
#include <string.h>

void display_main_menu(void) {
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║                        🌊 OCEANDEPTHS 🤿                         ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║   🏝️  [1] NOUVELLE PLONGÉE                                       ║\n");
    printf("║   💾  [2] CHARGER UNE PARTIE                                     ║\n");
    printf("║   🗺️  [3] CARTOGRAPHIE DES OCÉANS                                ║\n");
    printf("║   🧪  [4] COMPÉTENCES MARINES                                    ║\n");
    printf("║   🧰  [5] INVENTAIRE                                             ║\n");
    // printf("║   ⚙️  [6] OPTIONS                                                ║\n");
    printf("║   🚪  [6] QUITTER LE JEU                                         ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║  💧 Oxygène critique ? Revenez à la surface avant qu’il ne soit  ║\n");
    printf("║  trop tard...                                                    ║\n");
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
    printf("> ");
}


int start_new_game(void) {
    printf("Démarrage d'une nouvelle plongée...\n");

    return 1;
}


void display_options(void) {
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║                          ⚙️ OPTIONS                               ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║   🌐  [1] Changer la langue                                      ║\n");
    printf("║   🔊  [2] Activer/Désactiver les effets sonores                  ║\n");
    printf("║   💾  [3] Activer/Désactiver la sauvegarde automatique           ║\n");
    printf("║   🎨  [4] Modifier le thème visuel                               ║\n");
    printf("║   🔙  [5] Retour au menu principal                               ║\n");
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
    printf("> ");
}

void display_inventory(Inventory* inv) {
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║                        🧰 INVENTAIRE 🤿                           ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                  ║\n");
    
    // Affichage des équipements portés
    printf("║  🛡️  ÉQUIPEMENT PORTÉ :                                          ║\n");
    printf("║                                                                  ║\n");
    
    if (inv && inv->equipedWeapon) {
        printf("║  ⚔️  Arme : %-50s ║\n", inv->equipedWeapon->name);
    } else {
        printf("║  ⚔️  Arme : Aucune                                            ║\n");
    }
    
    if (inv && inv->equipedHelmet) {
        printf("║  🪖 Casque : %-48s ║\n", inv->equipedHelmet->name);
    } else {
        printf("║  🪖 Casque : Aucun                                            ║\n");
    }
    
    if (inv && inv->equipedSuit) {
        printf("║  🦺 Combinaison : %-44s ║\n", inv->equipedSuit->name);
    } else {
        printf("║  🦺 Combinaison : Aucune                                       ║\n");
    }
    
    if (inv && inv->equipedGloves) {
        printf("║  🧤 Gants : %-50s ║\n", inv->equipedGloves->name);
    } else {
        printf("║  🧤 Gants : Aucuns                                            ║\n");
    }
    
    if (inv && inv->equipedBoots) {
        printf("║  👢 Bottes : %-49s ║\n", inv->equipedBoots->name);
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
            char itemLine[70];
            snprintf(itemLine, sizeof(itemLine), "  [%d] %s (x%d)", 
                     i + 1, inv->objets[i].name, inv->objets[i].quantity);
            printf("║ %-64s ║\n", itemLine);
        }
    } else {
        printf("║  Inventaire vide...                                            ║\n");
    }
    
    printf("║                                                                  ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║  💡 Utilisez les numéros pour équiper ou consommer des objets    ║\n");
    printf("║  🔙 Appuyez sur [0] pour retourner au menu principal             ║\n");
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
    printf("> ");
}

void handle_menu_input(void) {
    char input = getchar();
    switch (input) {
        case '1':
            // Nouvelle Plongée
            currentGameState = GAME_STATE_SAVE_MENU_CREATE;
            break;
        case '2':
            // Charger une Partie
            currentGameState = GAME_STATE_SAVE_MENU_LOAD;
            break;
        case '3':
            // Cartographie des Océans
            clear_terminal();
            printf("Affichage de la cartographie des océans...");
            break;
        case '4':
            // Compétences Marines
            clear_terminal();
            // display_skills();
            break;
        case '5':
            // Inventaire
            clear_terminal();
            // display_inventory(NULL); // TODO: Passer l'inventaire du joueur
            break;
        case '6':
        case 'q':
        case 'Q':
            // Quitter le Jeu
            running = 0;
            break;
        default:
            // clear_input_buffer();
            printf("Entrée invalide. Veuillez réessayer.");
            // sleep_ms(1000);
            break;
    }
}
