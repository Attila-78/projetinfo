#include "movement.h"

// définition de la constante taille
#define SIZE_MAP 100

// définition des valeurs vraies/faux
#define true 1
#define false 0

// définition du epsilon gérant la partie aléatoire de la génération de la cart
#define EPSILON 2

// définition de la longueur et la largeur de la fenêtre de jeu
#define WIDTH 800
#define HEIGHT 800

// énumération des types de cases
typedef enum Cell_type
{
    CELL_GRASS,
    CELL_DIRT,
    CELL_WATER,
    CELL_SNOW,
    CELL_ROCK,
    CELL_SAND,
    CELL_MUD,
    CELL_MAGMA,

    CELL_AMOUNT
} Cell_type;

// énumération des contenus des cases
typedef enum Cell_content
{
    CONTENT_NOTHING,
    CONTENT_HERO,
    CONTENT_FLOWER,
    CONTENT_ROCK,
    CONTENT_CRATE,
    CONTENT_PNJ,
    CONTENT_MONSTER,

    CONTENT_AMOUNT
} Cell_Content;

// structure qui donne le contenu et le type d'une case
typedef struct Cell
{
    Cell_type type;
    Cell_Content content;
    Cell_Orientation orientation;
} Cell;

int abs(int x);
int random_sign(int start);
void clamp(int min, int max, int *num);
int map_renderer(int **map);
int **map_generate();

// gcc main.c map.c -o CYValley.exe -I include -L lib -lSDL2main -lSDL2
