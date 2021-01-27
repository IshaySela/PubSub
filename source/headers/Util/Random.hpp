#ifndef RANDOM_UTIL
#define RANDOM_UTIL

#include <iostream>
#include <ctime>
#include <unistd.h>

namespace PubSub
{
    namespace Util
    {
        /**
        * @brief Create random string.
        *@param len The size of the string.
        *@returns A random string of the size len.
        */
        std::string randomString(const int len);

        /**
        * @brief Create random integer.
        *@param min The minimum value of the number.
        *@param max The maximum vakue of the number.
        *@returns A random number between min and max.
        */
        int randomInteger(int min = 0, int max = RAND_MAX);
    } // namespace Util
} // namespace PubSub

#endif