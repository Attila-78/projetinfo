#ifndef HEADER_MAP
#define HEADER_MAP 1

// définition de la constante taille
#define SIZE_MAP 100

// définie la champ de vision autour du joueur
#define PLAYER_VIEW 3

// définition des valeurs vraies/faux
#define true 1
#define false 0

// définition du epsilon gérant la partie aléatoire de la génération de la cart
#define EPSILON 2

// définition de la longueur et la largeur de la fenêtre de jeu
#define WIDTH SDL_WINDOW_FULLSCREEN_DESKTOP
#define HEIGHT SDL_WINDOW_FULLSCREEN_DESKTOP

// énumération des types de cases
typedef enum Cell_type
{
    CELL_GRASS,
    CELL_DIRT,
    CELL_WATER,
    CELL_SAND,

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
    CONTENT_FENCE,
    CONTENT_PNJ,
    CONTENT_MONSTER,

    CONTENT_AMOUNT
} Cell_Content;

// structure qui donne le contenu et le type d'une case
typedef struct Cell
{
    Cell_type type;
    Cell_Content content;
} Cell; 

int abs(int x);
int random_sign(int start);
void clamp(int min, int max, int *num);
int map_renderer(Cell map[SIZE_MAP][SIZE_MAP]);
void map_generate_cell(Cell map[SIZE_MAP][SIZE_MAP]);
void map_display(Cell map[SIZE_MAP][SIZE_MAP], int *player_x, int *player_y);

#endif