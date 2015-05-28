#include "creep.h"

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
/** \class Creep
    \brief class for creep instances

    This is to class used to create instances of creeps.
*/


/**
    Constructor for a new tower.
    @param[out] &sceneManager The SceneManager(ogre3D) that the object should be linked too.
    @param[in] x, y, z Coordinates of the creep in 3D space
    @param[in] id Name assosiated with object (creep),
     no two entities within the same SceneManager(ogre3D) should have the same name
*/
Creep::Creep(Ogre::SceneManager& sceneManager, int x, int y, int z,
std::string id, std::string mesh, int health, Ogre::Vector3 ifv, std::string deathanimation) //ifv = initial facing vector
{
    facingVector = ifv;
    name = id;
    // Create the walking list

    hp = health;
    startPos = Ogre::Vector3(x,y,z);
    unit = sceneManager.createEntity(id, mesh);
    Ogre::SceneNode* newNode = sceneManager.getRootSceneNode()
    ->createChildSceneNode(id, Ogre::Vector3(0, 0, 0));
    newNode->attachObject(unit);
    direction = Ogre::Vector3::ZERO;

    newNode->setPosition(startPos);

    destination = junctions.front();
    //direction = destination - sceneManager.getSceneNode(name)->getPosition();

    Ogre::Vector3 src = sceneManager.getSceneNode(name)->getOrientation() * facingVector;

        if ((1.0f + src.dotProduct(direction)) < 0.0001f) {
            //Ogre::LogManager::getSingletonPtr()->logMessage("180 Degree rotate");
            newNode->yaw(Ogre::Degree(180));
        } else {
        Ogre::Quaternion quat = src.getRotationTo(destination);
                    sceneManager.getSceneNode(name)->rotate(quat);
        } // else

    alive = true;
    notified = false;
    animationState = unit->getAnimationState("Walk");
    animationState->setLoop(true);
    animationState->setEnabled(true);
    speed = 1.0f;
    da = deathanimation;
}

Creep::Creep()
{
}

/**
    Destructor for a tower instance.
*/
Creep::~Creep()
{
    //dtor
}

/**
    Getter for the creep's health points.
*/
int Creep::getHP() {
    return hp;
}

/**
    Setter for the creep's health points.
    @param[in] newHP the health points the creep should be set too.
*/
void Creep::setHP(int newHP){
    hp = newHP;
}

Ogre::Vector3 Creep::getPosition(Ogre::SceneManager& sceneManager) {
    return sceneManager.getSceneNode(name)->getPosition();
}

/**
    logicals update of the creep.
    currently includes static animation, creep moves on set path.
    @param[out] &sceneManager SceneManager(Ogre3D) of the
*/
bool Creep::checkStatus(Ogre::SceneManager& sceneManager) {

        //sceneManager.getSceneNode(name)->setPosition(startPos);

    if(hp<=0)
        alive = false;

    if(!alive && !notified) {
        sceneManager.getSceneNode(name)->setVisible(false);
        notified = true;
        return false;
    }
    return true;
}


/**
    @returns false if a creep has made it to the finishing point
*/
bool Creep::updateMovement(Ogre::SceneManager& sceneManager) {
    Ogre::Vector3 pos = sceneManager.getSceneNode(name)->getPosition();

    if (direction == Ogre::Vector3::ZERO) //newly spawned creep
        {
            if (nextLocation(sceneManager)) //setup animation
            {
                // Set walking animation
                animationState = unit->getAnimationState("Walk");
                animationState->setLoop(true);
                animationState->setEnabled(true);
                animationState->addTime(1/120.0); //60th in float so return is float rather than int which would be 0.
            }
        }
    else //if creep is still moving to its next vertex/junction
     {
         Ogre::Real move = speed;
         distance -= move;
         animationState->addTime(1/120.0); //120th in float so return is float rather than int which would be 0.
         if (distance <= 0.0f) //if for some reason the creep has crossed the vertex/junction
             {
                 sceneManager.getSceneNode(name)->setPosition(destination);
                 direction = Ogre::Vector3::ZERO;

                 if (!nextLocation(sceneManager)) //and has made it to the finish end game.
                {
                    // Set Idle animation
                    animationState = unit->getAnimationState("Idle1"); //TODO: Idle without 1 for robot
                    animationState->setLoop(true);
                    animationState->setEnabled(true);
                    animationState->addTime(1/120.0);
                    return false;
                }
                else //set it to its next vertex/junction
                {
                    // Rotate to face next vertex/junction
                    Ogre::Vector3 src = sceneManager.getSceneNode(name)->getOrientation() * facingVector;
                    Ogre::Quaternion quat = src.getRotationTo(direction);
                    sceneManager.getSceneNode(name)->rotate(quat);
                }
            }

    else
     {
        //update position based on speed (calculated in move) if not at vertex
         sceneManager.getSceneNode(name)->translate(direction * move);
     } // else
    } // if
    return true;

}

bool Creep::nextLocation(Ogre::SceneManager& sceneManager){
if (junctions.empty())
             return false;

             destination = junctions.front();  // this gets the front of the deque
        junctions.pop_front();             // this removes the front of the deque

        direction = destination - sceneManager.getSceneNode(name)->getPosition();
        distance = direction.normalise();

	return true;
}
