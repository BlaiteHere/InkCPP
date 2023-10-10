#include <iostream>
using namespace std;

bool areYouDebugging = true;

void debug(string message, bool putTheDebugThingies = true){ //DEBUG
    if(areYouDebugging){
        if(putTheDebugThingies) message = ">>> " + message;
        cout << message;
    }
    return;
}