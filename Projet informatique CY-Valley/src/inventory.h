#ifndef HEADER_INVENTORY
#define HEADER_INVENTORY 1

// constante définissant la taille de l'inventaire
#define SIZE_INVENTORY 11
// constante définissant la taille d'une case d'inventaire
#define SIZE_SLOT 16
// constante définissant la place de la variable vie dans le tableau
#define HEALTH_SLOT 1
// constante définissant la place de la variable point dans le tableau
#define POINT_SLOT 2
// constante définissant la place de la variable point dans le tableau
#define TIME_SLOT 3

// énumération des contenus possible des cases
typedef enum Object_inventory
{
    OBJECT_NULL,
    OBJECT_LIFE,
    OBJECT_XP,
    OBJECT_TIME,
    OBJECT_FLOWER_YELLOW,
    OBJECT_SKULL,

    INVENTORY_AMOUNT
} Object_inventory;

// création d'une structure qui permet de connaitre le type et le nombre d'objects dans une case d'inventaire
typedef struct Case_inventory
{
    Object_inventory Objet;
    int amount;
    int Curseur;
    /*curseur nous permettera de sélectionner la case de l'inventaire voulue*/
} Case_inventory;

void add_inventory(Case_inventory inventory[], Object_inventory item);
void remove_inventory(Case_inventory inventory[], int n);
void remove_health(Case_inventory inventory[]);
void add_xp(Case_inventory inventory[], int amount);
void remove_time(Case_inventory inventory[]);
void inventory_left(Case_inventory inventory[], int *n);
void inventory_right(Case_inventory inventory[], int *n);
void purge_inventory(Case_inventory inventory[]);

#endif