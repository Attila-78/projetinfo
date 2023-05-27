#ifndef HEADER_MOVEMENT
#define HEADER_MOVEMENT 1

#include "inventory.h"
#include "map.h"

typedef enum Cell_Orientation
{
    ORIENTATION_UP,
    ORIENTATION_DOWN,
    ORIENTATION_RIGHT,
    ORIENTATION_LEFT,

    ORIENTATION_AMOUNT
} Cell_Orientation;

int equilibre(int n);
void movement_LEFT(Cell map[SIZE_MAP][SIZE_MAP], int pos_x, int pos_y, Case_inventory inventory[]);
void movement_RIGHT(Cell map[SIZE_MAP][SIZE_MAP], int pos_x, int pos_y, Case_inventory inventory[]);
void movement_UP(Cell map[SIZE_MAP][SIZE_MAP], int pos_x, int pos_y, Case_inventory inventory[]);
void movement_DOWN(Cell map[SIZE_MAP][SIZE_MAP], int pos_x, int pos_y, Case_inventory inventory[]);

#endif