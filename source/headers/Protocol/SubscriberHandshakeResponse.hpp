#include "../Util/ISerializable.hpp"
#include <string>

#define HEADER_NAME_ID "Id"

namespace PubSub
{
    namespace Protocol
    {
        /**
        * @brief The handshake response for a subscriber. Based on 
        * <a href="1.2_subscriber-handshake-response.json" target="_blank">implements /Schema/1.2_subscriber-handshake-response.json</a>
        */
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