#include "tiles.h"
using namespace std;

bool youWannaKeepGaming = 1,
     isPlayerInNewChunk = 0;
char gameViewMode = 1;
unsigned char current_selected_item;
const int oneChunkSize=5;
const char defaultInventorySize=8;
string recent_action = nothing;

hash<string> seed;


class StaticChunkTile
{
    //Index of the tile that is in tile_templates[]
    char tile_index;

    StaticChunkTile(const char c_tileindex)
    {
        tile_index = c_tileindex;
    }
};


class Chunk
    //[oneChunkSize] TILES + UNIQUE ID
{
    public:
    unsigned int id;
    Tile* stage[oneChunkSize];


    Chunk(const unsigned int chunk_id=0)
    {
        id=chunk_id;
        for(int i=0; i<5; i++)
            stage[i] = nullptr;
    }
    

    ~Chunk(){ debug(((string)"Chunk " + to_string(id) + (string)" has been deleted.\n")); }
};





vector<Chunk> chunks;
Chunk* current_chunk = new Chunk();