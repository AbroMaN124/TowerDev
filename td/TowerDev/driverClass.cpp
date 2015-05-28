#include "driverClass.h"

#include <SdkTrays.h>
#include <SdkCameraMan.h>

#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>

#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include <OgreMeshManager.h>
#include <unistd.h>
#include <ctime>

#include "tower.h"
#include "creep.h"
#include "bullet.h"
#include "OgreText.h"
#include "objectController.h"
#include "gameController.h"

#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>

#include <sys/time.h>
#include <sstream>


//TODO: change scenemanager to a singleton instance.
/** \class DriverClass
    \brief driver class for game.

    This is to driver class for the program. It contains the main() function.
*/

/**
    Constructor for DriverClass.
*/
//-------------------------------------------------------------------------------------
DriverClass::DriverClass(void)
 : mRoot(0),
	mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK)
{
}
//-------------------------------------------------------------------------------------
/**
    Destructor for DriverClass.
*/
DriverClass::~DriverClass(void)
{
    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot; //TODO: delete stuff like here! :)
}

/**
    Startup of game, ran by main().
*/
bool DriverClass::go(void)
{

#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif
    gameover = false;
    // construct Ogre::Root
    mRoot = new Ogre::Root(mPluginsCfg);

    // set up resources
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }

    // configure
    // Show the configuration dialog and initialise the system
    if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
    {
        return false;
    }

    gsManager = new gameStateManager();
    gsManager->setState(1);

    mWindow = mRoot->initialise(true, "Tower Defence Game");

    gController = new gameController();
    objController = new objectController();
    initialiseOIS();

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    oldTime = GetMillisecondsTime();

    objController->createScene(*mRoot, *mWindow);
    objController->setupOverlay();

    //gameloop
    while(true)
    {
        //capture input at every tick
        mKeyboard->capture();
        mMouse->capture();

        //update elapsed time at every tick
        newTime = GetMillisecondsTime();
        timeElapsed = timeElapsed + (newTime - oldTime);

        //check if logic should be executed at this tick
        if(timeElapsed > 33.0) { //16.6 = 1/60th of a second (in milliseconds). //TODO remove random number
            timeElapsed =  timeElapsed - 33.0;
            tick = true;
        }

        if(tick){ //update logic
            switch(gsManager->getState()) {
                case 1: //pre-game, press space to start
                    if(mKeyboard->isKeyDown(OIS::KC_SPACE)) {
                        gsManager->setState(2);
                    }
                    objController->oStartGame();
                    break;
                case 2: //ingame
                    objController->hideOverlay();
                    if(!runGame()) //returns false if game is lost
                       gsManager->setState(3);
                    break;
                case 3: //game lost
                    objController->oGameLost();
                    break;
                case 4: //game won
                    objController->oGameWon();
                    break;
            }
        }

        // Pump window messages as we are not using startRendering()
        Ogre::WindowEventUtilities::messagePump();

        // Render a frame, exit if fail
        if(!mRoot->renderOneFrame())
            return false;

         //if exit
        if(mWindow->isClosed())
                return false;

        //if escape pressed exit
        if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
            return false;

        oldTime = newTime;
    }

    return true;
}


/**
    @returns false if the game is lost
*/
bool DriverClass::runGame() {
    tick = false;
                //framerate = 1/60th of second i.e. 60 fps
                //TODO: multi-threading

                //update loop
                if(!objController->updateLogic(gController->getLevel(), *gController)) {
                    gController->upLevel(*objController);
                //go next level if creeps are all dead (return false)
                }

                if(!objController->creepMovement()) {
                    return false;
                }

                tower = objController->rInput(*mKeyboard);
                if(tower == 3) {
                    gController->placeTower(3,*objController);
                } else if(tower == 4) {
                    gController->placeTower(4,*objController);
                }

                if(gController->getLevel() == 6 && !gameover) {
                    //update currency when tower is placed.
                    gsManager->setState(4);
                    //gameover = true;
                }
            return true;
}

/**
    Initilaises the Object Oriented Input System. This library used to create the game window and receive keyboard/mouse input.
*/
void DriverClass::initialiseOIS()
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, false ));

}


//Adjust mouse clipping area
/**
    Sets mouse clipping area based on window size.
*/
void DriverClass::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

//Unattach OIS before window shutdown (very important, or there is no way to exit!)
/**
    Function needs to run uninitialise OIS for successful window,
    else window can not be closed(and stays in fullscreen! hard restart required!)
*/
void DriverClass::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created the OIS
    if(rw == mWindow)
    {
        if(mInputManager)
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}

unsigned long DriverClass::GetMillisecondsTime()
{
   struct timeval tv;
   if(gettimeofday(&tv, NULL) != 0) return 0;
   return (unsigned long)((tv.tv_sec * 1000ul) + (tv.tv_usec / 1000ul));
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        DriverClass app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
