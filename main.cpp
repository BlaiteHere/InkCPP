#include <iostream>
#include "stuff.h"
using namespace std;

/*                        /
                          /----------------.
    MADE WITH FILMORA X   /     thanks   o  |
      BY @BLAITEHERE      /      for        |--------]
                          /     using a     |--------]
                          /-----pc! ;3-----'
/                        */

void debug(string message, bool putTheDebugThingies=true){
    if(areYouDebugging){
        if(putTheDebugThingies) message = ">>> " + message;
        cout << message;
    }
    return;
}

void renderBackpack(Human* &this_human){
    Item* this_item;
    cout << this_human->nickname << "'s Backpack:\n";
    for(int i=0; i<4; i+=2){
        for(int j=0; j<2; j++){
            this_item = this_human->backpack[i+j];
            if(this_item==NULL)
                cout << i+j << " - None: ...\t\t";
            else
                cout << i+j << ' ' << this_item->icon << ' ' <<
                this_item->name << ": " << 
                this_item->description << "\t\t";
        }
        cout << '\n';
    }
    return;
}

void doTheActions(); //does actions like growing trees, moving enemies, etc.

void introduction(){
    if(areYouDebugging) {
        player->nickname = "Blaite"; 
        return;
    }
    string nameYourInk;
    cout << 
    "Name your ink. (type \"no\" if you want it to be nameless)\n>>> ";
    cin >> nameYourInk;
    if(nameYourInk!="no") player->nickname = nameYourInk;
    cout << "Welcome to the world of " << player->nickname << '!' << endl;
    return;
}

Chunk* composeChunk(unsigned int this_id, Chunk* &this_chunk){
    srand(player_seed + player->chunk_pos);
    int this_random_number;
    string debug_msg;
    debug("Generating new chunk with random numbers: ");
    for(int i=0; i<5; i++){
        this_random_number = randomNumberGenerator(5);
        debug_msg = to_string(this_random_number) + ", ";
        debug(debug_msg, false);
        this_chunk->stage[i] = tile_templates[this_random_number]->duplicate();
    }
    debug("\n", false);
    this_chunk->id = this_id;
    return this_chunk;
}

Chunk* loadChunk(Human* this_human=player, Chunk* &this_chunk = current_chunk){
    //Search if chunk exists
    for(int i=0; i<chunks.size(); i++){
        if(chunks[i].id == this_human->chunk_pos){
            for(int a=0; a<5; a++) this_chunk->stage[a] = chunks[i].stage[a];
            debug("Chunk data found. Loading chunk...\n");
            return this_chunk;
        }
    }
    //If not found:
    debug("Chunk data not found. Creating new chunk...\n");
    Chunk* new_chunk = composeChunk(this_human->chunk_pos, this_chunk);
    chunks.push_back(*new_chunk);
    return this_chunk;
}

void moveTheHuman(bool moveThemLeft, Human* moveThem=player){
	if(moveThemLeft){
		if(gameViewMode==1){
			moveThem->move(m_left);
			if(isPlayerInNewChunk)
				current_chunk = loadChunk();
			isPlayerInNewChunk=false;
		} else {
			if(moveThem->selected_item==0) 
				moveThem->selected_item=7;
			else moveThem->selected_item--;
		}
	} else {
		if(gameViewMode==1){
			if(player->stage_pos>3) 
				current_chunk = loadChunk();
			moveThem->move(m_right);
			if(isPlayerInNewChunk)
				current_chunk = loadChunk();
			isPlayerInNewChunk=false;
		} else {
			if(moveThem->selected_item==7) 
				moveThem->selected_item=0;
			else moveThem->selected_item++;
		}
	}
	return;
}

void quitTheGame(){
	char answer;
	cout << "Are you sure you want to leave the game? (y/n)\n>>>";
	cin >> answer;
	if(answer=='y' or answer=='Y') {
		youWannaKeepGaming = false;
		cout << "See you soon " << player->nickname << "... ";
		cin >> answer;
	} else cout << "Phew! I thought you were going to leave us...\n";
	return;
}

void interact(Human* this_human){
    Tile* this_tile=current_chunk->stage[this_human->stage_pos];
	int amount_of_actions = this_tile->interact();
	int action_number;
	while(true){
		cin >> action_number;
		if(action_number >= amount_of_actions){
			cout << '\n'; 
			return;
		}
		else if(action_number < amount_of_actions) break;  // only 3 actions in tile possible
	}
	player->pickup_item(this_tile->get_loot(action_number));
    if(this_tile->change_to == 127) return;
	this_tile = tile_templates[this_tile->change_to]->duplicate();
	return;
}

void povYouDidNothing(){
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
		"Uwu, U-um, *sweats confused* I t-think you might f-f-fowwgot to u-use your keyboawd >///<\n(pls, kill me)"
	};
	cout << youDidNuthin[rand()%10] << endl;
	return;
}

void getInput(Human* moveThem){
    char input;
    cin >> input;
    if(input>96) 
        input -= 32;
    switch(input){
        case 'A':
            moveTheHuman(true);
            break;
        case 'D':
			moveTheHuman(false);
            break;
        case 'Q':
            quitTheGame();
            return;
        case 'I':
			interact(moveThem);
			break;
        case 'E':
            if(gameViewMode==0) gameViewMode=1;
            else gameViewMode = 0;
            break;
        default:
            povYouDidNothing();
            break;
    }
    return;
}

string renderChunk(Tile* this_chunk[5], Human* players[]){
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
    debug(to_string(player->chunk_pos) + '\n');
    for(int y=0; y<3; y++){
        for(int x=0; x<5; x++){
            if(x==0) {
                if(y==2) this_render += '_';
                else this_render += ' ';
            }
            this_render += this_canvas[y][x];
            if(y==2) this_render += '_';
            else this_render += ' ';
        }
        this_render += '\n';
    }
    return this_render;
}

int main(){
    introduction();
    current_chunk = loadChunk();
    while(youWannaKeepGaming){
        if(!areYouDebugging) system("cls");
        if(gameViewMode==1)
            cout << renderChunk(current_chunk->stage, humans);
        else
            renderBackpack(player);
        getInput(player);
    }
    return 0;
}