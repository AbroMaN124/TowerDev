#include "tower.h"

#include <iostream>
#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include <OgreMeshManager.h>
/** \class Tower
    \brief class for tower instances

    This is to class used to create instances of towers.
*/


/**
    Constructor for a new tower.
    @param[out] &sceneManager The SceneManager(ogre3D) that the object should be linked too.
    @param [in] x, y, z Coordinates of the tower in 3D space
    @param [in] id Name assosiated with object (tower),
     no two entities within the same SceneManager(ogre3D) should have the same name
*/

Tower::Tower(Ogre::SceneManager& sceneManager, int x, int y, int z, std::string id, std::string modelname, int r)
{
    radius = r;
    pos = Ogre::Vector3(x,y,z);
    Ogre::Entity* unit = sceneManager.createEntity(id, modelname);

    Ogre::LogManager::getSingletonPtr()->logMessage("entity created: " + id);
    newNode = sceneManager.getRootSceneNode()->createChildSceneNode( id, Ogre::Vector3( 0, 0, 0 ) );

        Ogre::LogManager::getSingletonPtr()->logMessage("scenenode created: " + id);
    newNode->attachObject(unit);

    newNode->setPosition(pos);

    name = id;


        Ogre::LogManager::getSingletonPtr()->logMessage("all done: " + id);
}

/**
    Destructor for a tower instance.
*/
Tower::~Tower()
{
    //dtor
}

/**
    Attack class attacks creep passed too it. Should be called as part of the tower's update.
    @Param[out] &creep the creep that is being attacked by the tower.
*/

void Tower::Attack(Creep& creep, Ogre::SceneManager& sceneManager, std::string bulletid)
{
    //if creep is within a specific radius (int radius?) of the tower the tower will attack.
    Ogre::Real i = sceneManager.getSceneNode(name)->getPosition().distance(creep.getPosition(sceneManager));
        Ogre::LogManager::getSingletonPtr()->logMessage("distance: " + Ogre::StringConverter::toString(i));
    if(creep.getHP()>0){

        if(i <= radius) {
        //creep.getPosition(sceneManager).x < pos.x+radius && creep.getPosition(sceneManager).x >= pos.x-radius) {
        //TODO: change to range
        eBullets.push_back( new bullet(bulletid, creep.getPosition(sceneManager), sceneManager, pos) );
        }
    }
}

Creep* Tower::UTarget(Creep& currentTarget, Creep& potentialTarget, Ogre::SceneManager& sceneManager)
{
    if(currentTarget.getHP()<=0) {
        return &potentialTarget;
    }
    if(potentialTarget.getHP()>0){
        if(&currentTarget == &potentialTarget) {
            return &potentialTarget;
        } else {
            Ogre::Vector3 tempP = potentialTarget.getPosition(sceneManager)-pos;
            Ogre::Vector3 tempC = currentTarget.getPosition(sceneManager)-pos;

            //Alternative to using square root to find distance between two points
            //Did not use square root due performance issues that they can create
            if((tempP.x*tempP.x + tempP.y*tempP.y + tempP.z*tempP.z) <
                (tempC.x*tempC.x + tempC.y*tempC.y + tempC.z*tempC.z)){
                    return &potentialTarget;
                }
        }
    }
    return &currentTarget;
}

std::string Tower::getName()
{
    return name;
}

void Tower::UpdateBullets(Ogre::SceneManager& sceneManager, Creep& creep)
{
    std::list<bullet*>::iterator i;
        for(i=eBullets.begin(); i != eBullets.end(); ++i) {
            tempBullet= (*i);
            if(!tempBullet->Update(sceneManager, creep));
            {
               //TODO: Delete object
            }
        }
}
