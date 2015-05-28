#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include <OgreRoot.h>
#include "typeonetower.h"
#include "typetwotower.h"
#include "tower.h"
#include "creep.h"
#include <list>
#include "bullet.h"
#include "gameController.h"
#include "ninjacreep.h"
#include "robotcreep.h"
#include "gameMap.h"
//#include "common.h"
#include "camera.h"
#include "randomgenerator.h"


#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <OgreOverlayManager.h>
#include <OgreOverlaySystem.h>
#include "OgreTextAreaOverlayElement.h"

class gameController;

class objectController
{
    public:
        objectController();
        virtual ~objectController();
        void createScene(Ogre::Root& mRoot);
        bool updateLogic(int level, gameController& gc);
        int rInput(OIS::Keyboard& mKeyboard);
        void createScene(Ogre::Root& mRoot, Ogre::RenderWindow& mWindow);
        //std::string IntToString (int x);
        void newCreepWave(int numOfCreeps);
        void placeT1Tower();
        void placeT2Tower();
        int getCreepCount();
        bool creepMovement();
        void oGameLost();
        void oGameWon();
        void oStartGame();
        void setupOverlay();
        void hideOverlay();

    protected:
    private:
    Ogre::SceneManager* mSceneMgr;
    Ogre::Camera *mCamera;

    GameMap* gMap;
    Tower* tempTower;
    Creep* tempCreep;
    Creep* tCreep;
    //for robots
    Creep* tCreep2;
    std::list<ninjaCreep*> nCreeps;
    std::list<robotCreep*> rCreeps;
    std::list<typeOneTower*> eTowers;
    std::list<typeTwoTower*> fTowers;

    int creepCount;

    bullet* testBullet;

    int hp;
    int dn; //dynamic name

    //size of map in pixels
    float mapLength;

    int bulletid;
    int towerreload;

    int mToggle;

    //selectlight coordinates
    Ogre::Vector3 lpos;

    Ogre::OverlayContainer* panel;
    Ogre::Overlay* overlay;

    RandomGenerator* rand;
};

#endif // OBJECTCONTROLLER_H
