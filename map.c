// on inclu les librairies nécessaires
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// définition de la constante taille
#define SIZE_MAP 100
#define true 1
#define false 0
#define EPSILON 2
 
typedef enum Case_type {
    CASE_GRASS,
    CASE_DIRT,
    CASE_WATER,
    CASE_SNOW,
    CASE_ROCK,
    CASE_SAND,
    CASE_MUD,

    CASE_AMOUNT
} Case_type;

typedef enum Case_content{
    NOTHING,
    FLOWER,
    ROCK,
    MONSTER,
    
    CONTENT_AMOUNT
} Case_Content;

int abs(int x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

// donne un signe aléatoire à la valeur donnée
int random_sign(int start) {
    if (start < EPSILON) {
        return 1;
    }
    if (start > CASE_AMOUNT - EPSILON) {
        return -1;
    }
    return rand() % 2 ? 1 : -1;
}

//fonction permettant de borner la génération
void clamp(int min, int max, int *num) {
    if (*num < min) {
        *num = min;
        return;
    }
    if (*num > max) {
        *num = max;
        return;
    }
}

// fonction générant la carte aléatoirement
int map_generator(int **map) {
    // on vérifie que le pointeur n'est pas nul pour être sûr qu'il n'y ai pas de segmentation fault
    if (map == NULL) {
        return false;
    }

    int min, max;

    // generation aléatoire
    for (int y = 0; y < SIZE_MAP; y++) {
        for (int x = 0; x < SIZE_MAP; x++) {
            if (x == 0 && y == 0) {
                // aucune case au dessus ou à gauche
                map[y][x] = rand() % CASE_AMOUNT;

            } else if (y == 0) {
                // aucune case au dessus
                map[y][x] = map[y][x - 1] + random_sign(map[y][x - 1]) * (rand() % EPSILON);

            } else if (x == 0) {
                // aucune case à gauche
                map[y][x] = map[y - 1][x] + random_sign(map[y - 1][x]) * (rand() % EPSILON);

            } else {
                // comme avant, même ligne et en haut
                // impossible de trouver une valeur +/- epsilon pour remplir notre objectif
                if (abs(map[y - 1][x] - map[y][x - 1]) > EPSILON) {
                    map[y][x] = (map[y - 1][x] + map[y][x - 1]) / 2;

                } else {
                    // ici oui, donc on prends la valeur minimale et on ajoute rand()%EPSILON
                    if (map[y - 1][x] > map[y][x - 1]) {
                        min = map[y][x - 1];
                        max = map[y - 1][x];
                    } else {
                        min = map[y - 1][x];
                        max = map[y][x - 1];
                    }

                    if (max == min) {
                        map[y][x] = map[y - 1][x] + (rand() % 2 ? 1 : -1) * (rand() % EPSILON);
                    } else {
                        // on choisis de façon aléatoire où l'on applique epsilon
                        if (rand() % 2) {
                            map[y][x] = max - rand() % EPSILON;
                        } else {
                            map[y][x] = min + rand() % EPSILON;
                        }
                    }
                }
            }

            // on borne nos nombres
            clamp(0, CASE_AMOUNT, &map[y][x]);

            // affichage
            printf("%d ", map[y][x]);
        }
        printf("\n");
    }
    return true;
}

int main() {
    srand(time(NULL));

    // On définit le double pointeur pointant vers matrice de 100x100
    int **map_matrix = NULL;
    // allocation dynamique de la matrice
    map_matrix = calloc(1, sizeof(int *) * SIZE_MAP);
    for (int y = 0; y < SIZE_MAP; y++) {
        map_matrix[y] = calloc(1, sizeof(int) * SIZE_MAP);
    }

    // generation de la carte
    if (!map_generator(map_matrix)) {
        printf("La génération de la carte à raté.\n");
    }

    // on libère l'espace utilisé
    for (int y = 0; y < SIZE_MAP; y++) {
        free(map_matrix[y]);
    }
    free(map_matrix);
    return 0;
}
