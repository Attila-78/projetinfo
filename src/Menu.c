#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/SDL.h"
#include "map.h"
#include "inventory.h"


// on retourne au menu principal
void quitterpartie() {




}
void sauvegarderpartie(tab[], Case_inventory inventory[) {
    char save_name[] = "00";
    int save_number = 0;
    FILE* file;
    printf("choisir votre sauvegarde");
    scanf("&d", &save_number);
    save_name[0] = save_number / 10;
    save_number[1] = save_number % 10;
    file = fopen("dossier1/sauvegarde" save_name ".txt");
    for (l = 0; l < 99; l++) {
        for (c = 0; c < 299; c = c + 3) {
            i0 = tab[l][c].type
            i1 = tab[l][c + 1].content
            i2 = tab[l][c + 2].orientation
            int fputc(int i0, FILE * file);
            int fputc(int i1, FILE * file);
            int fputc(int i2, FILE * file);
           
        }
    }
    for (i = 299, i < 331, i=i+2) {
        x= inventory[i].object
        y= inventory[i+1].amount
        int fputc(int x, FILE * file);
        int fputc(int y, FILE * file);
    }
    fclose(file);
  
            if (file == NULL);
        {
            printf("Can't file number %02d", save_number);
                return;
        }
    }

    // on lance une partie avec le tableau de sauvegarderpartie 
    void chargerpartie() {
        char save_name[] = "00";
        int save_number = 0;
        FILE* file;
        printf("choisir votre sauvegarde");
        scanf("&d", &save_number);
        save_name[0] = save_number / 10;
        save_number[1] = save_number % 10;
        file = fopen("dossier1/sauvegarde" save_name ".txt");
        char* fgets(char* chaine, int 30000, FILE * file);
        tab[] = void map_generate_cell(Cell map[SIZE_MAP][SIZE_MAP]);

        if (file == NULL);
        {
            printf("Can't open the save file number %02d", save_number);
            return;
        }
    }


