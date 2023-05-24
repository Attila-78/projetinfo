// constante définissant la taille de l'inventaire 
#define SIZE_INVENTORY 11
// constante définissant la taille d'une case d'inventaire
#define SIZE_SLOT 16

// énumération des contenus possible des cases
typedef enum Object_inventory
{
    OBJECT_NULL,
    OBJECT_LIFE,
    OBJECT_XP,
    OBJECT_TIME,
    OBJECT_FLOWER_YELLOW,
    OBJECT_FLOWER_RED,
    OBJECT_SKULL,

    CONTENT_AMOUNT
} Object_inventory;

//création d'une structure qui permet de connaitre le type et le nombre d'objects dans une case d'inventaire
typedef struct Case_inventory{
    Object_inventory Objet;
    int amount;
    bool Curseur;
    /*curseur nous permettera de sélectionner la case de l'inventaire voulue*/
    }Case_inventory;

