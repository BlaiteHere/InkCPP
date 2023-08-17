#include <iostream>
#include <vector>
#include "tiles.h"
using namespace std;

bool youWannaKeepGaming=true;
bool areYouDebugging=true;
bool isPlayerInNewChunk=false;
bool gameViewMode=true;
hash<string> seed;
enum moving_direction{
    m_left=true,
    m_right=false
};

class Chunk{
    public:
    unsigned int id;
    Tile* stage[5];
    Chunk(unsigned int chunk_id){
        id=chunk_id;
        for(int i=0; i<5; i++)
            stage[i] = NULL;
    }
};

class Human{
    public:
    string nickname;
    int stage_pos=2, selected_item=0;
    unsigned int chunk_pos=0;
    Item* backpack[8];
    string layers[3];
    Human(string human_nick="Ann", Item* human_inv[]=NULL){
        layers[0] = nothing;
        layers[1] = ".o.";
        layers[2] = "_x_";
        //human_selected=selected_item;
        nickname = human_nick;
        for(int i=0; i<8; i++){
            if(human_inv == nullptr)
                backpack[i] = NULL;
            else backpack[i] = human_inv[i];
        }
    }
    //void select_item(){
    //    if(selected_item == 8) layers[1][2] = '.';
    //    else layers[1][2] = backpack[selected_item]->icon;
    //    return;
    //}
    void move(bool moveTo){
        if(moveTo){
            if(stage_pos == 0){
                stage_pos=4;
                chunk_pos--;
                isPlayerInNewChunk=true;
            }
            else stage_pos--;
        } else {
            if(stage_pos == 4){
                stage_pos=0;
                chunk_pos++;
                isPlayerInNewChunk=true;
            }
            else stage_pos++;
        }
        return;
    }
    void pickup_item(Item* item){
        backpack[0]=item;
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
int player_seed = seed(player->nickname);