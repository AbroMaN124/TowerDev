#ifndef CREEPCONTAINER_H
#define CREEPCONTAINER_H

#include "robotcreep.h"
#include "ninjacreep.h"
class creepContainer
{
    public:
        creepContainer();
        creepContainer(ninjaCreep* creep);
        creepContainer(robotCreep* creep);
        virtual ~creepContainer();
        int getType();
        void setType(int x);
    protected:
    private:
        int valueType; //1=ninja, 2=robot
        union {
            ninjaCreep* ninja;
            robotCreep* robot;
        } creepCont;
};

#endif // CREEPCONTAINER_H
