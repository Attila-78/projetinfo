#ifndef HEADER_MENU
#define HEADER_MENU 1

#include "map.h"
#include "inventory.h"

typedef enum
{
    MENU_MAIN,
    MENU_GAME,
    MENU_NEW,
    MENU_LOAD,
    // pour les erreurs
    MENU_UNKNOWN
} Main_Menu_Type;

void main_menu(Cell map[SIZE_MAP][SIZE_MAP], Case_inventory inventory[SIZE_INVENTORY]);
#endif