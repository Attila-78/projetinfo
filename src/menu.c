#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/SDL.h"
#include "map.h"
#include "inventory.h"


// on retourne au menu principal
void quitterpartie (){




}
void sauvgarderpartie(){
    FILE* sauvegarde

}

// on lance une partie avec le tableau de enregistrerpartie 
void chargerpartie(){
    char save_name[] = "00";
    int save_number = 0;
    FILE * file;
    printf ("choisir votre sauvegarde")
    scanf ("&d", &save_number);
    save_name[0] = save_number / 10;
    save_number[1] = save_number %10;
    file = fopen ("dossier1/sauvegarde" save_name ".txt");
    if (file ==NULL)
    {
        printf("Can't open the save file number %02d", save_number);
        return;
    }
}


int main(){





}

    