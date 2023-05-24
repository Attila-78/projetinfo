#include <inventory.h>
//On crée une forntion pour ajouter des objects à l'inventaire
void add_inventory(Case_inventory inventory[],Object_inventory item){
    for(int i=2;i<=SIZE_INVENTORY;i++){
        if(inventory[i].Objet==OBJECT_NULL){
            inventory[i].Objet=item;
            inventory[i].amount++;
            return;
        }
        else if (inventory[i].Objet==item|| inventory[i].amount<SIZE_SLOT) 
        {
            inventory[i].amount++;
        }
        else
        {
        break;
        }
    }
}

//Fonction permettant de retirer des object
void remove_inventory(Case_inventory inventory[], int n ){
    if (inventory[n].Objet-1<=0){
        inventory[n].Objet=OBJECT_NULL;
    }
    else{
        inventory[n].Objet--;
    }

}

void inventory_left(){



}
void inventory_right(){




}