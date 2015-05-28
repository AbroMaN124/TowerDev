#ifndef BULLET_H
#define BULLET_H


#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include <OgreRoot.h>
#include "creep.h"



class bullet
{
    public:
        bullet(std::string id, Ogre::Vector3 destination, Ogre::SceneManager& sceneManager, Ogre::Vector3 pos);
        virtual ~bullet();
        bool Update(Ogre::SceneManager& sceneManager, Creep& creep);
    protected:
    private:
        float speed;
        Ogre::Vector3 direction;
        std::string name;
        Ogre::Vector3 pos;

        //Ogre::Vector3 destinations;
        Ogre::Vector3 dest;
        Ogre::Real distance;
};

#endif // BULLET_H
