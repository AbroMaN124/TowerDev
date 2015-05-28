#include "mapfilehandler.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>

using namespace std;

MapFileHandler::MapFileHandler()
{
}

MapFileHandler::~MapFileHandler()
{
    //
}

deque<vertex*> MapFileHandler::parseMap() {
    //input file  stream for file storing adjecent list and coordinates of vertices
    ifstream mapFile ("map1.map");

    //temp for storing lines received from file
    string input;
    deque<vertex*> vertices;
    string tempChild;

    //store a line at a time to temp, removing any white spaces.
    //TODO: prevent tracing lines (extra lines at end of file)
    if(mapFile.is_open()) {
        //TODO: for report, if(coord.is_open()) { while( getline( coord, input ) ) {
        // reads an extra line
        while(getline(mapFile, input)) {

            //make sure its not end of file
                    Ogre::LogManager::getSingletonPtr()->logMessage(input);
                    //resize temp after white spaces are removed
                    string::iterator spaces = remove(input.begin(), input.end(), ' ');
                        input.erase(spaces, input.end());

                    //parse a character at a time
                    int i = 0; //index of position in input string
                    int cmember = 0;
                    int x, z;
                    deque<string> childenNames;
                    deque<vertex*> children;
                    string vertexName;
                    //get name of vertex
                    while(input[i]!= '=') {
                        //saves the char at end of currently created string and increases length by one
                        vertexName.push_back(input[i]);
                        i++;
                    }

                    i++; //the equals
                    //name finished, next is coordinates x and z

                    string tempCord;
                    while(input[i] != ',') {
                        tempCord.push_back(input[i]);
                        i++;
                    }
                    x = atoi(tempCord.c_str());
                    i++;


                    tempCord.clear();
                    while(input[i] != ';') {
                        tempCord.push_back(input[i]);
                        i++;
                    }
                    z = atoi(tempCord.c_str());
                    i++;

                    //Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::StringConverter::toString(i+1));

                    //itterate through deque to check if vertex exists, if not create.

                    //next is vertices this vertex can go to (directed)
                    //semicolon once list of vertices adjecent are complete

                    while(input[i] != ';') {
                        tempChild.clear();

                        //TODO: For report, had to replace OR operator with AND in while condition for reason in link:
                        //http://www.cplusplus.com/forum/beginner/60629/
                        while((input[i] != ',') && (input[i] != ';')) {
                            tempChild.push_back(input[i]);
                            i++;
                        }

                        if(input[i] == ',') {
                            i++;
                        }

                        childenNames.push_back(tempChild);
                    //Ogre::LogManager::getSingletonPtr()->logMessage(tempChild + Ogre::StringConverter::toString(i));

                    }
                    i++;

                    //adjecent list for vertex parsed

                    //Ogre::LogManager::getSingletonPtr()->logMessage("line parsed");

                    //add children
                    if(!childenNames.empty()) {
                        for(deque<string>::iterator kids = childenNames.begin(); kids!=childenNames.end(); ++kids) {
                            bool found = false;
                            for(deque<vertex*>::iterator cl = vertices.begin(); cl!=vertices.end(); ++cl) {
                                if((*kids) == (*cl)->name) {
                                    found = true;
                                    children.push_back((*cl));
                                }
                            }
                            if(!found) {
                            //exit(1);
                            }
                        }
                    }

                vertices.push_back(new vertex(x, z, children, vertexName)); /*
                Ogre::LogManager::getSingletonPtr()->logMessage("printing vertex data:");
                Ogre::LogManager::getSingletonPtr()->logMessage("name: " + vertexName);
                Ogre::LogManager::getSingletonPtr()->logMessage("coord: " + Ogre::StringConverter::toString(x) +
                "," + Ogre::StringConverter::toString(z));
                if(!children.empty()) {
                //TODO: make sure that none-connected nodes are not children (e.g. vertex d and a are not connected
                //but vertex d is a child of a.
                Ogre::LogManager::getSingletonPtr()->logMessage("child 1: " + children.front()->name);
                Ogre::LogManager::getSingletonPtr()->logMessage("its x: " +Ogre::StringConverter::toString(children.front()->xCor));
                Ogre::LogManager::getSingletonPtr()->logMessage("its z: " + Ogre::StringConverter::toString(children.front()->zCor));
                } */
        }
    }

    //changing file format to include the vertices in reverse (leaves first, so that this method is no longer required
    // this improving optimisation
    /*
    //update the children with the new vertices, rather then their holders
    for (std::deque<vertex*>::iterator it = vertices.begin(); it!=vertices.end(); ++it) {
        deque<vertex*> temp;
        temp = (*it)->childrenNodes;
        for (std::deque<vertex*>::iterator it2 = (*it)->childrenNodes.begin(); it2!=(*it)->childrenNodes.end(); ++it2) {
            for (std::deque<vertex*>::iterator it3 = vertices.begin(); it3!=vertices.end(); ++it3) {
                if((*it3)->name == (*it2)->name) {
                    (*it2)->xCor = (*it3)->xCor;
                    (*it2)->zCor = (*it3)->zCor;
                    (*it2)->childrenNodes = (*it3)->childrenNodes;
                }
            }
        }
    }
    */

    return vertices;

}
