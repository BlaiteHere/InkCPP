#include "stuff.h"
#include "maths.h"
using namespace std;

class Inventory
{
    public:
    InventoryItem* m_inventory[defaultInventorySize];


    Inventory() 
    { 
        for(int i=0; i<8; i++)
            m_inventory[i] = new InventoryItem;
    }
};



class Entity: public NamePrinter
{
    public:
    char entity_type='e';
    ThreeLayerDrawable render;
    mutable bool direction;


    Entity() { name = "DefaultEntity"; }


    Entity(
        const string e_name,
        const char layerone[4], 
        const char layertwo[4], 
        const char layerthree[4],
        const bool e_dir=false
    ):
        direction(e_dir), 
        render(ThreeLayerDrawable(layerone, layertwo, layerthree))
    {
        name = e_name;
    }
};



class Human: public Entity
    //CHARACTER YOU MOVE AS IN GAME
{
    public:
    mutable char stage_pos=2,
                 selected_item=0;
    mutable unsigned int chunk_pos=0;
    mutable Inventory backpack;


    Human(const string human_nick="Ann")//, InventoryItem* human_inv[] = nullptr)
    {
        entity_type='h';
        render = ThreeLayerDrawable(" O ", "/V\\", "_A_");
        direction = false;
        name = human_nick;
    }

    const void move(const bool moveTo) const
    {
        direction = moveTo;

        if(moveTo)
        {
            if(stage_pos == 0)
            {
                stage_pos = oneChunkSize-1;
                chunk_pos--;

                isPlayerInNewChunk=true;
            } else 
                stage_pos--;

        } else
        {
            if(stage_pos == oneChunkSize-1)
            {
                stage_pos=0;
                chunk_pos++;
                isPlayerInNewChunk=true;
            } else 
                stage_pos++;
        }
        return;
    }


    const bool addItemToInv (const Item* item) const
    {
        for(int i=0; i<8; i++)
            if (backpack.m_inventory[i]->item == nullptr)
            {
                backpack.m_inventory[i] = new InventoryItem(item, 1);
                return 0;
            } else if (backpack.m_inventory[i]->item == item) {
                backpack.m_inventory[i]->amount++;
                return 0;
            }
        return 1;
    }


    const bool pickup_item(const Item* item) const
    {
        return addItemToInv(item);
    }


    const void useItem(const int selected_inv_space) const
    {
        backpack.m_inventory[selected_inv_space]->amount--;

        if (backpack.m_inventory[selected_inv_space]->amount == 0)
            backpack.m_inventory[selected_inv_space]->item = nullptr;

        return;
    }


    ~Human(){ debug(((string)"Human named \"" + name + (string)"\" has been deleted.\n")); }
};



Entity* const entity_templates = 
{
    new Entity(
        "Silly tutel",
        " _ ",
        "/#a",
        "n~n"
    )
};

Human* const player = new Human();
Human* const humans[]={player};

vector<Entity*> entities;
int player_seed = seed(player->name);