#include "ninjacreep.h"

ninjaCreep::ninjaCreep(Ogre::SceneManager& sceneManager, int x, int y, int z, std::string id, vertex* initial, RandomGenerator& rgen)
        : Creep(sceneManager, x, y ,z, id, "ninja.mesh", 100, Ogre::Vector3::NEGATIVE_UNIT_Z, "Death1")
{
    //ninja.mesh
    //hp = 100
    //initial facing vector = NEGATIVE_UNIT_Z
    int k = 1;
    junctions.clear();
    //TODO: for report, the below line removes an incosistant starting rotation glitch
    junctions.push_back(Ogre::Vector3(x,y,z+1));
    do {
        if(k == 0) {
        initial = initial->childrenNodes[rgen.getRandom(0, initial->childrenNodes.size())];
        } else
            k = 0;
        junctions.push_back(Ogre::Vector3(initial->xCor, 0, initial->zCor));

    } while(!initial->childrenNodes.empty());
}

ninjaCreep::~ninjaCreep()
{
    Ogre::LogManager::getSingletonPtr()->logMessage("ninja creep destroyed");

}
