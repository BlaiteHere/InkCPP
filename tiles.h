#include "crafting.h"
using namespace std;

string nothing="   ";

enum tile_change_to{
    dont_change = 127
};

int loot_tables[][3]={
    {},
    {1, 2, 3}
};


/*class Action{
    public:
    string name="Default action";
    int loot_table[3];
    Action(){}
};*/


class Tile{
    public:
    int change_to;
    string layers[3]={nothing, "ERR", "OR!"};
    string actions[3];
    Item* requires;
    Tile(){}
    Tile(string layerone, string layertwo, string layerthree,
    int tile_change = dont_change, Item* tile_req = NULL, string actionone = nothing, 
    string actiontwo = nothing, string actionthree = nothing){
        layers[0] = layerone;
        layers[1] = layertwo;
        layers[2] = layerthree;
        change_to = tile_change;
        requires = tile_req;
        actions[0]=actionone;
        actions[1]=actiontwo;
        actions[2]=actionthree;
    }
    virtual int interact(){
        cout << "Interacted with object:\n";
        for(int i=0; i<3; i++)
            cout << layers[i] << '\n';
        cout << "No actions to perform.\nWrite 3 to exit.\n";
        return 0;
    }
    virtual Tile* duplicate(){
        return new Tile(layers[0], layers[1], layers[2]);
    }
    virtual Item* get_loot(int action){
        return item_templates[loot_tables[action][rand() % 3]];
    }
};


class Pickup_Tile: public Tile{
    public:
    int loot_table[4];
    Pickup_Tile(string layerone, string layertwo, string layerthree,
    int loot_table_id, int tile_change = dont_change, string actionone = nothing,
    string actiontwo = nothing, string actionthree = nothing){
        layers[0] = layerone;
        layers[1] = layertwo;
        layers[2] = layerthree;
        change_to = tile_change;
        loot_table[0] = loot_table_id; // the id of the loot_table
        actions[0]=actionone;
        actions[1]=actiontwo;
        actions[2]=actionthree;
        for(int i=1; i<4; i++)
            loot_table[i] = loot_tables[loot_table_id][i]; // the loot table
    }
    int interact(){
        int amount_of_actions=0;
        for(int i=0; i<3; i++){
            if(actions[i]==nothing) break;
            amount_of_actions++;
        }

        cout << "Interacted with pickup-tile:\n";
        for(int i=0; i<3; i++){
            cout << layers[i] << '\n';
        }

        cout << "Which action would you like to perform with it?\n";
        for(int i=0; i<amount_of_actions; i++)
            cout << nothing << i << ". " << actions[i] << '\n';

        cout << "\nWrite 3 to exit.\n";
        return amount_of_actions;
    }

    Pickup_Tile* duplicate(){
        return new Pickup_Tile(layers[0], layers[1], layers[2],
        0, change_to, actions[0], actions[1], actions[2]);
    }
};


Tile* tile_templates[]={
    new Tile(nothing, nothing, "___"), // i personally ated. sorry
    new Tile(nothing, nothing, "_v_"), // grass
    new Pickup_Tile(nothing, nothing, "_*_", 1, 0, "Pick up an item", "Don't pick up an item", "Idk what else to add in here."), // item
    new Tile(nothing, " /\\", "//]"),  // rock
    new Pickup_Tile(" ^ ", "/^\\", "^i^", 2, 0, "Chop the tree", "Get leaves")     // tree
};