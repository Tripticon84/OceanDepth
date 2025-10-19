#ifndef OCEANDEPTH_UTILS_H
#define OCEANDEPTH_UTILS_H

typedef struct {
    int rows;
    int cols;
} TerminalSize;

extern TerminalSize terminalSize;

int get_terminal_size(TerminalSize* size);

void print_terminal_size();

void clear_terminal();

void print_chars(char* ch, int count);

int calculate_text_width(const char* text);

#endif //OCEANDEPTH_UTILS_H
