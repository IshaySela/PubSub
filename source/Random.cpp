#include "headers/Util/Random.hpp"

namespace PubSub
{
    namespace Util
    {
        std::string randomString(const int len)
        {
            std::string tmp_s;
            static const char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";

            std::srand((unsigned)time(NULL) * getpid());

            tmp_s.reserve(len);
            for (int i = 0; i < len; ++i)
                tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];

            return tmp_s;
        }

        int randomInteger(int min, int max)
        {
            return std::rand() % max + min;
        }

    } // namespace Util
} // namespace PubSub