#include "functions.h"
using namespace std;


void getInput(Human* moveThem)
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
                    useSelectedItem(player);
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
            Tile* this_tile = current_chunk->stage[player->stage_pos];
            int input_to_int = input - 48;

            //check if the int can be an input
            if(input_to_int >= amount_of_actions || input_to_int < 0){
                gameViewMode = actual_game;
                return;
            }

            player->pickup_item(this_tile->get_loot(input_to_int));

            if(this_tile->change_to == dont_change) 
                return;

            this_tile = tile_templates[this_tile->change_to]->duplicate();
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
    return 0;
}