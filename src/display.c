#include "include/display.h"

void display_progress_bar(int current, int max, int width) {
    int filled = (current * width) / max;
    for (int i = 0; i < filled; i++) printf("█");
    for (int i = filled; i < width; i++) printf("▒");
}
