#include "inventory.h"
#include "movement.h"

//On crée une forntion pour ajouter des objects à l'inventaire
void add_inventory(Case_inventory inventory[],Object_inventory item){
    for(int i=2;i<=SIZE_INVENTORY;i++){
        //si on trouve un case vide dans l'inventaire, on ajoute l'object ramassé 
        if(inventory[i].Objet==OBJECT_NULL){
            inventory[i].Objet=item;
            inventory[i].amount++;
            return;
        }
        //Si on trouve une pile d'object non complète, on ajoute un au nobre d'objects
        else if (inventory[i].Objet==item|| inventory[i].amount<SIZE_SLOT) 
        {
            inventory[i].amount++;
        }
        //Si ces conditions ne sont pas remplies, alors l'inventaire est plein et l'object est détruit 
        else
        {
        break;
        }
    }
}

//Fonction permettant de retirer des object
void remove_inventory(Case_inventory inventory[], int n ){
    //on vérifie au cas où que on ne traite pas une des valeurs vie, temps ou points
    if (n<2){
        if (inventory[n].Objet-1<=0){
            inventory[n].Objet=OBJECT_NULL;
            inventory[n].amount=0;
        }
        else{
            inventory[n].Objet--;
        }
    }
    else{}
}
void remove_health(Case_inventory inventory[]){
    if (inventory[HEALTH_SLOT].amount-1<=0){
        //partie terminée
    }
    else{
        inventory[HEALTH_SLOT].amount--;
    }
}
void add_xp(Case_inventory inventory[],int amount){
    inventory[POINT_SLOT].amount=inventory[POINT_SLOT].amount+amount;
}
void remove_time(Case_inventory inventory[]){
    inventory[TIME_SLOT].amount=inventory[TIME_SLOT].amount-1;
}
//On veut déplacer le curseur de l'inventaire, vers la gauche, avec en entrée l'inventaire et la position du curseur
void inventory_left(Case_inventory inventory[], int* n){
    inventory[*n].Curseur=0;
    if (*(n-1)<=3){
        inventory[SIZE_INVENTORY].Curseur=1;
    }
    else{
         inventory[*n-1].Curseur=1;
    }    
}
// on vide tout le tableau de l'inventaire
void purge_inventory(Case_inventory inventory[]){
    for(int i=0;i<SIZE_INVENTORY ;i++ ){
        inventory[i].amount=0;
        inventory[i].Objet=0;
        }
    }
//On veut déplacer le curseur de l'inventaire, vers la droite, avec en entrée l'inventaire et la position du curseur
void inventory_right(Case_inventory inventory[], int* n){
    inventory[*n].Curseur=0;
    if (*(n+1)>SIZE_INVENTORY){
        inventory[4].Curseur=1;
    }
    else{
        inventory[*n+1].Curseur=1;
    }
}