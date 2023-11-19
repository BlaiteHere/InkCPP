#include "entity.h"
using namespace std;

char input;
char amount_of_actions = 3;
char selected_inventory_space = 0;


enum gameViewModes: char 
    //ALL RENDER/OUTPUT MODES
{
    inventory_tui,
    actual_game,
    interaction_tui,
    crafting_tui
};


void titleScreen() {
    char key_input;
    const char title_screen[] = {
       "\
   ___  ,    /\\         ___       _   /\\     ^~^       .-~>\n\
  /  :\\ |\\  / :`---.   /   \\ /\\  / ^~' :\\   /  :\\ /\\  /  <_.^.\n\
\\/   ;:V :\\/  ;:  :;\\^/   :;V :\\/  :; :;:\\^/  o :V :\\/   :;  :\\\n\
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\
  ####   ##  ##   ####    #####   #####  ######   ####   ###### \n\
 ##  ##  ##  ##  ##  ##  ##      ##        ##    ##  ##    ##   \n\
 #####   ##  ##  #####   #####    ####     ##    #####     ##   \n\
 ##  ##  ##  ##  ##      ##          ##    ##    ##  ##    ##   \n\
 ##  ##   ####   ##       #####  #####     ##    ##  ##  ###### \n\n\
\t\t\t\t\t\t made by Blaite.\n"
    };
    cout << title_screen << "Press any key to continue...   ";
    cin >> key_input;
    return;
}


void introduction()
    //ASKS FOR THE INK HUMAN NAME, IT IS LATER USED AS THE WORLD SEED
{
    string nameYourInk;

    if(areYouDebugging)
    {
        player->name = "Blaite";
        return;
    }

    cout << "Name your ink. (type \"no\" if you want it to be nameless)\n>>> ";
    cin >> nameYourInk;

    if(nameYourInk!="no")
        player->name = nameYourInk;

    cout << "Welcome to " << player->name << "'s world!" << endl
    << "Write any key to continue...\n";
    cin >> nameYourInk;
    return;
}


void renderBackpack(const Human* const& this_human)
    //RENDERS HUMAN INVENTORY
{
    InventoryItem* this_item;

    cout << this_human->name << "'s Backpack:\n";

    for(int i=0; i<8; i++)
    {
        this_item = this_human->backpack.m_inventory[i];

        if(i == selected_inventory_space)
            cout << " >>> ";
        else
            cout << i+1 << ' ';


        if(this_item->item == nullptr)
            cout << "[ ] | None: ...\n";
        else
        {
            this_item->item->writeDesc();
            cout << " x " << this_item->amount << '\n';
        }
    }
    return;
}


void useSelectedItem(Human* const &this_human, Chunk& this_chunk = current_chunk)
    //DOES use() ON ITEM THAT IS SELECTED WHEN INVENTORY'ING
{
    Item* item = this_human->backpack.m_inventory[selected_inventory_space]->item;

    if(item == nullptr)
        return;

    //Change recent_action dialogue
    if (item->type == 'i')
        recent_action = "Materials can't be used or equiped.";

    else if (item->type == 't')
        recent_action = item->name + " has been equiped.";

    else if (item->type == 'c') 
        recent_action = item->name + " consumed.";

    else if (item->type == 'T') 
        recent_action = item->name + " placed down.";

    else
        recent_action = "Error! How did we get here?";

    //Check Item type and execute what that type should do
    if (item->type == 't' || item->icon == 'w')
        this_human->render.layers[1][2] = item->icon;

    else if (item->type == 'c') 
        this_human->useItem(selected_inventory_space);

    else if (
        item->type == 'T' && 
        this_chunk.stage[this_human->stage_pos] == tile_templates[0]
    )
    {
        ItemTile* item_tile = static_cast<ItemTile*>(item);
        this_chunk.stage[this_human->stage_pos] = tile_templates[item_tile->tileToChange];
        this_human->useItem(selected_inventory_space);
    }

    return;
};


void doTheActions(const Chunk& this_chunk = current_chunk)
// growing trees, moving enemies, etc.
{
    char a;
    //Do the dog
    for(int i=0; i<oneChunkSize; i++){
        a = current_chunk.stage[i]->getType();
        if(a == 'D')
            tile_templates[7]->animateTile();
    }

    return;
}


