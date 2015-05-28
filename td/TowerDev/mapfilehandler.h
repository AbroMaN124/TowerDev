#ifndef MAPFILEHANDLER_H
#define MAPFILEHANDLER_H

#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include <OgreRoot.h>

#include <deque>
#include "vertex.h"

class MapFileHandler
{
    public:
        MapFileHandler();
        virtual ~MapFileHandler();
        std::deque<vertex*> parseMap();
    protected:
    private:
};

#endif // MAPFILEHANDLER_H
