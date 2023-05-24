// on inclu les librairies nécessaires
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/SDL.h"
#include <unistd.h>
#include "map.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    // On définit le double pointeur pointant vers matrice de 100x100
    Cell map_matrix[SIZE_MAP][SIZE_MAP];

    map_generate_cell(map_matrix);

    // generation
    if (!map_renderer(map_matrix))
    {
        printf("Il y a eu une erreur.\n");
    }

    return 0;
}
