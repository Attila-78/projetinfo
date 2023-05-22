#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/SDL.h"
#include "map.h"

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
        return;
    }
}

int **map_generate()
{
    // allocation dynamique de la matrice
    int **map = calloc(1, sizeof(int *) * SIZE_MAP);
    for (int line = 0; line < SIZE_MAP; line++)
    {
        map[line] = calloc(1, sizeof(int) * SIZE_MAP);
    }

    int min, max;
    // generation aléatoire de la carte
    for (int line = 0; line < SIZE_MAP; line++)
    {
        for (int column = 0; column < SIZE_MAP; column++)
        {
            if (column == 0 && line == 0)
            {
                // on génère un type de case pour la première case du tableau
                map[line][column] = rand() % CELL_AMOUNT + 1;
            }
            else if (line == 0)
            {
                // génération pour une case si il n'y a aucune case au dessus
                map[line][column] = map[line][column - 1] + random_sign(map[line][column - 1]) * (rand() % EPSILON);
            }
            else if (column == 0)
            {
                // génération pour une case si il n'y a aucune case à gauche
                map[line][column] = map[line - 1][column] + random_sign(map[line - 1][column]) * (rand() % EPSILON);
            }
            else
            {
                // comme avant, même ligne et en haut
                // impossible de trouver une valeur +/- epsilon pour remplir notre objectif
                if (abs(map[line - 1][column] - map[line][column - 1]) > EPSILON)
                {
                    map[line][column] = (map[line - 1][column] + map[line][column - 1]) / 2;
                }
                else
                {
                    // ici oui, donc on prends la valeur minimale et on ajoute rand()%EPSILON
                    if (map[line - 1][column] > map[line][column - 1])
                    {
                        min = map[line][column - 1];
                        max = map[line - 1][column];
                    }
                    else
                    {
                        min = map[line - 1][column];
                        max = map[line][column - 1];
                    }

                    if (max == min)
                    {
                        map[line][column] = map[line - 1][column] + (rand() % 2 ? 1 : -1) * (rand() % EPSILON);
                    }
                    else
                    {
                        // on choisis de façon aléatoire où l'on applique epsilon
                        if (rand() % 2)
                        {
                            map[line][column] = max - rand() % EPSILON;
                        }
                        else
                        {
                            map[line][column] = min + rand() % EPSILON;
                        }
                    }
                }
            }

            // on borne nos nombres
            clamp(0, CELL_AMOUNT, &map[line][column]);

            // affichage
            printf("%d ", map[line][column]);
        }
    }
}

Cell **map_generate_cell()
{
    // allocation dynamique de la matrice
    Cell **map = calloc(1, sizeof(Cell *) * SIZE_MAP);
    for (int line = 0; line < SIZE_MAP; line++)
    {
        map[line] = calloc(1, sizeof(Cell) * SIZE_MAP);
    }

    int min, max;
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

            // affichage
            printf("%d ", map[line][column].type);
        }
    }
}

