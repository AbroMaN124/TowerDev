#ifndef MAP_H
#define MAP_H

#include "vertex.h"
#include <vector>


class GameMap
{
    public:
        GameMap(int numOfVertices);
        virtual ~GameMap();
        vertex* getVertex(int index);
        vertex* getLastVertex();
    protected:
    private:
        std::deque<vertex*> vertices;
};

#endif // MAP_H
