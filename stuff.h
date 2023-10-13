#include "tiles.h"
using namespace std;

bool youWannaKeepGaming = 1,
     isPlayerInNewChunk = 0;
char gameViewMode = 1;
unsigned char current_selected_item;

hash<string> seed;

class Chunk
    //5 TILES + UNIQUE ID
{
    public:
        unsigned int id;
        Tile* stage[5];


        Chunk(unsigned int chunk_id){
            id=chunk_id;
            for(int i=0; i<5; i++)
                stage[i] = nullptr;
        }
    

    ~Chunk(){ debug(((string)"Chunk " + to_string(id) + (string)" has been deleted.\n")); }
};

class Human: public NamePrinter
    //CHARACTER YOU MOVE AS IN GAME
{
    enum moving_direction: bool{
        m_left=true,
        m_right=false
    };
    public:
        string name;
        int stage_pos=2, selected_item=0;
        unsigned int chunk_pos=0;
        InventoryItem* backpack[8];
        string layers[3];
        Human(string human_nick="Ann", InventoryItem* human_inv[]=nullptr){
            layers[0] = nothing;
            layers[1] = ".o.";
            layers[2] = "_x_";
            //human_selected=selected_item;
            name = human_nick;
            for(int i=0; i<8; i++){
                if(human_inv == nullptr)
                    backpack[i] = nullptr;
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


        const bool pickup_item(const Item* item)
        {
            backpack[1] = new InventoryItem(item, 1);
            return true;
        }


        ~Human(){ debug(((string)"Human named \"" + name + (string)"\" has been deleted.\n")); }
};



Human* const player = new Human();
Human* humans[]={player};
vector<Chunk> chunks;
Chunk* current_chunk = new Chunk(0);
int player_seed = seed(player->name);