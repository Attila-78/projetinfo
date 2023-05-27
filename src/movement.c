#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "map.h"
#include "inventory.h"

// fonction qui amène la variable à 100 lorsque celle ci est <0 et qui l'amène à 0 lorsque celle ci est >100
int equilibre(int n)
{
    if (n < 0)
    {
        n = (SIZE_MAP - n) % SIZE_MAP;
    }
    else if (n >= 100)
    {
        n = n % SIZE_MAP;
    }
    return n;
}

// mouvement vers la gauche prend en entrée la carte, la position horizontale(x) et la position verticale(y) ainsi que l'entitée qui doit se déplacer, l'orientation
void movement_LEFT(Cell map[SIZE_MAP][SIZE_MAP], int pos_x, int pos_y, Case_inventory inventory[])
{
    Cell_Content entity = map[pos_y][pos_x].content;
    /*
    x: gauche droite
    y: haut bas
    0:0 ->100:100
    |
    V   y:x
    */
    // permet d'aller à l'index de la case
    switch (map[pos_y][equilibre(pos_x - 1)].content)
    {
    case CONTENT_MONSTER:
        /* le personnage doit prendre des dégats, mais si c'est un monstre qui va dans un autre monstre, le premier bloque le deuxième */
        if (entity == CONTENT_MONSTER)
        {
            return;
        }
        else if (entity == CONTENT_CRATE)
        {
            map[pos_y][equilibre(pos_x - 1)].content = 0;
        }
        else
        {
            // prendre des dégats
            remove_health(inventory);
        }
        break;
    case CONTENT_FLOWER:
        /* le personnage doit ramasser les fleurs*/
        add_inventory(inventory, OBJECT_FLOWER_YELLOW);
        break;
        // le personnage saute cet obstable, et va donc se déplacer de deux cases au lieu d'une seule. si c'est un caisse qui se déplace, alors elle casse la barrière
    case CONTENT_FENCE:
        if (entity == CONTENT_CRATE)
        {
            map[pos_y][equilibre(pos_x - 1)].content = map[pos_y][pos_x].content;
            map[pos_y][equilibre(pos_x)].content = CONTENT_NOTHING;
            add_xp(inventory, 50);
        }
        else if (map[pos_y][equilibre(pos_x - 2)].content == CONTENT_ROCK || map[pos_y][equilibre(pos_x - 2)].content == CONTENT_PNJ)
        {
            return;
        }
        else
        {
            map[pos_y][equilibre(pos_x - 2)].content = map[pos_y][pos_x].content;
            map[pos_y][equilibre(pos_x)].content = CONTENT_NOTHING;
            add_xp(inventory, 10);
            break;
        }
    case CONTENT_ROCK:
        remove_health(inventory);
        add_xp(inventory, -50);
        break;
        /* le personnage est bloqué */
    case CONTENT_CRATE:
        /* le personnage doir pousser la caisse , on va donc appeler la fonction pour la case de la caisse */
        if (map[pos_y][equilibre(pos_x - 1)].content == CONTENT_MONSTER)
        {
            add_xp(inventory, 200);
            add_inventory(inventory, OBJECT_SKULL);
        }
        movement_LEFT(map, pos_x - 1, pos_y, inventory);
        // dans ce ce cas check si la caisse peut bouger dans cette dite direction
        break;
    case CONTENT_HERO:
        remove_health(inventory);
        break;
    case CONTENT_PNJ:
        /*Si c'est le héro qui se déplace, alors on a une zone de texte qui donne la quête, si c'est un monstre, on a rien */
        if (entity == CONTENT_HERO)
        {
            remove_time(inventory);
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

void movement_RIGHT(Cell map[SIZE_MAP][SIZE_MAP], int pos_x, int pos_y, Case_inventory inventory[])
{
    Cell_Content entity = map[pos_y][pos_x].content;
    switch (map[pos_y][equilibre(pos_x + 1)].content)
    {
    case CONTENT_MONSTER:
        /* le personnage doit prendre des dégats, mais si c'est un monstre qui va dans un autre monstre, le premier bloque le deuxième */
        if (entity == CONTENT_MONSTER)
        {
            return;
        }
        else if (entity == CONTENT_CRATE)
        {
            map[pos_y][pos_x + 1].content = 0;
        }
        else
        {
            // prendre des dégats
            remove_health(inventory);
            add_xp(inventory, -50);
        }
        break;
    case CONTENT_FLOWER:
        /* le personnage doit ramasser les fleurs*/
        add_inventory(inventory, OBJECT_FLOWER_YELLOW);
        add_xp(inventory, 25);
        break;
        // le personnage saute cet obstable, et va donc se déplacer de deux cases au lieu d'une seule. si c'est un caisse qui se déplace, alors elle casse la barrière
    case CONTENT_FENCE:
        if (entity == CONTENT_CRATE)
        {
            map[pos_y][equilibre(pos_x + 1)].content = map[pos_y][pos_x].content;
            map[pos_y][equilibre(pos_x)].content = CONTENT_NOTHING;
            add_xp(inventory, 50);
        }
        else if (map[pos_y][equilibre(pos_x + 2)].content == CONTENT_ROCK || map[pos_y][equilibre(pos_x + 2)].content == CONTENT_PNJ)
        {
            return;
        }
        else
        {
            map[pos_y][equilibre(pos_x + 2)].content = map[pos_y][pos_x].content;
            map[pos_y][equilibre(pos_x)].content = CONTENT_NOTHING;
            add_xp(inventory, 10);
            break;
        }
    case CONTENT_ROCK:
        remove_health(inventory);
        break;
        /* le personnage est bloqué */
    case CONTENT_CRATE:
        /* le personnage doir pousser la caisse , on va donc appeler la fonction pour la case de la caisse */
        if (map[pos_y][equilibre(pos_x + 1)].content == CONTENT_MONSTER)
        {
            add_xp(inventory, 200);
            add_inventory(inventory, OBJECT_SKULL);
        }
        movement_RIGHT(map, pos_x + 1, pos_y, inventory);
        // dans ce ce cas check si la caisse peut bouger dans cette dite direction
        break;
    case CONTENT_HERO:
        remove_health(inventory);
        break;
    case CONTENT_PNJ:
        /*Si c'est le héro qui se déplace, alors on a une zone de texte qui donne la quête, si c'est un monstre, on a rien */
        if (entity == CONTENT_HERO)
        {
            remove_time(inventory);
        }
        else
        {
            return;
        }
        break;

        // Déplacement normal, si on arrive au bord de l'espace de jeu, l'entitée est placée à l'opposé de la carte
    default:
        map[pos_y][equilibre(pos_x + 1)].content = map[pos_y][pos_x].content;
        map[pos_y][equilibre(pos_x)].content = CONTENT_NOTHING;
        break;
    }
}

void movement_UP(Cell map[SIZE_MAP][SIZE_MAP], int pos_x, int pos_y, Case_inventory inventory[])
{
    Cell_Content entity = map[pos_y][pos_x].content;
    switch (map[equilibre(pos_y - 1)][pos_x].content)
    {
    case CONTENT_MONSTER:
        /* le personnage doit prendre des dégats, mais si c'est un monstre qui va dans un autre monstre, le premier bloque le deuxième */
        if (entity == CONTENT_MONSTER)
        {
            return;
        }
        else if (entity == CONTENT_CRATE)
        {
            map[equilibre(pos_y - 1)][pos_x].content = 0;
        }
        else
        {
            // prendre des dégats
            remove_health(inventory);
        }
        break;
    case CONTENT_FLOWER:
        /* le personnage doit ramasser les fleurs*/
        add_inventory(inventory, OBJECT_FLOWER_YELLOW);
        break;
        // le personnage saute cet obstable, et va donc se déplacer de deux cases au lieu d'une seule. si c'est un caisse qui se déplace, alors elle casse la barrière
    case CONTENT_FENCE:
        if (entity == CONTENT_CRATE)
        {
            map[equilibre(pos_y - 1)][pos_x].content = map[pos_y][pos_x].content;
            map[pos_y][equilibre(pos_x)].content = CONTENT_NOTHING;
            add_xp(inventory, 50);
        }
        else if (map[equilibre(pos_y - 2)][equilibre(pos_x)].content == CONTENT_ROCK || map[equilibre(pos_y - 2)][pos_x].content == CONTENT_PNJ)
        {
            return;
        }
        else
        {
            map[equilibre(pos_y - 2)][equilibre(pos_x)].content = map[pos_y][pos_x].content;
            map[pos_y][equilibre(pos_x)].content = CONTENT_NOTHING;
            add_xp(inventory, 10);
            break;
        }
    case CONTENT_ROCK:
        remove_health(inventory);
        break;
        /* le personnage est bloqué */
    case CONTENT_CRATE:
        /* le personnage doir pousser la caisse , on va donc appeler la fonction pour la case de la caisse */
        if (map[equilibre(pos_y - 1)][equilibre(pos_x)].content == CONTENT_MONSTER)
        {
            add_xp(inventory, 200);
            add_inventory(inventory, OBJECT_SKULL);
        }
        movement_UP(map, pos_x, pos_y - 1, inventory);
        // dans ce ce cas vérifie si la caisse peut bouger dans cette dite direction
        break;
    case CONTENT_HERO:
        remove_health(inventory);
        break;
    case CONTENT_PNJ:
        /*Si c'est le héro qui se déplace, alors on a une zone de texte qui donne la quête, si c'est un monstre, on a rien */
        if (entity == CONTENT_HERO)
        {
            remove_time(inventory);
        }
        else
        {
            return;
        }
        break;

        // Déplacement normal, si on arrive au bord de l'espace de jeu, l'entitée est placée à l'opposé de la carte
    default:
        map[equilibre(pos_y - 1)][pos_x].content = map[pos_y][pos_x].content;
        map[pos_y][equilibre(pos_x)].content = CONTENT_NOTHING;
        break;
    }
}
// déplacement ver le bas
void movement_DOWN(Cell map[SIZE_MAP][SIZE_MAP], int pos_x, int pos_y, Case_inventory inventory[])
{
    Cell_Content entity = map[pos_y][pos_x].content;
    switch (map[equilibre(pos_y + 1)][pos_x].content)
    {
    case CONTENT_MONSTER:
        /* le personnage doit prendre des dégats, mais si c'est un monstre qui va dans un autre monstre, le premier bloque le deuxième */
        if (entity == CONTENT_MONSTER)
        {
            return;
        }
        else if (entity == CONTENT_CRATE)
        {
            map[equilibre(pos_y + 1)][pos_x].content = 0;
        }
        else
        {
            // prendre des dégats
            remove_health(inventory);
        }
        break;
    case CONTENT_FLOWER:
        /* le personnage doit ramasser les fleurs*/
        add_inventory(inventory, OBJECT_FLOWER_YELLOW);
        break;
        // le personnage saute cet obstable, et va donc se déplacer de deux cases au lieu d'une seule. si c'est un caisse qui se déplace, alors elle casse la barrière
    case CONTENT_FENCE:
        if (entity == CONTENT_CRATE)
        {
            map[equilibre(pos_y + 1)][pos_x].content = map[pos_y][pos_x].content;
            map[pos_y][equilibre(pos_x)].content = CONTENT_NOTHING;
            add_xp(inventory, 50);
        }
        else if (map[equilibre(pos_y + 2)][equilibre(pos_x)].content == CONTENT_ROCK || map[equilibre(pos_y + 2)][pos_x].content == CONTENT_PNJ)
        {
            return;
        }
        else
        {
            map[equilibre(pos_y + 2)][equilibre(pos_x)].content = map[pos_y][pos_x].content;
            map[pos_y][equilibre(pos_x)].content = CONTENT_NOTHING;
            add_xp(inventory, 10);
            break;
        }
    case CONTENT_ROCK:
        remove_health(inventory);
        break;
        /* le personnage est bloqué */
    case CONTENT_CRATE:
        /* le personnage doir pousser la caisse , on va donc appeler la fonction pour la case de la caisse */
        if (map[equilibre(pos_y - 1)][equilibre(pos_x)].content == CONTENT_MONSTER)
        {
            add_xp(inventory, 200);
            add_inventory(inventory, OBJECT_SKULL);
        }
        movement_UP(map, pos_x, pos_y - 1, inventory);
        // dans ce ce cas vérifie si la caisse peut bouger dans cette dite direction
        break;
    case CONTENT_HERO:
        remove_health(inventory);
        break;
    case CONTENT_PNJ:
        /*Si c'est le héro qui se déplace, alors on a une zone de texte qui donne la quête, si c'est un monstre, on a rien */
        if (entity == CONTENT_HERO)
        {
            remove_time(inventory);
        }
        else
        {
            return;
        }
        break;

        // Déplacement normal, si on arrive au bord de l'espace de jeu, l'entitée est placée à l'opposé de la carte
    default:
        map[equilibre(pos_y + 1)][pos_x].content = map[pos_y][pos_x].content;
        map[pos_y][equilibre(pos_x)].content = CONTENT_NOTHING;
        break;
    }
}