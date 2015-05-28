#ifndef COMMON_H_
#define COMMON_H_


#include <string>
#include <stdlib.h>


std::string IntToString(int x)
{
    std::ostringstream temp;
    temp<<x;
    return temp.str();
}


#endif
