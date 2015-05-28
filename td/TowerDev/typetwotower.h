#ifndef TYPETWOTOWER_H
#define TYPETWOTOWER_H

#include "tower.h"

class typeTwoTower : public Tower
{
    public:
        typeTwoTower(Ogre::SceneManager& sceneManager, int x, int y, int z, std::string id);
        virtual ~typeTwoTower();
    protected:
    private:
};

#endif // TYPETWOTOWER_H
