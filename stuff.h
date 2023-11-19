#include "tiles.h"
using namespace std;

bool youWannaKeepGaming = true,
     isPlayerInNewChunk = false;
char gameViewMode = 1;
unsigned char current_selected_item;
const unsigned int oneChunkSize = 16,
                   defaultInventorySize = 32;
string recent_action = nothing;
hash<string> seed;



class Chunk
    //[oneChunkSize] TILES + UNIQUE ID
{
    public:
    mutable unsigned int id;
    mutable const Tile* stage[oneChunkSize];


    Chunk(const unsigned int chunk_id = 0)
    {
        id = chunk_id;
        for(int i=0; i<5; i++)
            stage[i] = nullptr;
    }


    Chunk(const Chunk& other)
    {
        for(int i=0; i<oneChunkSize; i++)
            this->stage[i] = other.stage[i];

        this->id = other.id;
    }


    ~Chunk()
    {
        //for(int i=0; i<oneChunkSize; i++) delete stage[i];

        debug(
            ((string)"Chunk " + to_string(id) + (string)" has been deleted.\n")
        );
    }


    string debug_msg() const
    {
        return "Chunk data found. Loading chunk " + to_string(id) + "...\n";
    }
};





//vector<Chunk> chunks; make em pointy uwu \/\/\/\/
vector<Chunk> chunks;
Chunk current_chunk;