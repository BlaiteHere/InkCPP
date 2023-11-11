#include "tiles.h"
using namespace std;

bool youWannaKeepGaming = 1,
     isPlayerInNewChunk = 0;
char gameViewMode = 1;
unsigned char current_selected_item;
const int oneChunkSize = 16;
const char defaultInventorySize=8;
string recent_action = nothing;
hash<string> seed;
unsigned int chunks_vector_size=0;


class Chunk
    //[oneChunkSize] TILES + UNIQUE ID
{
    public:
    unsigned int id;
    //Tile* stage[oneChunkSize];

    shared_ptr<Tile> stage[5];


    Chunk(const unsigned int chunk_id = 0)
    {
        id = chunk_id;
        for(int i=0; i<5; i++)
            stage[i] = nullptr;
    }


    ~Chunk()
    {
        //for(int i=0; i<oneChunkSize; i++) delete stage[i];

        debug(
            ((string)"Chunk " + to_string(id) + (string)" has been deleted.\n")
        );
    }
};





//vector<Chunk> chunks; make em pointy uwu \/\/\/\/
shared_ptr<vector<Chunk*>> chunks = std::make_shared<vector<Chunk*>>();
Chunk myChunk;
Chunk* current_chunk = &myChunk;