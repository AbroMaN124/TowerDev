#ifndef TYPEONETOWER_H
#define TYPEONETOWER_H

#include "tower.h"


class typeOneTower : public Tower
{
    public:
        typeOneTower(Ogre::SceneManager& sceneManager, int x, int y, int z, std::string id);
virtual ~typeOneTower();
    protected:
    private:
};

#endif // TYPEONETOWER_H
