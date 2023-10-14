#include "action.h"
using namespace std;

string nothing = "   ";

enum tile_change_to: char {
    dont_change = 127
};


class Tile{
    public:
    string layers[3] = //Basically what is displayed when the
    {                  //          tile is rendered.
        nothing, 
        "ERR", 
        "OR!"
    };


    Tile(){}


    Tile(string layerone, string layertwo, string layerthree)
    {
        layers[0] = layerone;
        layers[1] = layertwo;
        layers[2] = layerthree;
    }


    virtual int interact() const
    // Interaction screen render
    {
        cout << "Interacted with object:\n";
        for(int i=0; i<3; i++)
            cout << layers[i] << '\n';
        cout << "No actions to perform.\nWrite 3 to exit.\n";
        return 0;
    }


    virtual Tile* duplicate()
    // Returns a heap ptr to a new tile of the same arguments
    {
        return this;
    }


    virtual const int change_tile_to(const int input=127) const
    // Returns what the tile should change to 
    // (index in item_teplates[])
    // 127 = don't change
    { 
        return input;
    }


    virtual const Item* get_loot(const int input=0) const
    // Returns loot from the action
    {
        return (const Item*)(item_templates[0]);
    }
};


class Action_Tile: public Tile{
    public:
    Action* actions[3];


    Action_Tile(
        string layerone, string layertwo, string layerthree, 
        Action* actionone, Action* actiontwo=nullptr, Action* actionthree=nullptr
    )
    {
        layers[0] = layerone;
        layers[1] = layertwo;
        layers[2] = layerthree;
        actions[0] = actionone;
        actions[1] = actiontwo;
        actions[2] = actionthree;
    }


    int interact() const
    {
        //Count the amount of actions
        int amount_of_actions = 0;
        for(int i=0; i<3; i++){
            if(actions[i] == nullptr) break;
            amount_of_actions++;
        }

        //Print the interacted Tile
        cout << "Interacted with pickup-tile:\n";
        for(int i=0; i<3; i++)
            cout << layers[i] << '\n';

        cout << "\nWhich action would you like to perform with it?\n";
        for(int i=0; i<amount_of_actions; i++)
            cout << "\tWrite " << i << " for [" << actions[i]->name << "]\n";

        //cout << "\nWrite 3 to exit.\n";
        return amount_of_actions;
    }
    

    Action_Tile* duplicate()
    {
        return this;
    }

    const int change_tile_to(const int input=127) const
    // Returns what the tile should change to 
    // (index in item_teplates[])
    {
        if(input==127) return 127;

        return actions[input]->afterUseChangeTileToThisIndex;
    }


    const Item* get_loot(const int input=0) const
    // Returns loot from the action
    {
        return (const Item*)(actions[input]->getItemFromThis);
    }
};


Tile* tile_templates[]={
    new Tile(nothing, nothing, "___"), // i personally ated. sorry
    new Tile(nothing, nothing, "_v_"), // grass
    new Action_Tile
    (
        nothing, nothing, "_*_", 
        &action_templates[1]
    ), // item
    new Tile(nothing, " /\\", "//]"),  // rock
    new Action_Tile
    (
        " ^ ", "{^}", "^i^",
        &action_templates[2],
        &action_templates[3]
    )     // tree
};