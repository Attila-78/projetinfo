#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/SDL.h"
#include "map.h"

// fonction qui amène la variable à 100 lorsque celle ci est <0 et qui l'amène à 0 lorsque celle ci est >100
int equilibre(int n){
    if (n<0){
        n=SIZE_MAP-n;
    }
    else if(n>100){
        n=n%SIZE_MAP;
    }
    return n;
}

// mouvement vers la gauche prend en entrée la carte, la position horizontale(x) et la position verticale(y) ainsi que l'entitée qui doit se déplace
void movement_LEFT(Cell **map, int pos_x, int pos_y, Cell_Content entity, int *quete, Cell_Orientation *orientation)
{
    // le personnage s'oriente dans la direction où il va
    *orientation = ORIENTATION_LEFT;
    /*
    x: gauche droite
    y: haut bas
    0:0 ->100:100
    |
    V   y:x
    */
    // permet d'aller à l'index de la case
    if (map[pos_y][(pos_x - 1 < 0) ? SIZE_MAP - pos_x - 1 : pos_x - 1].type == CELL_WATER)
    {
        return;
    }
    else
        switch (map[pos_y][(pos_x - 1 < 0) ? SIZE_MAP - pos_x - 1 : pos_x - 1].content)
        {
        case CONTENT_MONSTER:
            /* le personnage doit prendre des dégats, mais si c'est un monstre qui va dans un autre monstre, le premier bloque le deuxième */
            if (entity == CONTENT_MONSTER){
                return;
            }
            else{
                // prendre des dégats
            }
            break;
        case CONTENT_FLOWER:
            /* le personnage doit se déplacer normalement, et ramasser les fleurs*/
            break;
            // le personnage saute cet obstable, et va donc se déplacer de deux cases au lieu d'une seule. si c'est un caisse qui se déplace, alors elle casse la barrière
        case CONTENT_FENCE:
            if (entity==CONTENT_CRATE){
                map[pos_y][equilibre(pos_x - 1)].content = map[pos_y][pos_x].content;
                map[pos_y][equilibre(pos_x)].content = CONTENT_NOTHING;
            }
            else if (map[pos_y][equilibre(pos_x - 2)].content==CONTENT_ROCK || map[pos_y][equilibre(pos_x - 2)].content==CONTENT_PNJ )
            {
                return;
            }
        case CONTENT_ROCK:
            break;
            /* le personnage est bloqué */
        case CONTENT_CRATE:
            /* le personnage doir pousser la caisse , on va donc appeler la fonction pour la case de la caisse */
            movement_LEFT(map, pos_x - 1, pos_y, CONTENT_CRATE, quete, 0);
            // dans ce ce cas check si la caisse peut bouger dans cette dite direction
            break;
        case CONTENT_HERO:
            /*le personnage doit prendre des dégats, car le monstre l'attaque */
            break;
        case CONTENT_PNJ:
            /*Si c'est le héro qui se déplace, alors on a une zone de texte qui donne la quête, si c'est un monstre, on a rien */
            if (entity == CONTENT_HERO && *quete == false)
            {
                *quete = true;
            }
            else
            {
                return;
            }
            break;

// Déplacement normal, si on arrive au bord de l'espace de jeu, l'entitée est placée à l'opposé de la carte 
        default: 
            map[pos_y][equilibre(pos_x - 1)].content = map[pos_y][pos_x].content;
            map[pos_y][equilibre(pos_x)].content = CONTENT_NOTHING;
            break;
        }
    }

void movement_RIGHT() {}

void movement_UP() {}

void movement_DOWN() {}
