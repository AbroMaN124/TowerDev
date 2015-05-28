#include "typeonetower.h"

typeOneTower::typeOneTower(Ogre::SceneManager& sceneManager, int x, int y, int z, std::string id)
    : Tower(sceneManager, x, y, z, id, "Barrel.mesh", 500)
{
    newNode->scale(20, 40, 20);
    newNode->translate(0, 120, 0);
}

typeOneTower::~typeOneTower()
{
    //dtor
}
