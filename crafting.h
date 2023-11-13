#include "items.h"
using namespace std;


class Recipe: public NamePrinter {
    public:
    string name;
    const InventoryItem* elements[3];
    const InventoryItem* outcome;

    
    Recipe(
        const string recipename,
        const InventoryItem* recipe_outcome,
        const InventoryItem* elementone,
        const InventoryItem* elementtwo = nullptr,
        const InventoryItem* elementthree = nullptr
        )
    {

        name = recipename;
        elements[0] = elementone;
        elements[1] = elementtwo;
        elements[2] = elementthree;
    }


    void render();


    ~Recipe(){ debug(((string)"Recipe " + name + (string)" has been deleted.\n")); }
};


void Recipe::render(){
    int amount_of_elements = 0;

    //Count the amount of elements in the recipe
    for(int i=0; i<3; i++)
        if(elements[i] == nullptr) break;
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