void startCrafting()
    //RENDERS CRAFTING TUI
{
    recent_action = "Crafting... (jk)";

    return;
}


void PrintChunks()
//Prints chunks vector
{
    cout << "\nCHUNK IDs: ";

    const int chunks_size = chunks.size();
    for(int i=0; i<chunks_size; i++){
        cout << chunks[i].id;
        if(i!=chunks_size-1) cout << ", ";
    }

    cout << ".\n";
    return;
}


void composeChunk(unsigned const int& this_id, Chunk& this_chunk=current_chunk)
//CONSTRUCTS A CHUNK AND RETURNS IT
{
    srand(player_seed + player->chunk_pos);

    string debug_msg;   //DEBUG
    int this_random_number,
        tile_chance_map[] = 
    {
        0,
        1,
        2,
        3,
        4,
        5,
        6,
        0,
        1,
        2,
        3,
        7
    };

    debug("Generating new chunk with random numbers: ");
    for(int i=0; i<oneChunkSize; i++)
    {
        this_random_number = tile_chance_map[randomNumberGenerator(12)];
        debug_msg = to_string(this_random_number) + ", ";//DEBUG
        debug(debug_msg, false);                         //DEBUG
        this_chunk.stage[i] = tile_templates[this_random_number];
    }

    debug("\n", false); //DEBUG
    this_chunk.id = this_id;
    return;
}


void saveChunk(Chunk& this_chunk = current_chunk)
// Saves the chunk to the vector
{
    string debug_msg;
    int my_id;
    const int chunks_size = chunks.size();

    for(int i=0; i<chunks_size; i++)
    {
        my_id = chunks[i].id;

        if(my_id == this_chunk.id)
        {
debug_msg = "Chunk data found. Saving chunk " + to_string(my_id) + "...\n";
            debug(debug_msg);//DEBUG
            chunks.erase(chunks.begin()+i);
            chunks.push_back(this_chunk);
            return;
        }
    }

    debug("Error! Chunk saving failed. Chunk not found.");
    return;
}


void loadChunk(Human* const& this_human = player, Chunk& this_chunk = current_chunk)
//CHECKS IF CHUNK EXISTS, IF IT DOESN'T THEN MAKES ONE WITH composeChunk()
{
    //Search if chunk exists
    const int chunks_size = chunks.size();

    for(int i=0; i<chunks_size; i++)
    {
        if(chunks[i].id == this_human->chunk_pos)
        {
            this_chunk = chunks.at(i);

            debug(this_chunk.debug_msg()); //DEBUG
            return;
        }
    }

    //If not found:
    debug("Chunk data not found. Creating new chunk...\n"); //DEBUG
    composeChunk(this_human->chunk_pos, this_chunk);
    chunks.push_back(this_chunk);
    this_chunk = chunks.back();
    return;
}


void moveTheHuman(const bool moveInThisDirection, Human* const moveThem = player)
//MOVES SPECIFIED HUMAN IN THE PLACE THEY WANNA MOVE
{
    doTheActions();
    moveThem->move(moveInThisDirection);

    if(!isPlayerInNewChunk) return;

    saveChunk();
    loadChunk();
    isPlayerInNewChunk = false;
	return;
}


void change_inventory_selected_space(const bool change_space_left = true)
//CHANGES INVENTORY SELECTED CURSOR SPACE 
//and checks if it's not out of bounds of the array
{
    if(change_space_left)
    {
        if(selected_inventory_space == 0)
            selected_inventory_space = defaultInventorySize-1;

        else selected_inventory_space--;

    } else {
        if(selected_inventory_space == defaultInventorySize-1)
            selected_inventory_space = 0;

        else selected_inventory_space++;
    }
    return;
}


void quitTheGame()
    //ASKS YOU IF YOU'RE SURE TO EXIT 2HE GAME
{
	char answer;
	cout << "Are you sure you want to leave the game? (y/n)\n>>>";
	cin >> answer;

	if(answer=='y' or answer=='Y')
    {
		youWannaKeepGaming = false;
		cout << "See you soon " << player->name << "... ";
		cin >> answer;

	} else 
        cout << "Phew! I thought you were going to leave us...\n";

	return;
}


