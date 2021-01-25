#ifndef RANDOM_UTIL
#define RANDOM_UTIL

#include <iostream>
#include <ctime>
#include <unistd.h>

namespace PubSub
{
    namespace Util
    {
        std::string randomString(const int len);
        int randomInteger(int min = 0, int max = RAND_MAX);
    } // namespace Util
} // namespace PubSub

#endif