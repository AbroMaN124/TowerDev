#include "gameMap.h"
#include "mapfilehandler.h"


#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include <vector>
#include <deque>

/** \class GameMap
    \brief class for map

    This is to class used to create the map.
    Currently not implemented.
*/
GameMap::GameMap(int numOfVertices) //TODO: File
{
    MapFileHandler* m = new MapFileHandler();
    Ogre::LogManager::getSingletonPtr()->logMessage("MapFileHandler created!");
    vertices = m->parseMap();


        Ogre::LogManager::getSingletonPtr()->logMessage("# of vertices: " + Ogre::StringConverter::toString(vertices.size()));

        for (std::deque<vertex*>::iterator it = vertices.begin(); it!=vertices.end(); ++it) {
            Ogre::LogManager::getSingletonPtr()->logMessage((*it)->name +
            Ogre::StringConverter::toString((*it)->xCor) +
            Ogre::StringConverter::toString((*it)->zCor));

    }
   // }
}

vertex* GameMap::getVertex(int index) {
    return vertices[index];
}


vertex* GameMap::getLastVertex() {
    return vertices.back();
}

GameMap::~GameMap()
{
    //dtor
}
