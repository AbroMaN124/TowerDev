#include "randomgenerator.h"

RandomGenerator::RandomGenerator()
{
    srand (time(NULL));
}

/**
    Returns a random int from a given range.
    rStart and rEnd are the start and end of the range the random should be within.
*/
int RandomGenerator::getRandom(int rStart, int rEnd) {
    return (int)((rand() % rEnd) + rStart);
}

RandomGenerator::~RandomGenerator()
{
    //dtor
}
