#ifndef OCEANDEPTH_UTILS_H
#define OCEANDEPTH_UTILS_H

#define MIN_TERMINAL_COLS 80
#define MIN_TERMINAL_ROWS 30

typedef struct {
    int rows;
    int cols;
} TerminalSize;

extern TerminalSize terminalSize;

/**
 * Obtient la taille du terminal et la stocke dans la structure TerminalSize.
 * @param size Pointeur vers la structure TerminalSize à remplir.
 * @return 0 en cas de succès, -1 en cas d'échec.
 */
int get_terminal_size(TerminalSize* size);

/**
 * Vérifie si la taille du terminal est suffisante selon les constantes définies.
 * Affiche un message d'erreur et quitte le programme si la taille est insuffisante.
 */
void check_terminal_size(void);

/**
 * Affiche la taille actuelle du terminal (lignes et colonnes).
 */
void print_terminal_size(void);

/**
 * Efface le contenu du terminal.
 */
void clear_terminal(void);

/**
 * Affiche un certain nombre de caractères spécifiés.
 * @param ch Pointeur vers le caractère à afficher.
 * @param count Nombre de fois à afficher le caractère.
 */
void print_chars(char* ch, int count);

/**
 * Calcule la largeur (nombre de caractères) d'une chaîne de caractères.
 * @param text Chaîne de caractères à mesurer.
 * @return Largeur de la chaîne.
 */
int calculate_text_width(const char* text);

/**
 * Calcule la largeur (nombre de chiffres) d'un nombre entier.
 * @param number Nombre à mesurer.
 * @return Largeur du nombre.
 */
int calculate_number_width(int number);

/**
 * Affiche un texte centré dans une largeur donnée.
 * @param text Texte à afficher.
 * @param width Largeur totale pour le centrage.
 */
void print_centered(const char* text, int width);

/**
 * Vide le buffer d'entrée standard.
 */
void clear_input_buffer(void);

/**
 * Met le programme en pause pendant un certain nombre de millisecondes.
 * @param milliseconds Durée de la pause en millisecondes.
 */
void sleep_ms(int milliseconds);

/**
 * Génère un nombre entier aléatoire entre min et max inclus.
 * @param min Valeur minimale.
 * @param max Valeur maximale.
 * @return Nombre aléatoire généré.
 */
int random(int min, int max);

#endif //OCEANDEPTH_UTILS_H
