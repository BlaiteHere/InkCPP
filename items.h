/*
    Legend:
    Item:
        - can't be used
        - material
    Tool
        - can be used
        - used only `max_amount` times
    Consumable:
        - can be used
        - used only `max_amount` times
        - use grants stats
    ItemTile:
        - can be used
        - use builds the structure in the tile
*/

#include "pure.h"
using namespace std;



class BasicItem: public NamePrinter
{
    //FUNCTIONS FOR ITEM(s)
    virtual const void writeDesc() const = 0;
};



class Item: public BasicItem 
    //IT DOES STUFF, usually material
{
public:
    string description;
    char icon;
    char type;
    int max_amount;


    Item() = default;


    Item(
        string item_name, const char item_icon,
        string desc = "No description",
        const int maximum_item_amount = 16
    ):
        description(desc), icon(item_icon), 
        max_amount(maximum_item_amount),
        type('i')
    {
        name = item_name;
    }


    const void writeDesc() const
    {
        cout << '[' << icon << "] | " << name << ": " << description;
        return;
    }


    ~Item(){ debug(((string)"Item " + name + (string)" has been deleted.\n")); }
};



class Tool: public Item 
{
    //IT DESTROY STUFF
public:
    Tool(
        string item_name, const char item_icon,
        string desc="", const int maximum_item_durability=16
    ){
        description = desc;
        icon = item_icon;
        max_amount = maximum_item_durability;
        name = item_name;
        type = 't';
    }

    ~Tool(){ debug(((string)"Tool " + print() + (string)" has been deleted.\n")); }
};



class Consumable: public Item 
    //YUM, will be probably replaced by Tool since it is the same
{
public:
    Consumable(
        string item_name, const char item_icon,
        string desc="", const int maximum_item_amount=16
    )
    {
        description = desc;
        icon = item_icon;
        max_amount = maximum_item_amount;
        name = item_name;
        type = 'c';
    }

    ~Consumable(){ debug(((string)"Consumable " + print() + (string)" has been deleted.\n")); }
};



class ItemTile: public Item
    //NO CLUE WHAT IS THIS FOR. I WILL DELETE THIS IN THE NEXT COMMIT PROBABLY
{
public:
    char tileToChange;


    ItemTile(
        string item_name, const char item_icon, char item_tileToChange,
        string desc="", const int maximum_item_amount=16
    ): tileToChange(item_tileToChange)
    {
        description = desc;
        icon = item_icon;
        max_amount = maximum_item_amount;
        name = item_name;
        type = 'T';
    }

    ~ItemTile(){ debug(((string)"ItemTile " + print() + (string)" has been deleted.\n")); }
};



class InventoryItem
    //ITEM FOUND IN THE INVENTORY (WITH AMOUNT OF ITSELF)
{
    public:
    Item* item;
    int amount;

    
    InventoryItem(Item* inv_item=nullptr, int inv_amount=0)
    {
        item=inv_item;
        amount=inv_amount;
    }


    InventoryItem(const Item* inv_item, const int inv_amount)
    {
        item = (Item*)inv_item;
        amount = inv_amount;
    }


    ~InventoryItem(){ debug(((string)"InventoryItem " + item->print() + (string)" has been deleted.\n")); }
};



const Item* const item_templates[] =
{
    //ALL ITEMS IN THE GAME ARE STORED HERE
    new Item(
        "None", '-'
    ),
    new Item(
        "Stick", '/', "My favourite weapon"
    ),
    new Item(
        "Wood", 'U', "Basic building material"
    ),
    new Item(
        "Flint", 'd', "Looks sharp enough to make some tools"
    ),
	new Consumable(
        "Yumberry", '8', "Juicy sweetness in your jaw"
    ),
	new ItemTile(
        "Basic Workbench", '^', 0, "You can craft more advanced items with it"
    ),
    new Tool(
        "Axe", 'P', "Breaks trees"
    ),
    new Item(
        "Leaf", 'U', "Flat pieces of plant from the tree"
    ),
    new Consumable(
        "Airnut", 'o', "Hard on the outside, sweet on the inside"
    ),
    new ItemTile(
        "Portable building", 'A', 5, "A portable machinery"
    )
};