// fonction générant la carte aléatoirement et l'affichant
int map_renderer(int **map)
{
    // on vérifie que le pointeur n'est pas nul pour être sûr qu'il n'y ai pas de segmentation fault
    if (map == NULL)
    {
        return false;
    }

    // définition des variables :
    int line_position = 50;
    int column_position = 50;

    // controls animation loop
    int close = 0;

    // speed of box
    int speed = 300;

    // La fonction SDL_Init permettant d'intialiser SDL retourne 0 en cas de succès, donc si elle ne renvoie pas 0 on renvoie un message d'erreur
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    // créer une fenêtre de jeu "Cy-Valley"
    SDL_Window *win = SDL_CreateWindow("Cy-Valley",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOW_FULLSCREEN_DESKTOP, SDL_WINDOW_FULLSCREEN_DESKTOP, SDL_WINDOW_ALLOW_HIGHDPI);

    // Crée un message d'erreur si la fenêtre ne c'est pas bien crée
    if (win == NULL)
    {
        printf("Couldn't create window: %s", SDL_GetError());
        return 1;
    }

    // déclenche le programme qui contrôle les hardwares graphiques et définit les flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    // crée un moteur de rendu qui permettra d'afficher nos images
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);

    // les surfaces que l'on va ici définir représentent les cases que nous afficherons à l'écran :
    // comme nous afficherons une matrice de 3x3, il nous faut une surface par case; huit pour celle sur les cotés et une pour
    // le personnage au centre
    SDL_Surface *surface_up_left_cell;
    SDL_Surface *surface_up_middle_cell;
    SDL_Surface *surface_up_right_cell;
    SDL_Surface *surface_left_middle_cell;
    SDL_Surface *surface_character;
    SDL_Surface *surface_left_down_cell;
    SDL_Surface *surface_down_middle_cell;
    SDL_Surface *surface_down_right_cell;
    SDL_Surface *surface_right_middle_cell;

    //on crée les rectangles dans lesquels nos surfaces iront
    SDL_Rect *rect_up_left_cell = (400,400,800,800);
    SDL_Rect *rect_up_middle_cell = (1200,400,800,800);
    SDL_Rect *rect_up_right_cell = (2000,400,800,800);
    SDL_Rect *rect_left_middle_cell = (400,1200,800,800);
    SDL_Rect *rect_left_down_cell = (400,2000,800,800);
    SDL_Rect *rect_middle_cell = (1200,1200,800,800);
    SDL_Rect *rect_down_middle_cell = (1200,2000,800,800);
    SDL_Rect *rect_down_right_cell = (2000,2000,800,800);
    SDL_Rect *rect_right_middle_cell = (2000,1200,800,800);

    //on assigne nos surfaces aux rectangles correspondant
    int SDL_BlitSurface(surface_up_left_cell, NULL, surface_up_left_cell, rect_up_left_cell);
    int SDL_BlitSurface(surface_up_middle_cell, NULL, surface_up_middle_cell, rect_up_middle_cell);
    int SDL_BlitSurface(surface_up_right_cell, NULL, surface_up_right_cell, rect_up_right_cell);
    int SDL_BlitSurface(surface_left_middle_cell, NULL, surface_left_middle_cell, rect_left_middle_cell);
    int SDL_BlitSurface(surface_character, NULL, surface_character, rect_middle_cell);
    int SDL_BlitSurface(surface_left_down_cell, NULL, surface_left_down_cell, rect_left_down_cell);
    int SDL_BlitSurface(surface_down_middle_cell, NULL, surface_down_middle_cell, rect_down_middle_cell);
    int SDL_BlitSurface(surface_down_right_cell, NULL, surface_down_right_cell, rect_down_right_cell);
    int SDL_BlitSurface(rect_right_middle_cell, NULL, rect_right_middle_cell, rect_right_middle_cell);

    // on crée ensuite une surface pour chaque< sprite que l'on pourra afficher. On remplacera les surfaces précédemment citées
    // par celle-ci selon l'emplacement du personnage pour éviter
    // de devoir les charger à chaque fois et perdre du temps
    SDL_Surface *surface_character_front_first_step = SDL_LoadBMP("./resources/Main-Character front first step.bmp");
    SDL_Surface *surface_character_front_second_step = SDL_LoadBMP("./resources/Main-Character front second step.bmp");
    SDL_Surface *surface_character_front_third_step = SDL_LoadBMP("./resources/Main-Character front third step.bmp");
    SDL_Surface *surface_character_left_first_step = SDL_LoadBMP("./resources/Main-Character left first step.bmp");
    SDL_Surface *surface_character_left_second_step = SDL_LoadBMP("./resources/Main-Character left second step.bmp");
    SDL_Surface *surface_character_left_third_step = SDL_LoadBMP("./resources/Main-Character left third step.bmp");
    SDL_Surface *surface_character_right_first_step = SDL_LoadBMP("./resources/Main-Character right first step.bmp");
    SDL_Surface *surface_character_right_second_step = SDL_LoadBMP("./resources/Main-Character right second step.bmp");
    SDL_Surface *surface_character_right_third_step = SDL_LoadBMP("./resources/Main-Character right third step.bmp");
    SDL_Surface *surface_character_back_first_step = SDL_LoadBMP("./resources/Main-Character back first step.bmp");
    SDL_Surface *surface_character_back_second_step = SDL_LoadBMP("./resources/Main-Character back second step.bmp");
    SDL_Surface *surface_character_back_third_step = SDL_LoadBMP("./resources/Main-Character back third step.bmp");
    SDL_Surface *surface_Cell_Grass = SDL_LoadBMP("./resources/Cell_Grass.bmp");
    SDL_Surface *surface_Cell_Dirt = SDL_LoadBMP("./resources/Cell_Dirt.bmp");
    SDL_Surface *surface_Cell_Water = SDL_LoadBMP("./resources/Cell_Water.bmp");
    SDL_Surface *surface_Cell_Snow = SDL_LoadBMP("./resources/Cell_Snow.bmp");
    SDL_Surface *surface_Cell_Rock = SDL_LoadBMP("./resources/Cell_Rock.bmp");
    SDL_Surface *surface_Cell_Sand = SDL_LoadBMP("./resources/Cell_Sand.bmp");
    SDL_Surface *surface_Cell_Mud = SDL_LoadBMP("./resources/Cell_Mud.bmp");
    SDL_Surface *surface_Cell_Magma = SDL_LoadBMP("./resources/Cell_Magma.bmp");
  
    // on vérifie que nos sprites ont été chargés sans encombre
    if (surface_character_front_first_step == NULL)
    {
        printf("Couldn't load surface_character_front_first_step\n");
        exit(1);
    }
    if (surface_character_front_second_step == NULL)
    {
        printf("Couldn't load surface_character_front_second_step\n");
        exit(1);
    }
    if (surface_character_front_third_step == NULL)
    {
        printf("Couldn't load surface_character_front_third_step\n");
        exit(1);
    }
    if (surface_character_left_first_step == NULL)
    {
        printf("Couldn't load surface_character_left_first_step");
        exit(1);
    }
    if (surface_character_left_second_step == NULL)
    {
        printf("Couldn't load surface_character_left_second_step\n");
        exit(1);
    }
    if (surface_character_left_third_step == NULL)
    {
        printf("Couldn't load surface_character_left_third_step\n");
        exit(1);
    }
    if (surface_character_right_first_step == NULL)
    {
        printf("Couldn't load surface_character_right_first_step\n");
        exit(1);
    }
    if (surface_character_right_second_step == NULL)
    {
        printf("Couldn't load surface_character_right_second_step\n");
        exit(1);
    }
    if (surface_character_right_third_step == NULL)
    {
        printf("Couldn't load surface_character_right_third_step\n");
        exit(1);
    }
    if (surface_character_back_first_step == NULL)
    {
        printf("Couldn't load surface_character_back_first_step\n");
        exit(1);
    }
    if (surface_character_back_second_step == NULL)
    {
        printf("Couldn't load surface_character_back_second_step\n");
        exit(1);
    }
    if (surface_character_back_third_step == NULL)
    {
        printf("Couldn't load surface_character_back_third_step\n");
        exit(1);
    }
    if (surface_Cell_Grass == NULL)
    {
        printf("Couldn't load surface_Cell_Grass\n");
        exit(1);
    }
    if (surface_Cell_Dirt == NULL)
    {
        printf("Couldn't load surface_Cell_Dirt\n");
        exit(1);
    }
    if (surface_Cell_Water == NULL)
    {
        printf("Couldn't load surface_Cell_Water\n");
        exit(1);
    }
    if (surface_Cell_Snow == NULL)
    {
        printf("Couldn't load surface_Cell_Snow\n");
        exit(1);
    }
    if (surface_Cell_Rock == NULL)
    {
        printf("Couldn't load surface_Cell_Rock\n");
        exit(1);
    }
    if (surface_Cell_Sand == NULL)
    {
        printf("Couldn't load surface_Cell_Sand\n");
        exit(1);
    }
    if (surface_Cell_Mud == NULL)
    {
        printf("Couldn't load surface_Cell_Mud\n");
        exit(1);
    }
    if (surface_Cell_Magma == NULL)
    {
        printf("Couldn't load surface_Cell_Magma\n");
        exit(1);
    }

    // On commence par la case en haut à gauche : on remplace la surface y correspondant par la case  qui s'y trouve relativement à la position du personnage
    if (map[line_position - 1][column_position - 1] == 0)
    {
        surface_up_left_cell = surface_Cell_Grass;
    }
    else if (map[line_position - 1][column_position - 1] == 1)
    {
        surface_up_left_cell = surface_Cell_Dirt;
    }
    else if (map[line_position - 1][column_position - 1] == 2)
    {
        surface_up_left_cell = surface_Cell_Water;
    }
    else if (map[line_position - 1][column_position - 1] == 3)
    {
        surface_up_left_cell = surface_Cell_Snow;
    }
    else if (map[line_position - 1][column_position - 1] == 4)
    {
        surface_up_left_cell = surface_Cell_Rock;
    }
    else if (map[line_position - 1][column_position - 1] == 5)
    {
        surface_up_left_cell = surface_Cell_Sand;
    }
    else if (map[line_position - 1][column_position - 1] == 6)
    {
        surface_up_left_cell = surface_Cell_Mud;
    }
    else
    {
        surface_up_left_cell = surface_Cell_Magma;
    }

    // de même pour la case à gauche
    if (map[line_position][column_position - 1] == 0)
    {
        surface_left_middle_cell = surface_Cell_Grass;
    }
    else if (map[line_position][column_position - 1] == 1)
    {
        surface_left_middle_cell = surface_Cell_Dirt;
    }
    else if (map[line_position][column_position - 1] == 2)
    {
        surface_left_middle_cell = surface_Cell_Water;
    }
    else if (map[line_position][column_position - 1] == 3)
    {
        surface_left_middle_cell = surface_Cell_Snow;
    }
    else if (map[line_position][column_position - 1] == 4)
    {
        surface_left_middle_cell = surface_Cell_Rock;
    }
    else if (map[line_position][column_position - 1] == 5)
    {
        surface_left_middle_cell = surface_Cell_Sand;
    }
    else if (map[line_position][column_position - 1] == 6)
    {
        surface_left_middle_cell = surface_Cell_Mud;
    }
    else
    {
        surface_left_middle_cell = surface_Cell_Magma;
    }

    // de même pour la case en bas à gauche
    if (map[line_position + 1][column_position - 1] == 0)
    {
        surface_left_down_cell = surface_Cell_Grass;
    }
    else if (map[line_position + 1][column_position - 1] == 1)
    {
        surface_left_down_cell = surface_Cell_Dirt;
    }
    else if (map[line_position + 1][column_position - 1] == 2)
    {
        surface_left_down_cell = surface_Cell_Water;
    }
    else if (map[line_position + 1][column_position - 1] == 3)
    {
        surface_left_down_cell = surface_Cell_Snow;
    }
    else if (map[line_position + 1][column_position - 1] == 4)
    {
        surface_left_down_cell = surface_Cell_Rock;
    }
    else if (map[line_position + 1][column_position - 1] == 5)
    {
        surface_left_down_cell = surface_Cell_Sand;
    }
    else if (map[line_position + 1][column_position - 1] == 6)
    {
        surface_left_down_cell = surface_Cell_Mud;
    }
    else
    {
        surface_left_down_cell = surface_Cell_Magma;
    }

    // de même pour la case en bas
    if (map[line_position + 1][column_position] == 0)
    {
        surface_down_middle_cell = surface_Cell_Grass;
    }
    else if (map[line_position + 1][column_position] == 1)
    {
        surface_down_middle_cell = surface_Cell_Dirt;
    }
    else if (map[line_position + 1][column_position] == 2)
    {
        surface_down_middle_cell = surface_Cell_Water;
    }
    else if (map[line_position + 1][column_position] == 3)
    {
        surface_down_middle_cell = surface_Cell_Snow;
    }
    else if (map[line_position + 1][column_position] == 4)
    {
        surface_down_middle_cell = surface_Cell_Rock;
    }
    else if (map[line_position + 1][column_position] == 5)
    {
        surface_down_middle_cell = surface_Cell_Sand;
    }
    else if (map[line_position + 1][column_position] == 6)
    {
        surface_down_middle_cell = surface_Cell_Mud;
    }
    else
    {
        surface_left_middle_cell = surface_Cell_Magma;
    }

    // de même pour la case en bas à droite
    if (map[line_position + 1][column_position + 1] == 0)
    {
        surface_down_right_cell = surface_Cell_Grass;
    }
    else if (map[line_position + 1][column_position + 1] == 1)
    {
        surface_down_right_cell = surface_Cell_Dirt;
    }
    else if (map[line_position + 1][column_position + 1] == 2)
    {
        surface_down_right_cell = surface_Cell_Water;
    }
    else if (map[line_position + 1][column_position + 1] == 3)
    {
        surface_down_right_cell = surface_Cell_Snow;
    }
    else if (map[line_position + 1][column_position + 1] == 4)
    {
        surface_down_right_cell = surface_Cell_Rock;
    }
    else if (map[line_position + 1][column_position + 1] == 5)
    {
        surface_down_right_cell = surface_Cell_Sand;
    }
    else if (map[line_position + 1][column_position + 1] == 6)
    {
        surface_down_right_cell = surface_Cell_Mud;
    }
    else
    {
        surface_left_middle_cell = surface_Cell_Magma;
    }

    // de même pour la case à droite
    if (map[line_position][column_position + 1] == 0)
    {
        surface_right_middle_cell = surface_Cell_Grass;
    }
    else if (map[line_position][column_position + 1] == 1)
    {
        surface_right_middle_cell = surface_Cell_Dirt;
    }
    else if (map[line_position][column_position + 1] == 2)
    {
        surface_right_middle_cell = surface_Cell_Water;
    }
    else if (map[line_position][column_position + 1] == 3)
    {
        surface_right_middle_cell = surface_Cell_Snow;
    }
    else if (map[line_position][column_position + 1] == 4)
    {
        surface_right_middle_cell = surface_Cell_Rock;
    }
    else if (map[line_position][column_position + 1] == 5)
    {
        surface_right_middle_cell = surface_Cell_Sand;
    }
    else if (map[line_position][column_position + 1] == 6)
    {
        surface_right_middle_cell = surface_Cell_Mud;
    }
    else
    {
        surface_right_middle_cell = surface_Cell_Magma;
    }

    // de même pour la case en haut à droite
    if (map[line_position - 1][column_position + 1] == 0)
    {
        surface_up_right_cell = surface_Cell_Grass;
    }
    else if (map[line_position - 1][column_position + 1] == 1)
    {
        surface_up_right_cell = surface_Cell_Dirt;
    }
    else if (map[line_position - 1][column_position + 1] == 2)
    {
        surface_up_right_cell = surface_Cell_Water;
    }
    else if (map[line_position - 1][column_position + 1] == 3)
    {
        surface_up_right_cell = surface_Cell_Snow;
    }
    else if (map[line_position - 1][column_position + 1] == 4)
    {
        surface_up_right_cell = surface_Cell_Rock;
    }
    else if (map[line_position - 1][column_position + 1] == 5)
    {
        surface_up_right_cell = surface_Cell_Sand;
    }
    else if (map[line_position - 1][column_position + 1] == 6)
    {
        surface_up_right_cell = surface_Cell_Mud;
    }
    else
    {
        surface_up_right_cell = surface_Cell_Magma;
    }

    // de même pour la case en haut
    if (map[line_position - 1][column_position] == 0)
    {
        surface_up_middle_cell = surface_Cell_Grass;
    }
    else if (map[line_position - 1][column_position] == 1)
    {
        surface_up_middle_cell = surface_Cell_Dirt;
    }
    else if (map[line_position - 1][column_position] == 2)
    {
        surface_up_middle_cell = surface_Cell_Water;
    }
    else if (map[line_position - 1][column_position] == 3)
    {
        surface_up_middle_cell = surface_Cell_Snow;
    }
    else if (map[line_position - 1][column_position] == 4)
    {
        surface_up_middle_cell = surface_Cell_Rock;
    }
    else if (map[line_position - 1][column_position] == 5)
    {
        surface_up_middle_cell = surface_Cell_Sand;
    }
    else if (map[line_position - 1][column_position] == 6)
    {
        surface_up_middle_cell = surface_Cell_Mud;
    }
    else
    {
        surface_up_middle_cell = surface_Cell_Magma;
    }

    if (surface_character == NULL)
    {
        printf("Couldn't load surface: %s", SDL_GetError());
        return 1;
    } 
    

    // charge l'image dans notre mémoire graphique
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surface_character);

    // efface les surfaces utilisées
    SDL_FreeSurface(surface_character);
    SDL_FreeSurface(surface_left_down_cell);
    SDL_FreeSurface(surface_left_middle_cell);
    SDL_FreeSurface(surface_up_left_cell);
    SDL_FreeSurface(surface_up_middle_cell);
    SDL_FreeSurface(surface_up_right_cell);
    SDL_FreeSurface(surface_right_middle_cell);
    SDL_FreeSurface(surface_down_right_cell);
    SDL_FreeSurface(surface_down_middle_cell);

    SDL_FreeSurface(surface_Cell_Grass);
    SDL_FreeSurface(surface_Cell_Dirt);
    SDL_FreeSurface(surface_Cell_Water);
    SDL_FreeSurface(surface_Cell_Snow);
    SDL_FreeSurface(surface_Cell_Rock);
    SDL_FreeSurface(surface_Cell_Sand);
    SDL_FreeSurface(surface_Cell_Mud);
    SDL_FreeSurface(surface_Cell_Magma);

    SDL_FreeSurface(surface_character_front_first_step);
    SDL_FreeSurface(surface_character_front_second_step);
    SDL_FreeSurface(surface_character_front_third_step);
    SDL_FreeSurface(surface_character_left_first_step);
    SDL_FreeSurface(surface_character_left_second_step);
    SDL_FreeSurface(surface_character_left_third_step);
    SDL_FreeSurface(surface_character_right_first_step);
    SDL_FreeSurface(surface_character_right_second_step);
    SDL_FreeSurface(surface_character_right_third_step);
    SDL_FreeSurface(surface_character_back_first_step);
    SDL_FreeSurface(surface_character_back_second_step);
    SDL_FreeSurface(surface_character_back_third_step);

    // let us control our image position
    // so that we can move it with our keyboard.
    SDL_Rect dest;

    // connects our texture with dest to control position
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    // adjust height and width of our image box.
    dest.w /= 6;
    dest.h /= 6;

    // sets initial x-position of object
    dest.x = (1000 - dest.w) / 2;

    // sets initial y-position of object
    dest.y = (1000 - dest.h) / 2;

    // on définit ici la réaction du programme quand le joueur appuie sur une touche.
    while ((close) != true)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {

            case SDL_QUIT:
                // On ferme sdl si on reçoit l'instruction de quitter sdl
                close = 1;
                break;

            case SDL_KEYDOWN:
                // enregistre l'API pour le clavier selon la touche enfoncée,
                switch (event.key.keysym.scancode)
                {
                // si le joueur appuie sur z ou la flèche du haut
                case SDL_SCANCODE_Z:
                case SDL_SCANCODE_UP:
                    break;
                // si le joueur appuie sur q ou la flèche de gauche
                case SDL_SCANCODE_Q:
                case SDL_SCANCODE_LEFT:
                    surface_character = SDL_LoadBMP("./resources/Main-Character left first step.bmp");
                    column_position--;
                    clamp(0, SIZE_MAP, &column_position);
                    sleep(0.2);
                    surface_character = SDL_LoadBMP("./resources/Main-Character left second step.bmp");
                    column_position--;
                    clamp(0, SIZE_MAP, &column_position);
                    sleep(0.2);
                    surface_character = SDL_LoadBMP("./resources/Main-Character left third step.bmp");
                    column_position--;
                    clamp(0, SIZE_MAP, &column_position);
                    sleep(0.2);
                    break;
                // si le joueur appuie sur s ou la flèche du bas
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    surface_character = SDL_LoadBMP("./resources/Main-Character front first step.bmp");
                    line_position++;
                    clamp(0, SIZE_MAP, &line_position);
                    sleep(0.2);
                    surface_character = SDL_LoadBMP("./resources/Main-Character front second step.bmp");
                    line_position++;
                    clamp(0, SIZE_MAP, &line_position);
                    sleep(0.2);
                    surface_character = SDL_LoadBMP("./resources/Main-Character front third step.bmp");
                    line_position++;
                    clamp(0, SIZE_MAP, &line_position);
                    sleep(0.2);
                    break;
                // si le joueur appuie sur d ou la flèche de droite
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    surface_character = SDL_LoadBMP("./resources/Main-Character right first step.bmp");
                    column_position++;
                    clamp(0, SIZE_MAP, &column_position);
                    sleep(0.2);
                    surface_character = SDL_LoadBMP("./resources/Main-Character right second step.bmp");
                    column_position++;
                    clamp(0, SIZE_MAP, &column_position);
                    sleep(0.2);
                    surface_character = SDL_LoadBMP("./resources/Main-Character right third step.bmp");
                    column_position++;
                    clamp(0, SIZE_MAP, &column_position);
                    sleep(0.2);
                    break;
                // si le joueur appuie sur x ou échap
                case SDL_SCANCODE_X:
                case SDL_SCANCODE_ESCAPE:
                    close = 1;
                    break;
                default:
                    break;
                }
            }
        }

        // right boundary
        if (dest.x + dest.w > WIDTH)
            dest.x = 1000 - dest.w;

        // left boundary
        if (dest.x < 0)
            dest.x = 0;

        // bottom boundary
        if (dest.y + dest.h > HEIGHT)
            dest.y = 1000 - dest.h;

        // upper boundary
        if (dest.y < 0)
            dest.y = 0;

        // clears the screen
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, tex, NULL, &dest);

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }

    // détruit
    SDL_DestroyTexture(tex);

    // détruit le rendu
    SDL_DestroyRenderer(rend);

    // ferme la fenêtre de jeu
    SDL_DestroyWindow(win);

    // ferme sdl
    SDL_Quit();
}
