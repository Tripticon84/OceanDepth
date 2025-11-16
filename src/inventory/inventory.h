#ifndef OCEANDEPTH_INVENTORY_H
#define OCEANDEPTH_INVENTORY_H


enum type {
    // Divers
    CONSUMABLE = 0,

    // Armes
    WEAPON_CONTACT  = 10,
    WEAPON_DISTANCE = 11,
    WEAPON_SPECIAL  = 12,

    // Armures
    HELMET = 20,
    SUIT   = 21,
    GLOVES = 22,
    BOOTS  = 23,
};

enum rarity {
    COMMUN    = 0,
    UNCOMMUN  = 1,
    RARE      = 2,
    EPIC      = 3,
    LEGENDARY = 4,
    MYTHIC    = 5
};

typedef struct {
    char name[100];
    enum type type; // Type de l'objet (CONSUMABLE, WEAPON_CONTACT, etc.)
} TypeItem;

typedef struct {
    char name[100];
    enum rarity rarity;
    TypeItem type;
    int minAttack;
    int maxAttack;
    int quantity;
    int defenseBonus;
    int oxygenCost;
    char effect[50]; // "soin", "boost_oxygene", "boost_attaque", "boost_defense", "boost_vitesse"
} Item;

typedef struct {
    Item objets[8];
    int nb_objets;
    Item equipedWeapon;
    Item equipedHelmet;
    Item equipedSuit;
    Item equipedGloves;
    Item equipedBoots;
} Inventory;

void init_inventory(Inventory* inv);

/**
 * @brief Initialise l'inventaire avec les items de départ (Trident Rouillé et Armure basique)
 * @param inv Pointeur vers l'inventaire à initialiser
 */
void init_starting_inventory(Inventory* inv);

/**
 * @brief Ouvre l'inventaire sous-marin avec gestion des objets.
 * @param inv Pointeur vers l'inventaire à afficher
 */
void display_inventory(Inventory* inv);

/**
 * @brief Nettoie l'inventaire en réinitialisant tous les objets et compteurs.
 * @param inv Pointeur vers l'inventaire à nettoyer
 */
void clean_inventory(Inventory* inv);

/**
 * @brief Ajoute un nouvel objet à l'inventaire.
 * @param inv Pointeur vers l'inventaire
 * @param newItem Objet à ajouter
 */
void add_item(Inventory* inv, Item newItem);

/**
 * @brief Génère un objet aléatoire selon la rareté spécifiée.
 * @param rarity Niveau de rareté souhaité
 * @return Un objet généré aléatoirement
 */
Item generate_random_item(int rarity);

/**
 * @brief Utilise un objet de l'inventaire à l'index donné.
 * @param inv Pointeur vers l'inventaire
 * @param index Index de l'objet à utiliser
 */
void use_item(Inventory* inv, int index);

/**
 * @brief Équipe une arme depuis l'inventaire à l'index donné.
 * @param inv Pointeur vers l'inventaire
 * @param index Index de l'arme à équiper
 */
void equip_weapon(Inventory* inv, int index);

/**
 * @brief Équipe une armure depuis l'inventaire à l'index donné.
 * @param inv Pointeur vers l'inventaire
 * @param index Index de l'armure à équiper
 */
void equip_armor(Inventory* inv, int index);

/**
 * @brief Retourne une chaîne représentant le type d'objet.
 * @param t Type d'objet
 * @return Chaîne de caractères du type
 */
char* get_item_type(enum type t);

/**
 * @brief Retourne une chaîne représentant la rareté d'un objet.
 * @param r Rareté de l'objet
 * @return Chaîne de caractères de la rareté
 */
char* get_item_rarity(enum rarity r);
#endif //OCEANDEPTH_INVENTORY_H
