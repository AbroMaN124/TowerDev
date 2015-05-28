#include "bullet.h"

bullet::bullet(std::string id, Ogre::Vector3 destination, Ogre::SceneManager& sceneManager, Ogre::Vector3 position)
{


    //Ogre::LogManager::getSingletonPtr()->logMessage("*** Fired ***");
    speed = 20.0f;
    direction = Ogre::Vector3::ZERO;
    dest = destination;
    dest.y += 150;
    name = id;
    pos = position;
    pos.y += 200;

   Ogre::Entity* unit = sceneManager.createEntity(id, "sphere.mesh");
   Ogre::SceneNode* newNode = sceneManager.getRootSceneNode()->createChildSceneNode( id, Ogre::Vector3( 0, 0, 0 ) );
    newNode->attachObject(unit);
    newNode->setPosition(pos);
    newNode->scale(0.1f,0.1f,0.1f);

    direction = dest - pos;
    distance = direction.normalise();


}

bullet::~bullet()
{
    //dtor
}

//true = finished
bool bullet::Update(Ogre::SceneManager& sceneManager, Creep& creep)
{

    if(direction != Ogre::Vector3::ZERO) {
        distance -= speed;
        if(distance <= 0.0f) { //when bullet hits creep
            direction = Ogre::Vector3::ZERO;
            sceneManager.getSceneNode(name)->setVisible(false);
            creep.setHP(creep.getHP()-25);
            return false; //delete bullet finished
        }
        else {
            sceneManager.getSceneNode(name)->translate(direction * speed);
        }
    }

    return true;
}
