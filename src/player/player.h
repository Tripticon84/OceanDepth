#ifndef OCEANDEPTH_PLAYER_H
#define OCEANDEPTH_PLAYER_H


typedef struct {
    int health;
    int maxHealth;
    int oxygen;
    int maxOxygen;
    short tiredness;
    short maxTiredness; // 1 (peu fatigué) à 5 (très fatigué)
    int pearls;
    // Inventory* inventory;
} Diver;

void init_player(Diver* player);
void clean_player(Diver* player);

#endif //OCEANDEPTH_PLAYER_H
