#include "action.h"

using namespace std;

const char nothing[] = "   ";

enum tile_change_to: char {
    dont_change = 127
};


class Tile: public NamePrinter
{
    public:
    ThreeLayerDrawable render;


    Tile() { name = "Error"; }


    Tile(string layerone, string layertwo, string layerthree, string tilename)
    {
        render = ThreeLayerDrawable(layerone, layertwo, layerthree);

        name = tilename;
    }

    
    /*
    Tile(Tile& other)
    {
        other.name = name;
    }
    */


    virtual const Item* getActionReq(int action_index) const
    // Returns action's requirement item index (item_templates[])
    {
        return nullptr;
    }


    virtual int interact() const
    // Interaction screen render
    {
        cout << "Interacted with " << name << ":\n";
        for(int i=0; i<3; i++)
            cout << render.layers[i] << '\n';
        cout << "No actions to perform.\nWrite 3 to exit.\n";
        return 0;
    }


    virtual Tile* clone() const
    // Returns a heap ptr to a new tile of the same arguments
    {
        return new Tile(render.layers[0], render.layers[1], render.layers[2], name);
    }   // idk how to program this without ids


    virtual const char getTileToChange(const int input=dont_change) const
    // Returns what the tile should change to 
    // (index in item_teplates[])
    // 127 = don't change
    { 
        return input;
    }


    virtual const Item* getLoot(const int input=0) const
    // Returns loot from the action
    {
        return (const Item*)(item_templates[0]);
    }
};


class Action_Tile: public Tile{
    public:
    Action* actions[3];


    Action_Tile(
        string layerone, string layertwo, string layerthree, string tilename,
        Action* actionone, Action* actiontwo=nullptr, Action* actionthree=nullptr
    )
    {
        render = ThreeLayerDrawable(layerone, layertwo, layerthree);

        actions[0] = actionone;
        actions[1] = actiontwo;
        actions[2] = actionthree;
        name = tilename;
    }


    int interact() const
    {
        //Count the amount of actions
        int amount_of_actions = 0;
        for(int i=0; i<3; i++)
        {
            if(actions[i] == nullptr) break;
            amount_of_actions++;
        }

        //Print the interacted Tile
        cout << "Interacted with " << name << ":\n";
        for(int i=0; i<3; i++)
            cout << render.layers[i] << '\n';

        cout << "\nWhich action would you like to perform with it?\n";
        for(int i=0; i<amount_of_actions; i++)
        {
            cout << "\tWrite " << i+1 << " for [" << actions[i]->name << "]";
    
            if (actions[i]->requiredItem != nullptr)
            {
                cout << " (requires: ";
                actions[i]->requiredItem->writeDesc();
                cout << ')';
            }

            cout << '\n';
        }
        return amount_of_actions;
    }


    Action_Tile* clone() const
    {
        return new Action_Tile(
            render.layers[0], render.layers[1], render.layers[2], 
            name, actions[0], actions[1], actions[2]
        );
    }


    const char getTileToChange(const char input=127) const
    // Returns what the tile should change to
    // (index in item_teplates[])
    {
        if(input==127) return 127;

        return actions[input]->tileToChange;
    }


    const Item* getLoot(const int input=0) const
    // Returns loot from the action
    {
        return (const Item*)(actions[input]->getItemFromThis);
    }


    const Item* getActionReq(int action_index) const
    // Returns action's requirement item index (item_templates[])
    {
        return actions[action_index]->requiredItem;
    }
};


const Tile* tile_templates[] = {
    new Tile(nothing, nothing, "___", "an empty tile"),
    new Tile(nothing, nothing, "_v_", "a grass patch"),
    new Action_Tile(
        nothing, nothing, "_*_", 
        "an item on the ground",
        &action_templates[1]
    ),
    new Tile(
        nothing, " /\\", "//]", 
        "a rock"
    ),
    new Action_Tile
    (
        " ^ ", "/^\\", "^i^",
        "a tree",
        &action_templates[2],
        &action_templates[3],
        &action_templates[4]
    ),
    new Action_Tile(
        "/^\\", "[o]", "o-o", 
        "Portable building",
        &action_templates[5]
    ),
    new Action_Tile(
        " _ ", "/o\\", "[_]", 
        "Chest",
        &action_templates[6],
        &action_templates[7]
    )
};
