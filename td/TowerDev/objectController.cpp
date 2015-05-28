#include "objectController.h"

#include "tower.h"
#include "creep.h"
#include "bullet.h"
#include "gameController.h"
#include "gameMap.h"
#include "common.h"

objectController::objectController()
{
    dn = 0;
    mToggle = 0;
    gMap = new GameMap(3);
    rand = new RandomGenerator();
}

objectController::~objectController()
{
    //dtor
}


/**
    Function initiliases the scene capable of use with ogre3D.
    It also creates the basic scene including the SceneManager(Ogre3D),
    Camera(Ogre3d), Viewport(Ogre3D), Lighting,
    Shadows and Plane.

*/
void objectController::createScene(Ogre::Root& mRoot, Ogre::RenderWindow& mWindow)
{


        mSceneMgr = mRoot.createSceneManager("DefaultSceneManager");
        Ogre::OverlaySystem* ols = new Ogre::OverlaySystem();

         mSceneMgr->addRenderQueueListener(ols);


    //size of map mapLength by mapLength
    mapLength = 1400;
        // Set default mipmap level (note: some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    // initialise all resource groups
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    // Create the SceneManager, in this case a generic one

 // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    mCamera->setPosition(Ogre::Vector3(400,500,1800));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    // set the near clip distance
    mCamera->setNearClipDistance(5);


    Ogre::Viewport* mViewport = mWindow.addViewport(mCamera);
    mViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
    Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));

    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");

    // Create a light
    Ogre::Light* l = mSceneMgr->createLight("MainLight");
    l->setPosition(20,80,-1800);

    Ogre::Light* sl = mSceneMgr->createLight("SelectLight");
    sl->setType(Ogre::Light::LT_POINT);
    sl->setPosition(0,20,0);
    lpos = Ogre::Vector3(sl->getPosition());
    //sl->setDiffuseColour(1.0, 1.0, 1.0);
    sl->setSpecularColour(1.0, 1.0, 1.0);
   // sl->setAttenuation(3250, 1.0, 0.0014, 0.000007);

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    plane, mapLength*2, mapLength*2, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

    Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);

    entGround->setMaterialName("Examples/Map01");
    entGround->setCastShadows(false);

    newCreepWave(2);

    bulletid = 0;
    towerreload = 120;

    //test text display on screen

         //Ogre::LogManager::getSingletonPtr()->logMessage("overlaymanager created");
         // Create a panel

/*
        Ogre::OverlayElement* textBox = overlayManager.createOverlayElement("TextArea", "txtBox");
        textBox->setDimensions( 0.1, 0.1 );
        textBox->setMetricsMode(Ogre::GMM_PIXELS);
        textBox->setPosition( 0, 0 );
        textBox->setWidth(0.1);
        textBox->setHeight(0.1);
        textBox->setParameter("font", "MyFont");
        textBox->setParameter("char_height", "0.3");
        textBox->setColour(Ogre::ColourValue(1.0, 1.0, 1.0, 0.5));

        textBox->setCaption("Hello World");

        panel->addChild(textBox);

        //bug test

        Ogre::OverlayContainer* panel2;
         panel2 = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "container2" ) );
         panel2->setPosition( 0.0, 0.0 );
         panel2->setDimensions( 0.1, 0.1 );
         panel2->setMaterialName( "Examples/GameOver" );


         overlay->add2D( panel2 );
         overlay->show();
         Ogre::OverlayElement* textBox2 = overlayManager.createOverlayElement("TextArea", "txtBox2");
        textBox2->setDimensions( 100, 20 );
        textBox2->setMetricsMode(Ogre::GMM_PIXELS);
        textBox2->setPosition( 10, 1 );
        textBox2->setWidth(100);
        textBox2->setHeight(20);
        textBox2->setParameter("font", "MyFont");
        textBox2->setParameter("char_height", "0.1");
        textBox2->setColour(Ogre::ColourValue(1.0, 1.0, 1.0, 0.5));

        textBox2->setCaption("Hello World");

        panel2->addChild(textBox2);

         overlay->show();


        textBox2->setCaption("Hello World");
        */
}

