// on inclu les librairies nécessaires
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "inventory.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    // On définit le double pointeur pointant vers matrice de 100x100 qui sera notre zone de jeu
    Cell map_matrix[SIZE_MAP][SIZE_MAP];

    // On définit le tableau d'inventaire
    Case_inventory inventory[SIZE_INVENTORY];

    // vider l'inventaire
    purge_inventory(inventory);

    // On remplit l'inventaire avec les variables de base
    inventory[HEALTH_SLOT].amount = INVENTORY_AMOUNT;
    inventory[HEALTH_SLOT].amount = OBJECT_LIFE;
    inventory[POINT_SLOT].Objet = OBJECT_XP;
    inventory[TIME_SLOT].amount = 600;

    main_menu(map_matrix, inventory);

    return 0;
}