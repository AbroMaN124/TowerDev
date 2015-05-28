#include "creepcontainer.h"


creepContainer::creepContainer(ninjaCreep* creep)
{
    //ninja
    creepCont.ninja = creep;
}

creepContainer::creepContainer(robotCreep* creep)
{
    //creep
    creepCont.robot = creep;
}


creepContainer::~creepContainer()
{
    //dtor
}
