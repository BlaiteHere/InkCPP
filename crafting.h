#include "items.h"
using namespace std;

class Recipe {
    public:
    string name;
    InventoryItem* elements[3];
    Recipe(
        string recipename,
        InventoryItem* elementone,
        InventoryItem* elementtwo = NULL,
        InventoryItem* elementthree = NULL){

        name = recipename;
        elements[0] = elementone;
        elements[1] = elementtwo;
        elements[2] = elementthree;
    }
};
Recipe recipes[] {
    Recipe("Crafting Workstation", new InventoryItem(item_templates[2], 16))
};