#ifndef ROBOTCREEP_H
#define ROBOTCREEP_H


#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include <OgreRoot.h>
#include "creep.h"
#include "vertex.h"
#include "randomgenerator.h"


class robotCreep : public Creep
{
    public:
        robotCreep(Ogre::SceneManager& sceneManager, int x, int y, int z, std::string id,
         vertex* initial, RandomGenerator& rgen);
        virtual ~robotCreep();
    protected:
    private:
};

#endif // ROBOTCREEP_H