//TODO: do this in a seprate thread
/**
    Update loop of game. All logical update needs to be run in there.
    This includes receiving input and updating game logic.
*/
bool objectController::updateLogic(int level, gameController& gc)
{
    //TODO: Based on established time of game rather than using sleepstte

    //put this inside a function or better a different class
        //death = false;
        //lvlComplete = false;

        {std::list<typeOneTower*>::iterator j;
        //TODO: Change to only shooting nearest creep.
           for(j=eTowers.begin(); j != eTowers.end(); ++j) {
           //if !(*j)->hasTarget {get new target} else dont loop through, just attack
            if(towerreload == 120) { //once every 2 seconds

               for(std::list<ninjaCreep*>::iterator i=nCreeps.begin(); i != nCreeps.end(); ++i) {
                    tCreep = (*j)->UTarget(*tCreep, *(*i), *mSceneMgr);
               }

               for(std::list<robotCreep*>::iterator i=rCreeps.begin(); i != rCreeps.end(); ++i) {
                    tCreep = (*j)->UTarget(*tCreep, *(*i), *mSceneMgr);
               }
                (*j)->Attack(*tCreep, *mSceneMgr, "Bullet"+ IntToString(bulletid));
                bulletid++;
                towerreload = 0;
            }
            else
                {towerreload++;}

           (*j)->UpdateBullets(*mSceneMgr, *tCreep);
        } } //inclusion of j

        { std::list<typeTwoTower*>::iterator j;
        //TODO: Change to only shooting nearest creep.
           for(j=fTowers.begin(); j != fTowers.end(); ++j) {
           //if !(*j)->hasTarget {get new target} else dont loop through, just attack
            if(towerreload == 120) { //once every 2 seconds

               for(std::list<ninjaCreep*>::iterator i=nCreeps.begin(); i != nCreeps.end(); ++i) {
                    tCreep = (*j)->UTarget(*tCreep, *(*i), *mSceneMgr);
               }

               for(std::list<robotCreep*>::iterator i=rCreeps.begin(); i != rCreeps.end(); ++i) {
                    tCreep = (*j)->UTarget(*tCreep, *(*i), *mSceneMgr);
               }
                (*j)->Attack(*tCreep, *mSceneMgr, "Bullet"+ IntToString(bulletid));
                bulletid++;
                towerreload = 0;
            }
            else
                {towerreload++;}

           (*j)->UpdateBullets(*mSceneMgr, *tCreep);
        } }//inclusion of j

// check if dead
   { std::list<ninjaCreep*>::iterator i;
        for(i=nCreeps.begin(); i != nCreeps.end(); ++i) {
            if(!(*i)->checkStatus(*mSceneMgr)){ //creep dead
                //death = true; //TODO: crap code fix with something smart, if 2 bullets hit at once only 1 coin given - game breaking bug!
                creepCount--;
            }
        }} //inclusion of i

        {std::list<robotCreep*>::iterator i;
        for(i=rCreeps.begin(); i != rCreeps.end(); ++i) {
            if(!(*i)->checkStatus(*mSceneMgr)){ //creep dead
                //death = true; //TODO: crap code fix with something smart, if 2 bullets hit at once only 1 coin given - game breaking bug!
                creepCount--;
            }
        } } //inclusion of i


    if(creepCount<=0)  //level complete, levelup
        return false;

    return true;
}

bool objectController::creepMovement() {

    std::list<ninjaCreep*>::iterator i;
        for(i=nCreeps.begin(); i != nCreeps.end(); ++i) {
            if(!(*i)->updateMovement(*mSceneMgr)){ //game lost
                return false;
            }
        }

    {std::list<robotCreep*>::iterator i;
        for(i=rCreeps.begin(); i != rCreeps.end(); ++i) {
            if(!(*i)->updateMovement(*mSceneMgr)){ //game lost
                return false;
            }
        }}
    return true;

}

int objectController::getCreepCount() {
    return creepCount;
}

