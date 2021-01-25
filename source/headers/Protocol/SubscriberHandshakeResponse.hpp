#include "../Util/ISerializable.hpp"
#include <string>

#define HEADER_NAME_ID "Id"

namespace PubSub
{
    namespace Protocol
    {
        class SubscriberHandshakeResponse : public Util::ISerializable
        {
        public:
            SubscriberHandshakeResponse(std::string id);
            ~SubscriberHandshakeResponse();

            std::string getId() const;
            nlohmann::json toJson() const;
        private:
            std::string id;
        };
               
    }
}