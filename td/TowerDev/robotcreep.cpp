#include "robotcreep.h"

robotCreep::robotCreep(Ogre::SceneManager& sceneManager, int x, int y, int z, std::string id,
 vertex* initial, RandomGenerator& rgen)
        : Creep(sceneManager, x, y ,z, id, "robot.mesh", 150, Ogre::Vector3::UNIT_X, "Die")
{
    //robot.mesh
    //hp = 100
    //initial facing vector = UNIT_X

    int k = 1;
    junctions.clear();
    //TODO: for report, the below line removes an incosistant starting rotation glitch
    junctions.push_back(Ogre::Vector3(x,y,z+1));
    do {
        if(k == 0) {
        initial = initial->childrenNodes[rgen.getRandom(0, initial->childrenNodes.size())]; //TODO: random child, not the first!
        } else
            k = 0;
        junctions.push_back(Ogre::Vector3(initial->xCor, 0, initial->zCor));
        //Ogre::LogManager::getSingletonPtr()->logMessage(name + " " + Ogre::StringConverter::toString(initial->xCor) + "coordinates" + Ogre::StringConverter::toString(initial->zCor));

    } while(!initial->childrenNodes.empty());

    sceneManager.getSceneNode(id)->scale(2, 2 ,2);
}

robotCreep::~robotCreep()
{
    //dtor
}
