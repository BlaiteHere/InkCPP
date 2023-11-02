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
    const char entity_type='e';
    ThreeLayerDrawable render;
    bool direction;
    string name;


    Entity() : name("DefaultEntity") {}


    Entity(
        const string e_name,
        const char layerone[4], 
        const char layertwo[4], 
        const char layerthree[4],
        const bool e_dir=false
    ) 
        : name(e_name), 
        direction(e_dir), 
        render(ThreeLayerDrawable(layerone, layertwo, layerthree))
    {}
};



class Human: public Entity
    //CHARACTER YOU MOVE AS IN GAME
{
    public:
    const char entity_type='h';
    char stage_pos=2,
            selected_item=0;
    unsigned int chunk_pos=0;
    Inventory backpack;
    string name;


    Human(const string human_nick="Ann")//, InventoryItem* human_inv[] = nullptr)
    : name(human_nick)
    {
        render = ThreeLayerDrawable(" O ", "/V\\", " A ");
        direction = false;
    }

    void move(const bool moveTo)
    {
        if(moveTo)
        {
            if(stage_pos == 0)
            {
                stage_pos=4;
                chunk_pos--;

                isPlayerInNewChunk=true;
            } else stage_pos--;
            direction = false;
        } else {
            if(stage_pos == oneChunkSize-1)
            {
                stage_pos=0;
                chunk_pos++;
                isPlayerInNewChunk=true;
            } else stage_pos++;
            direction = true;
        }
        return;
    }


    const bool pickup_item(const Item* item)
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
        return 1;   // inventory full
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