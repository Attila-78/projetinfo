#include "save.h"
#include <stdlib.h>
#include <stdio.h>

int remove_save()
{
    remove(SAVE_FOLDER SAVE_FILE_NAME);
}

int save_file_exists()
{
    FILE *f = fopen(SAVE_FOLDER SAVE_FILE_NAME, "r");
    if (f == NULL)
    {
        return false;
    }
    fclose(f);
    return true;
}

void save_game(Case_inventory inventory[SIZE_INVENTORY], Cell map[SIZE_MAP][SIZE_MAP], int player_x, int player_y)
{
    FILE *save_file = fopen(SAVE_FOLDER SAVE_FILE_NAME, "wb");
    if (save_file == NULL)
    {
        printf("Failed to get the save file in save_game\n");
        // failed to save
        return ;
    }

    Save_Struct save;
    save.player_x = player_x;
    save.player_y = player_y;
    for (int x = 0; x < SIZE_INVENTORY; x++)
    {
        save.inventory[x] = inventory[x];
    }
    for (int x = 0; x < SIZE_MAP; x++)
    {
        for (int y = 0; y < SIZE_MAP; y++)
        {
            save.map[x][y] = map[x][y];
        }
    }

    // write in the file
    fwrite(&save, sizeof(Save_Struct), 1, save_file);

    // close stream
    fclose(save_file);
}

void load_game(Case_inventory inventory[SIZE_INVENTORY], Cell map[SIZE_MAP][SIZE_MAP], int *player_x, int *player_y)
{
    FILE *save_file = fopen(SAVE_FOLDER SAVE_FILE_NAME, "rb");
    if (save_file == NULL)
    {
        printf("Failed to get the save file in save_game\n");
        // failed to save
        return ;
    }

    Save_Struct save;
    // read in the file
    fread(&save, sizeof(Save_Struct), 1, save_file);

    *player_x = save.player_x;
    *player_y = save.player_y;

    for (int x = 0; x < SIZE_INVENTORY; x++)
    {
        inventory[x] = save.inventory[x];
    }
    for (int x = 0; x < SIZE_MAP; x++)
    {
        for (int y = 0; y < SIZE_MAP; y++)
        {
            map[x][y] = save.map[x][y];
        }
    }

    // close stream
    fclose(save_file);
}