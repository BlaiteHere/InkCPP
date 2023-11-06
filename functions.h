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
  ####   ##  ##   ####    #####   #####  ######   ####   ###### \n\
 ##  ##  ##  ##  ##  ##  ##      ##        ##    ##  ##    ##   \n\
 #####   ##  ##  #####   #####    ####     ##    #####     ##   \n\
 ##  ##  ##  ##  ##      ##          ##    ##    ##  ##    ##   \n\
 ##  ##   ####   ##       #####  #####     ##    ##  ##  ###### \n\n\
                                                 made by Blaite.\n"
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
    } else titleScreen();

    cout << "Name your ink. (type \"no\" if you want it to be nameless)\n>>> ";
    cin >> nameYourInk;

    if(nameYourInk!="no")
        player->name = nameYourInk;

    cout << "Welcome to " << player->name << "'s world!" << endl
    << "Write any key to continue...\n";
    cin >> nameYourInk;
    return;
}


const int randomNumberGenerator(const int& stop, const int& start=0)
    //RNG
{
    //Use the world/creator's name as a seed for the random generation
    return start + (rand() % (stop - start));
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


void useSelectedItem(Human* const &this_human, Chunk* this_chunk = current_chunk)
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
    else recent_action = "Error! How did we get here?";

    //Check Item type
    if (item->type == 't' || item->icon == 'w')
        this_human->render.layers[1][2] = item->icon;
    else if (item->type == 'c') 
        this_human->useItem(selected_inventory_space);
    else if (
        item->type == 'T' && 
        this_chunk->stage[this_human->stage_pos] == (const Tile*)item_templates[0]
    )
    {
        ItemTile* item_tile = static_cast<ItemTile*>(item);
        this_chunk->stage[this_human->stage_pos] = (Tile*)tile_templates[item_tile->tileToChange];
        this_human->useItem(selected_inventory_space);
    }

    return;
};


//void doTheActions(); // growing trees, moves enemies, etc.


void startCrafting()
    //RENDERS CRAFTING TUI
{
    recent_action = "Crafting...";

    return;
}


void composeChunk(unsigned const int& this_id, Chunk* &this_chunk)
    //CONSTRUCTS A CHUNK AND RETURNS IT
{
    srand(player_seed + player->chunk_pos);
    int this_random_number;
    string debug_msg;   //DEBUG

    debug("Generating new chunk with random numbers: ");

    for(int i=0; i<oneChunkSize; i++)
    {
        this_random_number = randomNumberGenerator(7);
        debug_msg = to_string(this_random_number) + ", ";//DEBUG
        debug(debug_msg, false);                         //DEBUG
        this_chunk->stage[i] = tile_templates[this_random_number]->clone();
    }

    debug("\n", false); //DEBUG
    this_chunk->id = this_id;
    return;
}


//Chunk* saveChunk();


void loadChunk(Human* const& this_human = player, Chunk* this_chunk = current_chunk)
    //CHECKS IF CHUNK EXISTS, IF IT DOESN'T THEN MAKES ONE WITH composeChunk()
{
    //Search if chunk exists
    for(int i=0; i<chunks.size(); i++)
    {
        if(chunks[i].id == this_human->chunk_pos)
        {
            for(int a=0; a<oneChunkSize; a++)
                this_chunk->stage[a] = chunks[i].stage[a];

            debug("Chunk data found. Loading chunk...\n");  //DEBUG
            return;
        }
    }
    //If not found:
    debug("Chunk data not found. Creating new chunk...\n"); //DEBUG
    composeChunk(this_human->chunk_pos, this_chunk);
    chunks.push_back(*this_chunk);
    return;
}

void moveTheHuman(const bool moveThemLeft, Human* const moveThem = player)
    //MOVES SPECIFIED HUMAN IN THE PLACE THEY WANNA MOVE
{
    enum moving_direction: bool{
        m_left=true,
        m_right=false
    };

	if(moveThemLeft && gameViewMode == actual_game)
    {
        moveThem->move(m_left);

        if(isPlayerInNewChunk)
            loadChunk();

        isPlayerInNewChunk=false;

	} else {
        if(player->stage_pos > 3) 
            loadChunk();

        moveThem->move(m_right);

        if(isPlayerInNewChunk)
            loadChunk();

        isPlayerInNewChunk = false;
	}
	return;
}


void change_inventory_selected_space(const bool change_space_left = true)
    //CHANGES INVENTORY SELECTED CURSOR SPACE 
    //and checks if it's not out of bounds of the array
{
    if(change_space_left)
    {
        if(selected_inventory_space == 0) 
            selected_inventory_space = 7;

        else selected_inventory_space--;

    } else {
        if(selected_inventory_space == 7) 
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

	if(answer=='y' or answer=='Y') {
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


string renderChunk(const Chunk* const& this_chunk, Human* const players[])
    //RETURNS STRING WITH THE VIEW OF THE GAME SCENE
{
    //Render Tiles to this_canvas array
    string this_canvas[3][oneChunkSize];

    for(int y=0; y<3; y++)
        for(int x=0; x<oneChunkSize; x++)
            this_canvas[y][x] = this_chunk->stage[x]->render.layers[y];


    //Render Humans to this_canvas array
    for(int i=0; i<1; i++)
        for(int y=0; y<3; y++)
            this_canvas[y][humans[i]->stage_pos] = humans[i]->render.layers[y];

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
    return this_render;
}

void interacting_with_tile(Human* const& moveMe, const int& this_input=input)
    //Checks stuff necessary for interacting
{
    //Current inspected tile
    Tile* this_tile = current_chunk->stage[moveMe->stage_pos];
        // turning char {"1"} to int {1}
    int input_to_int = this_input - 49;

    //Check if the input is a legal option of the interaction TUI
    if(input_to_int >= amount_of_actions || input_to_int < 0)
    {
        gameViewMode = actual_game;
        return;
    }

    //Check if human's hand has the item to do the action
    Item* human_hand = moveMe->backpack.m_inventory[moveMe->selected_item]->item;
    const Item* item_req = this_tile->getActionReq(input_to_int);

    if (item_req != nullptr && human_hand != item_req)
    {
        cout << "Requirements don't match.\n";
        gameViewMode = actual_game;
        return;
    }

    recent_action = "Successfully interacted with " + static_cast<Tile*>(this_tile)->name + '!';
    debug("Successfully commited tax fraud.\n");

    //Call Player(moveMe)'s pickup_item() that will put the item in the inventory
    Item* my_loot = (Item*)(this_tile->getLoot(input_to_int));
    if (moveMe->pickup_item(my_loot)) recent_action = "Full inventory!";

    if (this_tile->getLoot() == 0) 
        return;

    const char index = this_tile->getTileToChange(input_to_int);

    if(index!=127) 
        current_chunk->stage[moveMe->stage_pos]
         = tile_templates[index]->clone();

    gameViewMode = actual_game;
    return;
}



void credits()
{
    
}