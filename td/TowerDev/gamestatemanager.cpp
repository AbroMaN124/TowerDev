#include "gamestatemanager.h"


/**states:
    0 = default
    1 = pre-game
    2 = ingame
    3 = loss
    4 = win
*/
gameStateManager::gameStateManager()
{
   state = 1;
}


void gameStateManager::setState(int value) {
    state = value;
}

int gameStateManager::getState() {
    return state;
}

gameStateManager::~gameStateManager()
{
    //dtor
}
