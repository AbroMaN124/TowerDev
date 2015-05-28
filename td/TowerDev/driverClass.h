#include "tower.h"
#include "creep.h"
#include <OgreRoot.h>
#include <list>
#include "bullet.h"
#include "objectController.h"
#include "gameController.h"
//#include "OgreText.h"
//#include "OgreText2.h"
#include "gamestatemanager.h"

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreWindowEventUtilities.h>

class DriverClass : public Ogre::FrameListener, public Ogre::WindowEventListener
{
public:
    DriverClass(void);
    virtual ~DriverClass(void);
    bool go(void);
    protected:
    // Ogre::FrameListener
    //virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    void initialiseOIS();
    bool runGame();
    unsigned long GetMillisecondsTime();


    // Ogre::WindowEventListener
    virtual void windowResized(Ogre::RenderWindow* rw);
    virtual void windowClosed(Ogre::RenderWindow* rw);

    private:

    Ogre::Root* mRoot;
    Ogre::String mPluginsCfg;
    Ogre::String mResourcesCfg;
    Ogre::RenderWindow* mWindow;
    objectController* objController;
    gameController* gController;
    //GameMap* plane;

    // OIS Input devices
    OIS::InputManager* mInputManager;
    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;

    unsigned long oldTime;
    unsigned long newTime;
    unsigned long timeElapsed;

    bool tick; //triggers update loop
    bool gameover;

    int tower;

    gameStateManager* gsManager;

//    OgreBites::Label* mInfoLabel;


};