int objectController::rInput(OIS::Keyboard& mKeyboard) {
//TODO change lolwat
Ogre::Real speed = 10;
Ogre::Vector3 dir = mCamera->getDirection();
dir.normalise();

        //mCamera->move( dir*speed * evt.timeSinceLastFrame );
    if(mKeyboard.isKeyDown(OIS::KC_W))
        lpos.z -= 3;
    else if(mKeyboard.isKeyDown(OIS::KC_S))
        lpos.z += 3;
    else if(mKeyboard.isKeyDown(OIS::KC_A))
        lpos.x -= 3;
    else if(mKeyboard.isKeyDown(OIS::KC_D))
        lpos.x += 3;
    else if(mKeyboard.isKeyDown(OIS::KC_U))
        mCamera->pitch(Ogre::Degree(-0.5));//dir*speed);
    else if(mKeyboard.isKeyDown(OIS::KC_O))
        mCamera->pitch(Ogre::Degree(0.5));//-dir)*speed);
    else if(mKeyboard.isKeyDown(OIS::KC_I))
        mCamera->move(dir * speed);
    else if(mKeyboard.isKeyDown(OIS::KC_K))
        mCamera->move((-dir)  * speed);
    else if(mKeyboard.isKeyDown(OIS::KC_J)) {
        mCamera->yaw(Ogre::Degree(0.5)); }
    else if(mKeyboard.isKeyDown(OIS::KC_L)) {
        mCamera->yaw(Ogre::Degree(-0.5)); }


    mSceneMgr->getLight("SelectLight")->setPosition(lpos);

    mToggle++;

    if((mToggle>60) && (mKeyboard.isKeyDown(OIS::KC_1))){
        return 3;
    }
    else if((mToggle>60) && (mKeyboard.isKeyDown(OIS::KC_2))){
        return 4;
    }

    return 0;
}

void objectController::placeT1Tower() {
    eTowers.push_back(new typeOneTower(*mSceneMgr, lpos.x, 0, lpos.z, "Tower" + IntToString(dn)));
    dn++;
    mToggle = 0;
}

void objectController::placeT2Tower() {
    fTowers.push_back(new typeTwoTower(*mSceneMgr, lpos.x, 0, lpos.z, "TowerTwo" + IntToString(dn)));
    dn++;
    mToggle = 0;
}

/*std::string objectController::IntToString(int x)
{
    std::ostringstream temp;
    temp<<x;
    return temp.str();
}*/



void objectController::oGameLost(){
         panel->setMaterialName( "Examples/GameOver" );
         // Show the overlay
         overlay->show();
}

void objectController::oGameWon(){
         panel->setMaterialName( "Examples/GameOver" );
         // Show the overlay
         overlay->show();
}

void objectController::oStartGame(){
         panel->setMaterialName( "Examples/GameOver" ); //TODO: Replace
         // Show the overlay
         overlay->show();
}


void objectController::setupOverlay(){
        Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
         // Create an overlay

         panel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "container1" ) );
         panel->setPosition( 0.0, 0.0 );
         panel->setDimensions( 0.1, 0.1 );
         //panel->setMaterialName( "Examples/GameOver" );

         // Add the panel to the overlay
         overlay = overlayManager.create( "overlay1" );
         overlay->add2D( panel );

         // Show the overlay
         //overlay->show();

}

void objectController::hideOverlay() {
    overlay->hide();
}



void objectController::newCreepWave(int numOfCreeps) {
    //Delete objects before clear
    nCreeps.clear();
    rCreeps.clear();
    for(int i = 0; i < numOfCreeps; i++) {
        if(i>2) {
            rCreeps.push_back(new robotCreep(*mSceneMgr, 1200+((i+1)*100), 0, 0,
            "Creep"+IntToString(dn)+"x"+IntToString(i), gMap->getLastVertex(), *rand));
        }
        else {
            nCreeps.push_back(new ninjaCreep(*mSceneMgr, 1200+((i+1)*100), 0, 0,
            "Creep"+IntToString(dn)+"x"+IntToString(i), gMap->getLastVertex(), *rand));
        }
    }
    tCreep = nCreeps.front();
    dn++;
    creepCount = numOfCreeps;
}
