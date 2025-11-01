#ifndef OCEANDEPTH_UTILS_H
#define OCEANDEPTH_UTILS_H

#define MIN_TERMINAL_COLS 80
#define MIN_TERMINAL_ROWS 30

typedef struct {
    int rows;
    int cols;
} TerminalSize;

extern TerminalSize terminalSize;

// Obtient la taille du terminal et la stocke dans la structure TerminalSize
int get_terminal_size(TerminalSize* size);

// Vérifie si la taille du terminal est assez grande
void check_terminal_size(void);

// Affiche la taille actuelle du terminal
void print_terminal_size(void);

// Efface le contenu du terminal
void clear_terminal(void);

// Affiche un certain nombre de caractères spécifiés
void print_chars(char* ch, int count);

// Calcule la taille d'une chaine de caractères
int calculate_text_width(const char* text);

// Calcule la taille d'un nombre
int calculate_number_width(int number);

// Vide le buffer
void clear_input_buffer(void);

void sleep_ms(int milliseconds);

int random(int min, int max);

#endif //OCEANDEPTH_UTILS_H
