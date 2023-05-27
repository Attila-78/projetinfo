#ifndef HEADER_SAVE
#define HEADER_SAVE 1

#include "map.h"
#include "inventory.h"

#define SAVE_FOLDER ""
#define SAVE_FILE_NAME "valley.save"

typedef struct Save_Struct
{
    Case_inventory inventory[SIZE_INVENTORY];
    Cell map[SIZE_MAP][SIZE_MAP];
    int player_x;
    int player_y;
    // TODO position des entités
} Save_Struct;

// remove the save file
int remove_save();
// check if the save file exists
int save_file_exists();
// save the game in the save file
void save_game(Case_inventory inventory[SIZE_INVENTORY], Cell map[SIZE_MAP][SIZE_MAP], int player_x, int player_y);
// load the game from the save file if it exists
void load_game(Case_inventory inventory[SIZE_INVENTORY], Cell map[SIZE_MAP][SIZE_MAP], int *player_x, int *player_y);
#endif