#include "typetwotower.h"

typeTwoTower::typeTwoTower(Ogre::SceneManager& sceneManager, int x, int y, int z, std::string id)
    : Tower(sceneManager, x, y, z, id, "column.mesh", 700)
{

    newNode->scale(2.5, .7, 2.5);
}

typeTwoTower::~typeTwoTower()
{
    //dtor
}
