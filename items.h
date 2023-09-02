#include <iostream>
using namespace std;

int randomNumberGenerator(int stop, int start=0){
    //Use the name as a seed for the random generation
    return start + (rand() % (stop - start));
}

enum item_usage_list{
    none=0,
    breakTree,
    breakStone
};

class Item{
    public:
    string name, description;
    char icon;
    Item(){}
    Item(string item_name, char item_icon, string desc=""){
        name = item_name;
        icon = item_icon;
        description=desc;
    }
    virtual void writeDesc(){
        cout << name << ":\n" << description;
        return;
    }
};

class Tool: public Item{
    int usage, durability;
    public:
    Tool(string item_name, char item_icon,
    string desc,int item_usage=none){
        name = item_name;
        icon = item_icon;
        usage = item_usage;
        description = desc;
    }
    void writeDesc(){
        cout << name << ": [" << usage << "]\n" << description;
        return;
    }
};

class Edible: public Item{
    int usage, durability;
    public:
    Edible(string item_name, char item_icon,
    string desc,int item_usage=none){
        name = item_name;
        icon = item_icon;
        usage = item_usage;
        description = desc;
    }
    void writeDesc(){
        cout << name << ": [" << usage << "]\n" << description;
        return;
    }
};

class InventoryItem{
    public:
    Item* item;
    int amount;
    InventoryItem(Item* inv_item, int inv_amount){
        item=inv_item;
        amount=inv_amount;
    }
};

Item* item_templates[]={
    new Item("None", '-'),                        // empty
    new Item("Stick", '/', "My favourite weapon"),
    new Item("Wood", 'U', "Basic building material"),
    new Item("Flint", 'd', "Looks sharp enough to make some tools"),
	new Edible("Yumberry", '8', "Juicy"),
    new Tool("Axe", 'P', "AAAA", breakTree)
};