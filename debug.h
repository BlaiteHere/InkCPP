#include "includes.h"
using namespace std;

bool areYouDebugging = true;

void debug(string message, const bool putTheDebugThingies = true)
    //DEBUG
{
    if(areYouDebugging)
    {
        if(putTheDebugThingies) message = ">>> " + message;
        cout << message;
    }
    return;
}