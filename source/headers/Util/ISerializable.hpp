#ifndef ISERIALIZABLE_UTIL
#define ISERIALIZABLE_UTIL

#include "../json.hpp"

namespace PubSub
{
    namespace Util
    {
        /**
         * @brief interface for serializing object to json.
        */
        class ISerializable
        {
        public:
            /**
             * @brief virtual function for converting this object to json object.
             * @returns json representation of this class.
            */
            virtual nlohmann::json toJson() const = 0;
        };
    }
}

#endif