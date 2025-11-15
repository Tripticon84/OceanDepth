#include "shop.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <conio.h>
#endif

#include "utils/utils.h"

#define SHOP_COLUMNS 4
#define SHOP_ROWS 2
#define SHOP_SLOT_COUNT (SHOP_COLUMNS * SHOP_ROWS)

enum {
    KEY_ARROW_UP = 1000,
    KEY_ARROW_DOWN,
    KEY_ARROW_LEFT,
    KEY_ARROW_RIGHT,
    KEY_ENTER_KEY
};

typedef struct {
    Item item;
    int price;
    bool sold;
} ShopSlot;

static Diver* shopPlayer = NULL;
static Inventory* shopInventory = NULL;

static ShopSlot shopSlots[SHOP_SLOT_COUNT];
static int selectedIndex = 0;

static const enum rarity rarityTable[5][SHOP_SLOT_COUNT] = {
    {COMMUN, COMMUN, COMMUN, UNCOMMUN, UNCOMMUN, UNCOMMUN, RARE, RARE},
    {COMMUN, UNCOMMUN, UNCOMMUN, RARE, RARE, RARE, EPIC, EPIC},
    {UNCOMMUN, RARE, RARE, EPIC, EPIC, EPIC, LEGENDARY, LEGENDARY},
    {RARE, EPIC, EPIC, LEGENDARY, LEGENDARY, LEGENDARY, MYTHIC, MYTHIC},
    {LEGENDARY, LEGENDARY, LEGENDARY, MYTHIC, MYTHIC, MYTHIC, MYTHIC, MYTHIC}
};

static const char* rarityIcons[] = {"▫", "▪", "◆", "◇", "✶", "✷"};
static const int rarityBasePrice[] = {60, 120, 240, 360, 520, 720};

void setup_shop(Diver* player, Inventory* inventory) {
    shopPlayer = player;
    shopInventory = inventory;
}

static int clamp_depth(int depth) {
    if (depth < 1)
        return 1;
    if (depth > 5)
        return 5;
    return depth;
}

static int compute_price(const Item* item) {
    int base = rarityBasePrice[item->rarity];

    switch (item->type.type) {
        case CONSUMABLE:
            base = base / 2;
            if (base < 25)
                base = 25;
            base += (item->quantity - 1) * 15;
            break;
        case WEAPON_CONTACT:
        case WEAPON_DISTANCE:
        case WEAPON_SPECIAL:
            base += (item->maxAttack - item->minAttack) * 3;
            if (item->oxygenCost > 0)
                base -= item->oxygenCost * 5;
            if (base < 80)
                base = 80;
            break;
        case HELMET:
        case SUIT:
        case GLOVES:
        case BOOTS:
            base += item->defenseBonus * 10;
            if (base < 70)
                base = 70;
            break;
        default:
            break;
    }

    if (base < 20)
        base = 20;

    return base;
}

static int depth_to_tier(int depthMeters) {
    if (depthMeters <= 0) {
        return 1;
    }

    int tier = depthMeters / 50;
    if (depthMeters % 50 != 0) {
        tier += 1;
    }

    if (tier < 1)
        tier = 1;
    if (tier > 5)
        tier = 5;

    return tier;
}

static void generate_shop_slots(int depthMeters) {
    int tier = depth_to_tier(depthMeters) - 1;

    for (int i = 0; i < SHOP_SLOT_COUNT; ++i) {
        shopSlots[i].item = generate_random_item(rarityTable[tier][i]);
        shopSlots[i].price = compute_price(&shopSlots[i].item);
        shopSlots[i].sold = false;
    }
}

