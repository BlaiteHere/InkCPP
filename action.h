#include "crafting.h"
using namespace std;


class Action: public NamePrinter
{
    public:
    string name = "Default action";
    int tileToChange = dont_change;
    Item* getItemFromThis,
        * requiredItem;


    enum tile_change_to: char 
    {
        dont_change = 127
    };


    Action(
        const string a_name="Default action", 
        const Item* a_getItem = nullptr,
        const int a_change_to=dont_change,
        const Item* a_reqItem = nullptr
    )
    {
        name = a_name;
        tileToChange = a_change_to;
        getItemFromThis = (Item*)a_getItem;
        requiredItem = (Item*)a_reqItem;
    }
};



Action action_templates[] =
{
    Action(),
    Action(
        "Pick up an item",
        item_templates[1],
        0
    ),
    Action(
        "Chop the tree",
        item_templates[2],
        0,
        item_templates[6]
    ),
    Action(
        "Get leaves",
        item_templates[7]
    ),
    Action(
        "Get leaves but funnier",
        item_templates[8]
    ),
    Action(
        "Shove the contraption into your inventory",
        item_templates[9],
        0
    ),
    Action(
        "Open the chest",
        item_templates[6],
        0
    ),
    Action(
        "Break the chest for materials",
        item_templates[2],
        0
    ),
    Action(
        "Pet"
    )
};