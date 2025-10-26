#ifndef OCEANDEPTH_UTILS_H
#define OCEANDEPTH_UTILS_H

typedef struct {
    int rows;
    int cols;
} TerminalSize;

extern TerminalSize terminalSize;

// Obtient la taille du terminal et la stocke dans la structure TerminalSize
int get_terminal_size(TerminalSize* size);

// Affiche la taille actuelle du terminal
void print_terminal_size();

// Efface le contenu du terminal
void clear_terminal();

// Affiche un certain nombre de caractères spécifiés
void print_chars(char* ch, int count);

// Calcule la taille d'une chaine de caractères
int calculate_text_width(const char* text);

// Calcule la taille d'un nombre
int calculate_number_width(int number);

#endif //OCEANDEPTH_UTILS_H
