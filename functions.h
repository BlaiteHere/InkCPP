#include "stuff.h"
using namespace std;

char input;
char amount_of_actions = 3;
char selected_inventory_space = 0;


enum gameViewModes: char {
    inventory_tui,
    actual_game,
    interaction_tui,
    crafting_tui
};


int randomNumberGenerator(int stop, int start=0){
    //Use the name as a seed for the random generation
    return start + (rand() % (stop - start));
}


void debug(string message, bool putTheDebugThingies = true){ //DEBUG
    if(areYouDebugging){
        if(putTheDebugThingies) message = ">>> " + message;
        cout << message;
    }
    return;
}


void renderBackpack(Human* &this_human){
    Item* this_item = this_human->backpack[selected_inventory_space];

    cout << this_human->name << "'s Backpack:\n";

    for(int i=0; i<8; i+=2){
        for(int j=0; j<2; j++)
        {
            int current_index = i+j;
            this_item = this_human->backpack[current_index];

            if(i+j == selected_inventory_space)
                cout << '$';
            else
                cout << current_index;

            if(this_item == NULL)
                cout << " - None: ...\t\t";
            else
                cout << ' ' << this_item->icon << ' ' <<
                this_item->name << ": " << 
                this_item->description << "\t\t";
        }

        cout << '\n';
    }
    return;
}


void useSelectedItem(Human* human_with_inventory) 
{
    human_with_inventory->backpack[selected_inventory_space]->use();

    return;
};


void doTheActions(); //does actions like growing trees, moving enemies, etc.


void startCrafting(){
    return;
}


void introduction(){
    string nameYourInk; //DEBUG
    if(areYouDebugging){
        player->name = "Blaite";
        return;
    }

    cout << "Name your ink. (type \"no\" if you want it to be nameless)\n>>> ";
    cin >> nameYourInk;

    if(nameYourInk!="no")
        player->name = nameYourInk;

    cout << "Welcome to the world of " << player->name << '!' << endl;
    cin >> nameYourInk;
    return;
}


Chunk* composeChunk(unsigned int this_id, Chunk* &this_chunk){
    srand(player_seed + player->chunk_pos);
    int this_random_number;
    string debug_msg;   //DEBUG

    debug("Generating new chunk with random numbers: ");

    for(int i=0; i<5; i++){
        this_random_number = randomNumberGenerator(5);
        debug_msg = to_string(this_random_number) + ", ";   //DEBUG
        debug(debug_msg, false);    //DEBUG
        this_chunk->stage[i] = tile_templates[this_random_number]->duplicate();
    }

    debug("\n", false); //DEBUG
    this_chunk->id = this_id;
    return this_chunk;
}


Chunk* saveChunk();


Chunk* loadChunk(Human* this_human=player, Chunk* &this_chunk = current_chunk){
    //Search if chunk exists
    for(int i=0; i<chunks.size(); i++){
    
        if(chunks[i].id == this_human->chunk_pos){

            for(int a=0; a<5; a++) this_chunk->stage[a] = chunks[i].stage[a];

            debug("Chunk data found. Loading chunk...\n");  //DEBUG
            return this_chunk;
        }
    }
    //If not found:
    debug("Chunk data not found. Creating new chunk...\n"); //DEBUG
    Chunk* new_chunk = composeChunk(this_human->chunk_pos, this_chunk);
    chunks.push_back(*new_chunk);
    return this_chunk;
}

void moveTheHuman(bool moveThemLeft, Human* moveThem=player){
	if(moveThemLeft && gameViewMode == actual_game){
        moveThem->move(m_left);

        if(isPlayerInNewChunk)
            current_chunk = loadChunk();

        isPlayerInNewChunk=false;

	} else {
        if(player->stage_pos > 3) 
            current_chunk = loadChunk();

        moveThem->move(m_right);

        if(isPlayerInNewChunk)
            current_chunk = loadChunk();

        isPlayerInNewChunk = false;
	}
	return;
}


void change_inventory_selected_space(bool change_space_left = true)
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
{
	string youDidNuthin[]={
		"Uh oh! You did nothing...\t:/",
		"Woopsie daisy! Nothing happened.",
		"Nothing was changed! :/",
		"Bruhh, did you do nothing on purpose just to see this msg??",
		">-< n-nothing was done, user-chan!!~ nya.",
		"But nothing came.",
		">>> [Turn skipped!] >>>",
		"Nothing wasn't done, yesn't?",
		"Heavens! You happened to forget to write down the message!\nKinda cringe, innit bruv?",
		"UwU, U-um, *sweats confused* I t-think you might f-f-fowwgot to u-use your keyboawd >///<\n(pls, kill me)"
	};

	cout << youDidNuthin[rand() % 10] << endl;
	return;
}


string renderChunk(Tile* this_chunk[5], Human* players[])
{
    //Render Tiles to this_canvas array
    string this_canvas[3][5];

    for(int y=0; y<3; y++)
        for(int x=0; x<5; x++)
            this_canvas[y][x] = this_chunk[x]->layers[y];

    //Render Humans to this_canvas array
    for(int i=0; i<1; i++)
        for(int y=0; y<3; y++)
            this_canvas[y][humans[i]->stage_pos] = humans[i]->layers[y];

    //Render whole to this_render string
    string this_render = "";

    debug("Player chunk pos: " + to_string(player->chunk_pos) + '\n'); //DEBUG

    for(int y=0; y<3; y++){
        for(int x=0; x<5; x++){

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