static void truncate_text(const char* source, char* destination, size_t bufferSize) {
    if (bufferSize == 0) {
        return;
    }

    if (bufferSize == 1) {
        destination[0] = '\0';
        return;
    }

    size_t maxLen = bufferSize - 1;
    size_t srcLen = strlen(source);

    if (srcLen <= maxLen) {
        strncpy(destination, source, maxLen);
        destination[srcLen] = '\0';
        return;
    }

    if (maxLen < 3) {
        strncpy(destination, source, maxLen);
        destination[maxLen] = '\0';
        return;
    }

    strncpy(destination, source, maxLen - 3);
    destination[maxLen - 3] = '.';
    destination[maxLen - 2] = '.';
    destination[maxLen - 1] = '.';
    destination[maxLen] = '\0';
}

static void format_stat_line(const Item* item, char* buffer, size_t size) {
    if (item->type.type == CONSUMABLE) {
        if (strlen(item->effect) > 0) {
            snprintf(buffer, size, "x%d %s", item->quantity, item->effect);
        } else {
            snprintf(buffer, size, "x%d", item->quantity);
        }
    } else if (item->type.type >= HELMET && item->type.type <= BOOTS) {
        snprintf(buffer, size, "DEF +%d", item->defenseBonus);
    } else {
        snprintf(buffer, size, "ATK %d-%d", item->minAttack, item->maxAttack);
    }
}

static void draw_row(int rowIndex) {
    int start = rowIndex * SHOP_COLUMNS;

    printf("║  ┌──────────────┬──────────────┬──────────────┬──────────────┐  ║\n");

    // Ligne des noms
    printf("║  ");
    for (int col = 0; col < SHOP_COLUMNS; ++col) {
        int idx = start + col;
        const ShopSlot* slot = &shopSlots[idx];
        char name[32];
        truncate_text(slot->item.name, name, 14);

        char line[18];
        if (idx == selectedIndex) {
            snprintf(line, sizeof(line), "▶ %-12s", name);
        } else {
            snprintf(line, sizeof(line), "  %-12s", name);
        }
        printf("│ %-12s ", line);
    }
    printf("│  ║\n");

    // Ligne rareté
    printf("║  ");
    for (int col = 0; col < SHOP_COLUMNS; ++col) {
        int idx = start + col;
        const ShopSlot* slot = &shopSlots[idx];
        const char* rarityText = get_item_rarity(slot->item.rarity);
        char rarityLine[18];
        snprintf(rarityLine, sizeof(rarityLine), "%s %s", rarityIcons[slot->item.rarity], rarityText);
        printf("│ %-12s ", rarityLine);
    }
    printf("│  ║\n");

    // Ligne stats
    printf("║  ");
    for (int col = 0; col < SHOP_COLUMNS; ++col) {
        int idx = start + col;
        const ShopSlot* slot = &shopSlots[idx];
        char statLine[18];
        format_stat_line(&slot->item, statLine, sizeof(statLine));
        printf("│ %-12s ", statLine);
    }
    printf("│  ║\n");

    // Ligne prix
    printf("║  ");
    for (int col = 0; col < SHOP_COLUMNS; ++col) {
        int idx = start + col;
        const ShopSlot* slot = &shopSlots[idx];
        char priceLine[18];
        if (slot->sold) {
            snprintf(priceLine, sizeof(priceLine), "VENDU");
        } else {
            snprintf(priceLine, sizeof(priceLine), "💎 %d", slot->price);
        }
        printf("│ %-12s ", priceLine);
    }
    printf("│  ║\n");

    printf("║  └──────────────┴──────────────┴──────────────┴──────────────┘  ║\n");
}

static void render_shop(int depthMeters, const char* message) {
    clear_terminal();
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║                        🛒 BOUTIQUE MARINE 🐚                      ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    if (shopPlayer) {
        printf("║  Perles : %-6d                                  Profondeur max : -%dm ║\n", shopPlayer->pearls,
               depthMeters);
    } else {
        printf("║  Perles : --                                     Profondeur max : -%dm ║\n", depthMeters);
    }
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║  Commandes : Z/Q/S/D pour naviguer • E pour acheter • X pour quitter      ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");

    for (int row = 0; row < SHOP_ROWS; ++row) {
        draw_row(row);
    }

    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    if (message && strlen(message) > 0) {
        char truncated[70];
        truncate_text(message, truncated, sizeof(truncated));
        printf("║  %s%-*s║\n", truncated, (int)(66 - strlen(truncated)), "");
    } else {
        printf("║  Sélectionnez un article puis appuyez sur E pour l'acheter.           ║\n");
    }
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
}

