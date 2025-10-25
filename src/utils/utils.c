#include "utils.h"
#include <stdio.h>
#include <windows.h>

TerminalSize terminalSize = {.cols = 80, .rows = 24};

int get_terminal_size(TerminalSize* size) {
    if (size == NULL)
        return -1;

#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE)
        return -1;

    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        size->cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        size->rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        return 0;
    }
    return -1;
#else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
        return -1;
    size->rows = w.ws_row;
    size->cols = w.ws_col;
    return 0;
#endif
}

void print_terminal_size() {
    TerminalSize size;

    if (get_terminal_size(&size) == 0)
        printf("Terminal Size: %d rows, %d cols\n", size.rows, size.cols);
    else
        printf("Erreur: Impossible d'obtenir la taille du terminal\n");
}

void clear_terminal(void) {
#ifdef _WIN32
    // Méthode Windows utilisant l'API Console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    if (hConsole == INVALID_HANDLE_VALUE) return;

    // Obtenir les informations du buffer
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;

    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Remplir le buffer avec des espaces
    if (!FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count)) return;
    // Remplir les attributs
    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count)) return;

    // Replacer le curseur en haut à gauche
    SetConsoleCursorPosition(hConsole, homeCoords);
#else
    // Méthode Unix/Linux avec séquences d'échappement ANSI
    printf("\e[1;1H\e[2J");
    fflush(stdout);

    // Alternative avec system() si les séquences ANSI ne fonctionnent pas
    // system("clear");
#endif
}


void print_chars(char* ch, int count) {
    for (int i = 0; i < count; i++) {
        printf("%s", ch);
    }
}

int calculate_text_width(const char* text) {
    return (int)strlen(text);
}
