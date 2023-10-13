#include "pure.h"
using namespace std;



/*enum item_usage_list: char 
    //ITEM FUNCTIONALITY
{
    none = 0,
    breakTree,
    breakStone
};
*/



class Item: public NamePrinter, public BasicItem 
    //IT DOES STUFF
{
    public:
    string description;
    char icon;


    Item(){}


    Item(string item_name, char item_icon, string desc="")
    {
        name = item_name;
        icon = item_icon;
        description = desc;
    }


    void writeDesc() const
    {
        cout << name << ":\n" << description;
        return;
    }


    void use() const { return; } //wip


    ~Item(){ debug(((string)"Item " + print() + (string)" has been deleted.\n")); }
};



class Tool: public Item {
    //IT DESTROY STUFF
    public:
    int usage, durability;


    Tool(string item_name, char item_icon,
    string desc)
    {
        name = item_name;
        icon = item_icon;
        description = desc;
    }


    void writeDesc() const
    {
        cout << name << ": [" << usage << "]\n" << description;
        return;
    }


    ~Tool(){ debug(((string)"Tool " + print() + (string)" has been deleted.\n")); }
};



class Consumable: public Item 
    //YUM, will be probably replaced by Tool since it is the same
{
    public:
    int usage, durability;


    Consumable(string item_name, char item_icon,
    string desc)
    {
        name = item_name;
        icon = item_icon;
        description = desc;
    }


    void writeDesc() const
    {
        cout << name << ": [" << usage << "]\n" << description;
        return;
    }


    ~Consumable(){ debug(((string)"Consumable " + print() + (string)" has been deleted.\n")); }
};



class ItemTile: public Item
    //NO CLUE WHAT IS THIS FOR. I WILL DELETE THIS IN THE NEXT COMMIT PROBABLY
{
    public:
    int usage, durability;


    ItemTile(string item_name, char item_icon,
    string desc){
        name = item_name;
        icon = item_icon;
        description = desc;
    }


    void writeDesc() const
    {
        cout << name << ": [" << usage << "]\n" << description;
        return;
    }


    ~ItemTile(){ debug(((string)"ItemTile " + print() + (string)" has been deleted.\n")); }
};



class InventoryItem
    //ITEM FOUND IN THE INVENTORY (WITH AMOUNT OF ITSELF)
{
    public:
    Item* item;
    int amount;

    
    InventoryItem(Item* inv_item, int inv_amount)
    {
        item=inv_item;
        amount=inv_amount;
    }


    InventoryItem(const Item* inv_item, int inv_amount)
    {
        item = (Item*)inv_item;
        amount = inv_amount;
    }


    ~InventoryItem(){ debug(((string)"InventoryItem " + item->print() + (string)" has been deleted.\n")); }
};



const Item* item_templates[] =
{
    //ALL ITEMS IN THE GAME ARE STORED HERE
    new Item("None", '-'),                        // empty
    new Item("Stick", '/', "My favourite weapon"),
    new Item("Wood", 'U', "Basic building material"),
    new Item("Flint", 'd', "Looks sharp enough to make some tools"),
	new Consumable("Yumberry", '8', "Juicy"),
	new ItemTile("Basic Workstation", '^', "You can craft more advanced items with it"),
    new Tool("Axe", 'P', "Breaks trees")
};