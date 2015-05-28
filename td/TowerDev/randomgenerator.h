#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <ctime>
#include <stdlib.h>


class RandomGenerator
{
    public:
        RandomGenerator();
        virtual ~RandomGenerator();
        int getRandom(int rStart, int rEnd);
    protected:
    private:

};

#endif // RANDOMGENERATOR_H
