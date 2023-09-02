#include "functions.cpp"
using namespace std;


void getInput(Human* moveThem){
    char input;
    cin >> input;

    if(input>96) //Check if small letter, if yes - changes to capitalised letter 
        input -= 32;
    
    switch(gameViewMode)
    {
        case 0:                 //inventory
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
                    interact(moveThem);
                    break;
                case 'E':
                    switchGameViewModes();
                    break;
                default:
                    povYouDidNothing();
                    break;
            }
            break;

        case 1:                 //actual game input
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
                switchGameViewModes();
                break;
            default:
                povYouDidNothing();
                break;
            }
            break;

        case 2:                 //interaction screen
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
                switchGameViewModes();
                break;
            default:
                povYouDidNothing();
                break;
            break;
    }

    return;
}


void gameHandler(){
    switch(gameViewMode){
        case 0:                 //inventory
            renderBackpack(player);
            break;
        case 1:                 //actual game input
            cout << renderChunk(current_chunk->stage, humans);

            break;
        case 2:                 //interaction screen
            break;
    }
    return;
}


int main(){
    char* blaite;   //DEBUG
    introduction();
    current_chunk = loadChunk();
    while(youWannaKeepGaming){
        if(!areYouDebugging) system("cls"); //WINDOWS ONLY! cleans cmdl
        getInput(player);
    }

    delete blaite;  //DEBUG
    return 0;
}