static int read_input_key(void) {
#ifdef _WIN32
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        int arrow = _getch();
        switch (arrow) {
            case 72:
                return KEY_ARROW_UP;
            case 80:
                return KEY_ARROW_DOWN;
            case 75:
                return KEY_ARROW_LEFT;
            case 77:
                return KEY_ARROW_RIGHT;
            default:
                return 0;
        }
    }

    if (ch == '\r')
        return KEY_ENTER_KEY;

    return ch;
#else
    int ch = getchar();
    if (ch == '\033') {
        int next = getchar();
        if (next == '[') {
            int arrow = getchar();
            switch (arrow) {
                case 'A':
                    return KEY_ARROW_UP;
                case 'B':
                    return KEY_ARROW_DOWN;
                case 'C':
                    return KEY_ARROW_RIGHT;
                case 'D':
                    return KEY_ARROW_LEFT;
                default:
                    return 0;
            }
        }
    }

    if (ch == '\n')
        return KEY_ENTER_KEY;

    return ch;
#endif
}

static void move_selection(int key) {
    switch (key) {
        case 'z':
        case 'Z':
        case KEY_ARROW_UP:
            if (selectedIndex >= SHOP_COLUMNS)
                selectedIndex -= SHOP_COLUMNS;
            break;
        case 's':
        case 'S':
        case KEY_ARROW_DOWN:
            if (selectedIndex < SHOP_SLOT_COUNT - SHOP_COLUMNS)
                selectedIndex += SHOP_COLUMNS;
            break;
        case 'q':
        case 'Q':
        case KEY_ARROW_LEFT:
            if (selectedIndex % SHOP_COLUMNS != 0)
                selectedIndex -= 1;
            break;
        case 'd':
        case 'D':
        case KEY_ARROW_RIGHT:
            if ((selectedIndex + 1) % SHOP_COLUMNS != 0)
                selectedIndex += 1;
            break;
        default:
            break;
    }
}

static void attempt_purchase(char* message, size_t messageSize) {
    if (!shopPlayer || !shopInventory) {
        snprintf(message, messageSize, "Boutique non configurée.");
        return;
    }

    ShopSlot* slot = &shopSlots[selectedIndex];

    if (slot->sold) {
        snprintf(message, messageSize, "Article déjà acheté.");
        return;
    }

    if (shopPlayer->pearls < slot->price) {
        snprintf(message, messageSize, "Pas assez de perles (coût %d).", slot->price);
        return;
    }

    bool inventoryFull = (shopInventory->nb_objets >= 8) && (slot->item.type.type != CONSUMABLE);
    if (inventoryFull) {
        snprintf(message, messageSize, "Inventaire plein : libérez de la place.");
        return;
    }

    shopPlayer->pearls -= slot->price;
    add_item(shopInventory, slot->item);
    slot->sold = true;
    snprintf(message, messageSize, "%s ajouté à l'inventaire !", slot->item.name);
}

void showShop(int maxDepthMeters) {
    if (!shopPlayer || !shopInventory) {
        printf("[Boutique] Contexte joueur/inventaire non défini. Utilisez setup_shop avant showShop.\n");
        return;
    }

    maxDepthMeters = depth_to_tier(maxDepthMeters) * 50;
    generate_shop_slots(maxDepthMeters);
    selectedIndex = 0;

    char message[128] = "";

    while (true) {
        render_shop(maxDepthMeters, message);
        printf("> ");
        int key = read_input_key();
        if (key == 0)
            continue;

        if (key == KEY_ENTER_KEY)
            continue;

        if (key == 'x' || key == 'X') {
            break;
        }

        if (key == 'e' || key == 'E') {
            attempt_purchase(message, sizeof(message));
            continue;
        }

        move_selection(key);
    }
}
