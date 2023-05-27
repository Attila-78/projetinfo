#include "menu.h"
#include "input.h"
#include "save.h"
#include <stdio.h>
#include <stdlib.h>

void main_menu(Cell map[SIZE_MAP][SIZE_MAP], Case_inventory inventory[SIZE_INVENTORY])
{
    int correct = 0;
    int input = 0;
    int menu_running = true;
    int player_x = 0;
    int player_y = 0;

    while (menu_running)
    {
        // efface la console
        platform_console_clear();
        // affiche le menu
        printf("Main menu:\n1 - New game\n2 - Load game\n3 - Exit\n");

        // demande quelle fonction choisir
        do
        {
            correct = scanf("%d", &input);
            clean_input();
        } while (correct != 1 || input < 1 || input > 3);

        // action en fonction de l'option choisie
        switch (input)
        {
        case 1:
            // new game
            map_generate_cell(map);
            while (true)
            {
                map_display(map, &player_x, &player_y);
                save_game(inventory, map, player_x, player_y);
            }
            break;
        case 2:
            // load game
            if (!save_file_exists())
            {
                printf("No save file found.\n");
                platform_sleep(2000);
            }
            else
            {
                load_game(inventory, map, &player_x, &player_y);
                // TODO launch game
                while (true)
                {
                    map_display(map, &player_x, &player_y);
                }
            }
            break;
        case 3:
            // exit game
            printf("Bye!");
            platform_sleep(2000);
            exit(0);
            break;
        default:
            printf("input is out of range in main_menu\n");
            platform_sleep(2000);
            break;
        }
    }
}