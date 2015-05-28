/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "TutorialApplication.h"

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}


void TutorialApplication::createScene(void)
{


    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));

    /*Ogre::Entity* ninjaEntity = mSceneMgr->createEntity("Ninja", "ogrehead.mesh");
    Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("NinjaNode");
    node->attachObject(ninjaEntity);

     Ogre::Entity* ogreHead2 = mSceneMgr->createEntity( "Head2", "ogrehead.mesh" );
    Ogre::SceneNode* headNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode( "HeadNode2", Ogre::Vector3( 100, 0, 0 ) );
    headNode2->attachObject( ogreHead2 );*/

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

        Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);

    entGround->setMaterialName("Examples/Rockwall");
    entGround->setCastShadows(false);

    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(250, 150, 250));
    pointLight->setDiffuseColour(Ogre::ColourValue::White);
    pointLight->setSpecularColour(Ogre::ColourValue::White);

     Ogre::Entity* ogreHead3 = mSceneMgr->createEntity( "Head3", "ogrehead.mesh" );
            Ogre::SceneNode* headNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode( "HeadNode3", Ogre::Vector3( 0, 50, 0 ) );
            headNode3->attachObject( ogreHead3 );

            headNode3->flipVisibility();


}
//-------------------------------------------------------------------------------------

bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
    static int i = 5;
    static bool mMouseDown = false;     // If a mouse button is depressed
    static Ogre::Real mToggle = 0.0;    // The time left until next toggle
    static Ogre::Real mRotate = 0.13;   // The rotate constant
    static Ogre::Real mMove = 250;      // The movement constant

    Ogre::Vector3 transVe = Ogre::Vector3::ZERO;

    bool currMouse = mMouse->getMouseState().buttonDown(OIS::MB_Left);

    if (currMouse && !mMouseDown)
    {
        //Ogre::Light* light = mSceneMgr->getLight("pointLight");
        //light->setVisible(! light->isVisible());
        //i++;
        float lMouseX = float(mMouse->getMouseState().X.abs) / float(1280);
        float lMouseY = float(mMouse->getMouseState().Y.abs) / float(720);

        transVe.z -= lMouseX;

       // mSceneMgr->getSceneNode("HeadNode2")->translate(transVe, Ogre::Node::TS_LOCAL);


    /*
            Ogre::Entity* ogreHead3 = mSceneMgr->createEntity( "Head3", "ogrehead.mesh" );
            Ogre::SceneNode* headNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode( "HeadNode3", Ogre::Vector3( int(lMouseX), int(lMouseY), 0 ) );
            headNode3->attachObject( ogreHead3 );
            */

            mSceneMgr->getSceneNode("HeadNode3")->flipVisibility();
            //setVisible(! mSceneMgr->getSceneNode("ogreHead3")->isVisible());
        //isVisible

    }

    mMouseDown = currMouse;

    mToggle -= evt.timeSinceLastFrame;


    if ((mToggle < 0.0f ) && mKeyboard->isKeyDown(OIS::KC_1))
    {
        mToggle  = 0.5;
        Ogre::Light* light = mSceneMgr->getLight("pointLight");
        light->setVisible(! light->isVisible());
    }


    Ogre::Vector3 transVector = Ogre::Vector3::ZERO;

    if (mKeyboard->isKeyDown(OIS::KC_I)) // Forward
    {
        transVector.z -= mMove;
    }

    if (mKeyboard->isKeyDown(OIS::KC_K)) // Backward
    {
        transVector.z += mMove;
    }


    if (mKeyboard->isKeyDown(OIS::KC_L)) // Right - yaw or strafe
    {
        if(mKeyboard->isKeyDown( OIS::KC_LSHIFT ))
        {
            // Yaw right
            mSceneMgr->getSceneNode("HeadNode3")->yaw(Ogre::Degree(-mRotate));
        } else {
            transVector.x += mMove; // Strafe right
        }
    }

    if (mKeyboard->isKeyDown(OIS::KC_J)) // Left - yaw or strafe
    {
        if(mKeyboard->isKeyDown( OIS::KC_LSHIFT ))
        {
            // Yaw left
            mSceneMgr->getSceneNode("HeadNode3")->yaw(Ogre::Degree(mRotate));
        } else {
            transVector.x -= mMove; // Strafe left
        }
    }

    if (mKeyboard->isKeyDown(OIS::KC_U)) // Up
    {
        transVector.y += mMove;
    }
    if (mKeyboard->isKeyDown(OIS::KC_O)) // Down
    {
        transVector.y -= mMove;
    }




    mSceneMgr->getSceneNode("HeadNode3")->translate(transVector * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);



    return true;
}
//-------------------------------------------------------------------------------------
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    bool ret = BaseApplication::frameRenderingQueued(evt);


    if(!processUnbufferedInput(evt)) return false;

    return ret;
}
//-------------------------------------------------------------------------------------




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
        TutorialApplication app;

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
