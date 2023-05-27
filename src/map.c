#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "map.h"
#include "movement.h"
#include "input.h"

// fonction donnant la valeur absolue d'un entier x
int abs(int x)
{
    if (x < 0)
    {
        return -x;
    }
    return x;
}

// fonction donnant un signe aléatoire à la valeur donnée
int random_sign(int start)
{
    if (start < EPSILON)
    {
        return 1;
    }
    if (start > CELL_AMOUNT - EPSILON)
    {
        return -1;
    }
    return rand() % 2 ? 1 : -1;
}

// fonction permettant de borner un chiffre entre un min et un max
void clamp(int min, int max, int *num)
{
    if (*num < min)
    {
        *num = min;
        return;
    }
    if (*num > max)
    {

        *num = max;
    }
}

void map_generate_cell(Cell map[SIZE_MAP][SIZE_MAP])
{

    int min, max;
    int line, column;

    // generation aléatoire de la carte
    for (int line = 0; line < SIZE_MAP; line++)
    {
        for (int column = 0; column < SIZE_MAP; column++)
        {
            if (column == 0 && line == 0)
            {
                // on génère un type de case pour la première case du tableau
                map[line][column].type = rand() % CELL_AMOUNT + 1;
            }
            else if (line == 0)
            {
                // génération pour une case si il n'y a aucune case au dessus
                map[line][column].type = map[line][column - 1].type + random_sign(map[line][column - 1].type) * (rand() % EPSILON);
            }
            else if (column == 0)
            {
                // génération pour une case si il n'y a aucune case à gauche
                map[line][column].type = map[line - 1][column].type + random_sign(map[line - 1][column].type) * (rand() % EPSILON);
            }
            else
            {
                // comme avant, même ligne et en haut
                // impossible de trouver une valeur +/- epsilon pour remplir notre objectif
                if (abs(map[line - 1][column].type - map[line][column - 1].type) > EPSILON)
                {
                    map[line][column].type = (map[line - 1][column].type + map[line][column - 1].type) / 2;
                }
                else
                {
                    // ici oui, donc on prends la valeur minimale et on ajoute rand()%EPSILON
                    if (map[line - 1][column].type > map[line][column - 1].type)
                    {
                        min = map[line][column - 1].type;
                        max = map[line - 1][column].type;
                    }
                    else
                    {
                        min = map[line - 1][column].type;
                        max = map[line][column - 1].type;
                    }

                    if (max == min)
                    {
                        map[line][column].type = map[line - 1][column].type + (rand() % 2 ? 1 : -1) * (rand() % EPSILON);
                    }
                    else
                    {
                        // on choisis de façon aléatoire où l'on applique epsilon
                        if (rand() % 2)
                        {
                            map[line][column].type = max - rand() % EPSILON;
                        }
                        else
                        {
                            map[line][column].type = min + rand() % EPSILON;
                        }
                    }
                }
            }

            // on s'assure que le type de la case soit bien entre le min et le max
            clamp(0, CELL_AMOUNT, (int *)(&map[line][column].type));
        }
    }
}

void map_put_content(Cell map[SIZE_MAP][SIZE_MAP])
{
    map[2][2].content = CONTENT_FLOWER;
    for (int x = 0; x < SIZE_MAP; x++)
    {
        for (int y = 0; y < SIZE_MAP; y++)
        {
            // r pour le moment
        }
    }
}

void printmap(Cell map[SIZE_MAP][SIZE_MAP], int x, int y)
{
    int true_x, true_y;

    for (int i = x - PLAYER_VIEW; i <= x + PLAYER_VIEW; i++)
    {
        for (int j = y - PLAYER_VIEW; j <= y + PLAYER_VIEW; j++)
        {
            // vérifie les indices, si ils sont négatifs, prendre l'autre coté de la map
            // si equilibre bug, seg fault
            true_x = equilibre(i);
            true_y = equilibre(j);
            // printf("%d %d", true_x, true_y);
            // platform_sleep(5000);
            switch (map[true_x][true_y].type)
            {
            case CELL_GRASS:
                printf("33[%dm", 34);
                break;
            case CELL_DIRT:
                printf("33[%dm", 130);
                break;
            case CELL_SAND:
                printf("33[%dm", 229);
                break;
            case CELL_WATER:
                printf("33[%dm", 27);
                break;
            }

            // printf 2 char pour que les proportions sur la console en hauteur/largeur soit les meme
            if (true_x == x && true_y == y)
            {
                printf("[H]");
            }
            else
            {
                switch (map[true_x][true_y].content)
                {
                case CONTENT_NOTHING:
                    printf("[ ]");
                    break;
                case CONTENT_HERO:
                    printf("[H]");
                    break;
                case CONTENT_FLOWER:
                    printf("[f]");
                    break;
                case CONTENT_ROCK:
                    printf("[O]");
                    break;
                case CONTENT_CRATE:
                    printf("[K]");
                    break;
                case CONTENT_FENCE:
                    printf("[T]");
                    break;
                case CONTENT_PNJ:
                    printf("[i]");
                    break;
                case CONTENT_MONSTER:
                    printf("[X]");
                    break;
                }
            }
        }
        printf("\n");
    }

    // remet les couleurs par défaut
    printf("33[%dm", 0);
}

// fonction générant la carte aléatoirement et l'affichant
void map_display(Cell map[SIZE_MAP][SIZE_MAP], int *player_x, int *player_y)
{
    // on vérifie que le pointeur n'est pas nul pour être sûr qu'il n'y ai pas de segmentation fault
    if (map == NULL)
    {
        printf("map is null\n");
        exit(0);
    }

    //TODO montre le score, le temps, les pv

    platform_console_clear();
    printmap(map, *player_x, *player_y);

    // printf("\n Saisissez la direction dans laquelle vous voulez aller : z pour en haut, s pour en bas, d pour à droite, q pour à gauche.");
    // char direction = quick_scanf();
    char direction;
    scanf("%c", &direction);
    // modifie la position du joueur
    switch (direction)
    {
    case 'z':
        *player_y = equilibre(*player_y - 1);
        break;
    case 's':
        *player_y = equilibre(*player_y + 1);
        break;
    case 'q':
        *player_x = equilibre(*player_x - 1);
        break;
    case 'd':
        *player_x = equilibre(*player_x + 1);
        break;
    }
}
