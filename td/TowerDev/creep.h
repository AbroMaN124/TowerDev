#ifndef CREEP_H
#define CREEP_H

#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include <OgreRoot.h>

#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

class Creep
{
    public:
        Creep(Ogre::SceneManager& sceneManager, int x, int y, int z, std::string id, std::string mesh, int hp, Ogre::Vector3 ifv, std::string deathanimation);
        Creep();
        virtual ~Creep();
        int getHP();
        Ogre::Vector3 getPosition(Ogre::SceneManager& sceneManager);
        void setHP(int newHP);
        bool checkStatus(Ogre::SceneManager& sceneManager);
        bool updateMovement(Ogre::SceneManager& sceneManager);
        bool nextLocation(Ogre::SceneManager& sceneManager);
    protected:
        std::deque<Ogre::Vector3> junctions;
        std::string name;
        std::string da;

    private:
        int hp;
        Ogre::Vector3 pos;
        Ogre::Vector3 startPos;
        bool alive;
        bool notified;
        Ogre::AnimationState *animationState;
        Ogre::Entity* unit;
        Ogre::Vector3 direction;
        Ogre::Real speed;
        Ogre::Vector3 destination;
        Ogre::Real distance;
        Ogre::Vector3 facingVector;


};

#endif // CREEP_H