void povYouDidNothing()
    //POV: NO INPUT
{
	const string youDidNuthin[10] = 
    {
		"Uh oh! You did nothing...   :/",
		"Woopsie daisy! Nothing happened.",
		"Nothing was changed! :/",
		"Bruhh, did you do nothing on purpose just to see this msg??",
		">-< n-nothing was done, user-chan!!~ nya.",
		"But nothing came.",
		">>> [Turn skipped!] >>>",
		"Nothing wasn't done, yesn't?",
		"Heavens! You happened to forget to write down the message!\n> Kinda cringe, innit bruv?",
		"UwU, U-um, *sweats confused* I t-think you might f-f-fowwgot to u-use your keyboawd >///<\n> (pls, kill me)"
	};

	recent_action = youDidNuthin[rand() % 10];
	return;
}


string renderChunk(const Chunk& this_chunk, Human* const players[])
    //RETURNS STRING WITH THE VIEW OF THE GAME SCENE
{
    //Render Tiles to this_canvas array
    string this_canvas[3][oneChunkSize];

    for(int y=0; y<3; y++)
        for(int x=0; x<oneChunkSize; x++)
            this_canvas[y][x] = this_chunk.stage[x]->getRender().layers[y];


    //Render Humans to this_canvas array
    for(int i=0; i<1; i++) for(int y=0; y<3; y++)
        for(int x=0; x<3; x++) if(humans[i]->render.layers[y][x] != '?')
            this_canvas[y][humans[i]->stage_pos][x]
            = humans[i]->render.layers[y][x];

/*------------------------------------------------------*/

    //Render whole to this_render string
    string this_render = "";

    debug("Player chunk pos: " + to_string(player->chunk_pos) + '\n'); //DEBUG

    for(int y=0; y<3; y++)
    {
        for(int x=0; x<oneChunkSize; x++)
        {

            if(x==0) {
                if(y==2)
                    this_render += '_';
                else
                    this_render += ' ';
            }

            this_render += this_canvas[y][x];

            if(y==2)
                this_render += '_';
            else
                this_render += ' ';
        }
        this_render += '\n';
    }

    //Render shadow pointing at the human above
    for(int i=0; i<player->stage_pos; i++) 
        this_render += "    ";
    this_render += ">you<";

    return this_render;
}


void interacting_with_tile(Human* const& moveMe, Chunk& this_chunk=current_chunk, const int& this_input=input)
    //Checks stuff necessary for interacting
{
//Current inspected tile
    const Tile* this_tile = this_chunk.stage[moveMe->stage_pos];
//Turning char {"1"} to int {1}
    int input_to_int = this_input - 49;

    gameViewMode = actual_game;

    //Check if the input is a legal option of the interaction TUI
    if(input_to_int >= amount_of_actions || input_to_int < 0)
        return;

    //Check if human's Hand has the Item required to do the Action
    Item* human_hand = moveMe->backpack.m_inventory[moveMe->selected_item]->item;
    const Item* item_req = this_tile->getActionReq(input_to_int);

    if (item_req != nullptr && human_hand != item_req)
    {
        cout << "Requirements don't match.\n";
        return;
    }

    recent_action = "Successfully interacted with " + this_tile->name + '!';
    debug(recent_action);//DEBUG

//Call Player's (aka: moveMe's) pickup_item()
//that will put the item in the inventory
    const Item* my_loot = this_tile->getLoot(input_to_int);

    if (moveMe->pickup_item(my_loot))
        recent_action = "Full inventory!";

    //Doggo code. So cute.
    switch(this_tile->getType())
    {
        case 'D':
            const string dog_statue_wisdom[] = {
                "The statue wagged its tail.",
                "The statue licked your face.",
                "The statue sneezed.",
                "'Woof woof!'",
                "'Pant pant!'",
                "'Woof!'",
                "'Woof?'",
                "'Woof...'"
            };
            recent_action = dog_statue_wisdom[randomNumberGenerator(8)];
            return;
    }

    if (this_tile->getLoot(input_to_int) == 0) 
        return;

    const char index = this_tile->getTileToChange(input_to_int);

    if(index!=127) 
        this_chunk.stage[moveMe->stage_pos] = tile_templates[index];

    
    return;
}


void credits()
{
    
}