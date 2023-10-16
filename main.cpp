#include "functions.h"
using namespace std;


void getInput(Human* moveThem)
    //GETS INPUT
{
    cout << "Action: ";
    cin >> input;

    //Check if [small letter], if yes - changes to CAPITALISED LETTER
    if(input > 96) 
        input -= 32;
    
    switch(gameViewMode)
    {
        case inventory_tui:
            switch(input)
            {
                case 'A':
                    change_inventory_selected_space();
                    break;
                case 'D':
                    change_inventory_selected_space(false);
                    break;
                case 'Q':
                    quitTheGame();
                    return;
                case 'I':
                    useSelectedItem(moveThem);
                    break;
                case 'E':
                    gameViewMode = actual_game;
                    break;
                default:
                    povYouDidNothing();
                    return;
            }
            break;

        case actual_game:
            switch(input)
            {
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
                    gameViewMode = interaction_tui;
                    break;
                case 'E':
                    gameViewMode = inventory_tui;
                    break;
                case 'C':

                    break;
                default:
                    povYouDidNothing();
                    return;
            }
            break;

        case interaction_tui: 
        {
            // current inspected tile
            Tile* this_tile = current_chunk->stage[player->stage_pos];
             // turning char {"1"} to int {1}
            int input_to_int = input - 48;

            // check if the input is a legal option of the interaction TUI
            if(input_to_int >= amount_of_actions || input_to_int < 0){
                gameViewMode = actual_game;
                return;
            }

            //Check if human's hand has the item to do the action
            Item* human_hand = moveThem->backpack[moveThem->selected_item]->item;

            if (this_tile->getActionReq(input_to_int) != (const Item*)nullptr &&
            human_hand != this_tile->getActionReq(input_to_int))
            {
                cout << "Requirements don't match.\n";
                gameViewMode = actual_game;
                return;
            }

            cout << "Successfully commited tax fraud.\n";// << '\n';

            //Call player's pickup_item() that will put the item in the inventory
            Item* my_loot = (Item*)(this_tile->get_loot(input_to_int));
            moveThem->pickup_item(my_loot);

            if(this_tile->get_loot() == 0) 
                return;

            current_chunk->stage[player->stage_pos] = 
            tile_templates[this_tile->change_tile_to(input_to_int)]->duplicate();
            gameViewMode = actual_game;

            break;
        }

        case crafting_tui:
            switch(input)
            {
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
                    gameViewMode = interaction_tui;
                    break;
                case 'E':
                    gameViewMode = inventory_tui;
                    break;
                case 'C':
                    //startCrafting();
                    break;
                default:
                    povYouDidNothing();
                    return;
            }
            break;
    }
    return;
}


void inGameShowControls()
    //OUTPUTS GAME CONTROLS FOR SPECIFIC GAMEVIEWMODES
{
    cout << '\n';

    switch(gameViewMode)
    {
        case inventory_tui:
            cout << 
            "A-D to move    E to close inventory    I to use    C to craft\n";
            return;

        case actual_game:
            cout << 
            "A-D to navigate    E to open inventory    I to interact    C to craft\n";
            return;

        case interaction_tui:
            cout << 
            "0-1-2 select action    Anything else to close\n";
            return;
    }
    return;
}


void gameHandler()
    //OUTPUTS TO THE CONSOLE
{
    switch(gameViewMode)
    {
        case inventory_tui:
            renderBackpack(player);
            return;

        case actual_game:
            cout << renderChunk(current_chunk->stage, humans);
            return;

        case interaction_tui:
            amount_of_actions = current_chunk->stage[player->stage_pos]->interact();
            return;
    }
    return;
}


void memory_deletus()
    //DELETES HEAP MEMORY
{
    for(int i=0; i<1; i++)
        delete humans[i];
    vector<Chunk>().swap(chunks);
    for(int i=0; i<5; i++)
        delete tile_templates[i];
    for(int i=0; i<7; i++)
        delete item_templates[i];
}


int main()
{
    areYouDebugging = true;

    introduction();
    current_chunk = loadChunk();

    while(youWannaKeepGaming)
    {
        if(!areYouDebugging) system("cls"); //WINDOWS ONLY! cleans cmdl

        gameHandler();
        //cout << endl << gameViewMode << endl;     DEBUG!
        inGameShowControls();
        getInput(player);
    }

    memory_deletus();
    return 0;
}