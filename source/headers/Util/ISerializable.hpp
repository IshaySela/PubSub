#ifndef ISERIALIZABLE_UTIL
#define ISERIALIZABLE_UTIL

#include "../json.hpp"

namespace PubSub
{
    namespace Util
    {
        class ISerializable
        {
        public:
            virtual nlohmann::json toJson() const = 0;
        };
    }
}

#endif