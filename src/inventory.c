#include <inventory.h>
//On crée une forntion pour ajouter des objects à l'inventaire
void add_inventory(Case_inventory inventory[],Object_inventory item){
    for(int i=3;i<=SIZE_INVENTORY;i++){
        if(inventory[i].Objet==OBJECT_NULL|| inventory[i].amount<=16){
            inventory[i].Objet=item;
            inventory[i].amount++;
        }
        else{
        break;
        }
    }
}

void add_points();

//Fonction permettant de retirer des object
void remove_inventory(){



}

void inventory_left(){



}
void inventory_right(){




}