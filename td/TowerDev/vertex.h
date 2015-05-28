#ifndef VERTEX_H
#define VERTEX_H


#include <deque>
#include <string>

using namespace std;

//TODO: change to a class with private variables rather than a struct in a header file.

struct vertex {
    string name;
    int xCor, zCor;
    deque<vertex*> childrenNodes;

    vertex(int x, int z, deque<vertex*> children, string id) {
        name = id;
        xCor = x;
        zCor = z;
        childrenNodes = children;
    }

    vertex(int x, int z) {
        xCor = x;
        zCor = z;
    }

    vertex(string id) {
        name = id;
    }
};


#endif // VERTEX_H
