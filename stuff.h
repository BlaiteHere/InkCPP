#include "tiles.h"
using namespace std;

bool youWannaKeepGaming = 1,
     isPlayerInNewChunk = 0;
char gameViewMode = 1;
unsigned char current_selected_item;
const int oneChunkSize = 5;
const int defaultInventorySize=8;
string recent_action = nothing;
hash<string> seed;
unsigned int chunks_vector_size = 0;


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


    string debug_msg()
    {
        return "Chunk data found. Loading chunk " + to_string(id) + "...\n";
    }
};





//vector<Chunk> chunks; make em pointy uwu \/\/\/\/
vector<Chunk> chunks;
Chunk current_chunk;