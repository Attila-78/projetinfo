typedef struct {
    char *floor;
    char *obstacle;
    char *monster;
} cell;

// fonction générant la carte aléatoirement
int map_generator(int **map) {
    // on vérifie que le pointeur n'est pas nul pour être sûr qu'il n'y ai pas de segmentation fault
    if (map == NULL) {
        printf("Il y a eu une erreur de segmentation dans la génération de la carte.");
        return false;
    }
    // generation aléatoire
    for (int y = 1; y < SIZE_MAP; y++) {
        for (int x = 1; x < SIZE_MAP; x++) {
            map[y][x] = map[y-rand()%2][x-rand()%2]+(rand()%(2));
            // affichage
            printf("%d ", map[y][x]);
        }
        printf("\n");
    }
    return true;
}
