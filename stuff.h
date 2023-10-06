#include <vector>
#include "pure.h"
#include "tiles.h"
using namespace std;

bool youWannaKeepGaming=true;
bool areYouDebugging=false;
bool isPlayerInNewChunk=false;
int gameViewMode = 1;
unsigned int current_selected_item;

hash<string> seed;
enum moving_direction: bool{
    m_left=true,
    m_right=false
};

class Chunk
{
    public:
        unsigned int id;
        Tile* stage[5];


        Chunk(unsigned int chunk_id){
            id=chunk_id;
            for(int i=0; i<5; i++)
                stage[i] = NULL;
        }
};

class Human: public Printer
{
    public:
        string name;
        int stage_pos=2, selected_item=0;
        unsigned int chunk_pos=0;
        Item* backpack[8];
        string layers[3];
        Human(string human_nick="Ann", Item* human_inv[]=NULL){
            layers[0] = nothing;
            layers[1] = ".o.";
            layers[2] = "_x_";
            //human_selected=selected_item;
            name = human_nick;
            for(int i=0; i<8; i++){
                if(human_inv == nullptr)
                    backpack[i] = NULL;
                else 
                    backpack[i] = human_inv[i];
            }
            return;
        }


        void move(bool moveTo){
            if(moveTo){
                if(stage_pos == 0){
                    stage_pos=4;
                    chunk_pos--;
                    isPlayerInNewChunk=true;
                } else stage_pos--;
            
            } else {
                if(stage_pos == 4){
                    stage_pos=0;
                    chunk_pos++;
                    isPlayerInNewChunk=true;
                } else stage_pos++;
            }
            return;
        }


        void pickup_item(Item* item){
            backpack[0]=item;
        }


        string print() {
            return name;
        }
};


Item* free_cool_inventory[]={
    new Tool("Pickaxe", 'T', "Say Gex", breakStone),
    new Item("Gummy bear", 'x', "Yum yummies in our tummies.")
};

Human* player = new Human();//, free_cool_inventory);
Human* humans[]={player};
vector<Chunk> chunks;
Chunk* current_chunk = new Chunk(0);
int player_seed = seed(player->name);