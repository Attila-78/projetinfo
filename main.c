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
    int **map_matrix = map_generate();

    // generation
    if (!map_renderer(map_matrix))
    {
        printf("Il y a eu une erreur.\n");
    }

    // on libère l'espace utilisé
    for (int line = 0; line < SIZE_MAP; line++)
    {
        free(map_matrix[line]);
    }
    free(map_matrix);

    return 0;
}
