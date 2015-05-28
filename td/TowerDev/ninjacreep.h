#ifndef NINJACREEP_H
#define NINJACREEP_H


#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include <OgreRoot.h>
#include "creep.h"
#include "vertex.h"
#include "randomgenerator.h"

class ninjaCreep : public Creep
{
    public:
        ninjaCreep(Ogre::SceneManager& sceneManager, int x, int y, int z, std::string id,
         vertex* initial, RandomGenerator& rgen);
        virtual ~ninjaCreep();
    protected:
    private:
};

#endif // NINJACREEP_H
