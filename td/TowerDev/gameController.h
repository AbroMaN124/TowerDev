#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "objectController.h"

class objectController;

class gameController
{
    public:
        gameController();
        ~gameController();
        void upLevel(objectController& objController);
        void addCoins(int x);
        bool removeCoins(int x);
        int getLevel();
        void placeTower(int x, objectController& objController);
    protected:
    private:
        int coins;
        int level;
};

#endif // GAMECONTROLLER_H
