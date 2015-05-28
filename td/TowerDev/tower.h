#ifndef TOWER_H
#define TOWER_H

#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include <OgreMeshManager.h>
#include <OgreRoot.h>
#include <list>

#include <unistd.h>
#include <string.h>

#include "creep.h"
#include "bullet.h"

class Tower
{
    public:
        Tower(Ogre::SceneManager& sceneManager, int x, int y, int z, std::string id, std::string modelname, int r);
        virtual ~Tower();
        void Attack(Creep& creep, Ogre::SceneManager& sceneManager, std::string bulletid);
        Creep* UTarget(Creep& currentTarget, Creep& potentialTarget, Ogre::SceneManager& sceneManager);
        std::string getName();
        void UpdateBullets(Ogre::SceneManager& sceneManager, Creep& creep);
    protected:
        Ogre::SceneNode* newNode;
    private:
        int hp;
        Ogre::Vector3 pos;
        std::string name;
        int radius;
        std::list<bullet*> eBullets;

        bullet* tempBullet;

};

#endif // TOWER_H
