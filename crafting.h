#include "items.h"
using namespace std;


class Recipe: public Printer {
    public:
    string name;
    InventoryItem* elements[3];
    InventoryItem* outcome;

    
    Recipe(
        string recipename,
        InventoryItem* recipe_outcome,
        InventoryItem* elementone,
        InventoryItem* elementtwo = NULL,
        InventoryItem* elementthree = NULL){

        name = recipename;
        elements[0] = elementone;
        elements[1] = elementtwo;
        elements[2] = elementthree;
    }

    void render();

    string print() {
        return name;
    }
};


void Recipe::render(){
    int amount_of_elements = 0;

    //Count the amount of elements in the recipe
    for(int i=0; i<3; i++)
        if(elements[i] == NULL) break;
        else amount_of_elements++;

    //Render recipe
    cout << name << '\n';
    for(int i=0; i<amount_of_elements; i++){
        cout << elements[i]->item->name;

        if(i != amount_of_elements-1)
            cout << " + ";
        else
            cout << " --> ";
    }
    cout << outcome->item->name;

    return;
}


Recipe recipes[] {
    Recipe(
        "Crafting Workstation", 
        new InventoryItem(item_templates[2], 16),
        new InventoryItem(item_templates[2], 16)
    )
};