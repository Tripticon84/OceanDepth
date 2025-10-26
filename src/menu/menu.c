#include "menu.h"

#include "../save/save.h"
#include "../utils/utils.h"

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
    clear_terminal();
    printf("Démarrage d'une nouvelle plongée...\n");
    display_saves();


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

void display_inventory(void) {}
