#include "functions.h"
using namespace std;


void getInput(Human* moveThem)
    //GETS INPUT
{
    cout << "\n >>> Write your input here: ";
    cin >> input;

    //Check if [small letter], if yes - changes to CAPITALISED LETTER
    if(input > 96) 
        input -= 32;
    
    switch(gameViewMode)
    {
        case inventory_tui:
            switch(input)
            {
                case 'W':
                    change_inventory_selected_space();
                    break;
                case 'S':
                    change_inventory_selected_space(false);
                    break;
                case 'Q':
                    quitTheGame();
                    return;
                case 'R':
                    useSelectedItem(moveThem);
                    break;
                case 'E':
                    recent_action = " ";
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
                case 'R':
                    gameViewMode = interaction_tui;
                    break;
                case 'E':
                    gameViewMode = inventory_tui;
                    break;
                case 'C':
                    PrintChunks();
                    break;
                default:
                    povYouDidNothing();
                    return;
            }
            break;

        case interaction_tui: 
        {
            interacting_with_tile(moveThem);
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
                case 'R':
                    gameViewMode = interaction_tui;
                    break;
                case 'E':
                    gameViewMode = inventory_tui;
                    break;
                case 'C':
                    startCrafting();
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
    string current_obj;

    cout << "\nInstructions:\n";

    switch(gameViewMode)
    {
        case inventory_tui:
            current_obj = player->backpack.m_inventory[player->selected_item]->item->getName();
            cout << 
"\
 W-S to navigate the inventory up & down\n\
 E to close the inventory\n\
 R to use " << current_obj << "\n\
 C to craft (unavailable)\n\
";
            return;

        case actual_game:
            current_obj = current_chunk.stage[player->stage_pos]->getName();
            cout << 
"\
 A-D to move left-right\n\
 E to open inventory\n\
 R to interact with " << current_obj << "\n\
 C to craft (unavailable)\n\
";
            return;

        case interaction_tui:
            cout << 
"\
 1-2-3 to select action\n\
 Write anything else to exit the interaction screen\n\
";
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
            cout << renderChunk(current_chunk, humans);
            return;

        case interaction_tui:
            amount_of_actions = current_chunk.stage[player->stage_pos]->interact();
            return;
    }
    return;
}


/*void memory_deletus()
//DELETES HEAP MEMORY and has all the heap-allocated elements in here
{
    for(int i=0; i<1; i++)
        delete humans[i];
    vector<Chunk>().swap(chunks);
    for(int i=0; i<5; i++)
        delete tile_templates[i];
    for(int i=0; i<7; i++)
        delete item_templates[i];
}*/


int main()
{
    areYouDebugging = false;

    titleScreen();
    introduction();
    loadChunk();

    if(areYouDebugging)
        while(youWannaKeepGaming)
        {
            debug("NEWLINE\n");
            cout << recent_action << endl;

            gameHandler();
            inGameShowControls();
            getInput(player);
        }
    else
        while(youWannaKeepGaming)
        {
            //system("cls");  //WINDOWS ONLY! cleans cmdl

            cout << recent_action << endl;
            gameHandler();
            inGameShowControls();
            getInput(player);
        }
    return 0;
}