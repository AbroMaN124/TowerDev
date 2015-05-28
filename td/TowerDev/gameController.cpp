#include "gameController.h"
#include "objectController.h"

gameController::gameController()
{
    level = 1;
    coins = 6;
}

gameController::~gameController()
{
    //dtor
}

void gameController::upLevel(objectController& objController)
{
    level++;
    coins += ((level+1) - objController.getCreepCount()); //TODO: Update coins as creep dies instead of new level
    objController.newCreepWave(level+1);
}

void gameController::addCoins(int x){
    coins += x/2;
}

void gameController::placeTower(int type, objectController& objController){
    switch(type) {
        case 3:
            coins -= type;
            if(coins<0)
                coins += type;
            else
                objController.placeT1Tower();
            break;
        case 4:
            coins -= type;
            if(coins<0)
                coins += type;
            else
                objController.placeT2Tower();
            break;
    }
}

int gameController::getLevel() {
    return level;
}
