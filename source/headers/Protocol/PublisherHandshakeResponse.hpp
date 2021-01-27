#ifndef PUBLISHER_HANDSHAKE_RESPONSE
#define PUBLISHER_HANDSHAKE_RESPONSE

#include <string>
#include "ResponseStatus.hpp"
#include "../Util/ISerializable.hpp"

namespace PubSub
{
    /**
    * @brief Response for the handshake of publisher client 
    * <a href="1_publisher-handshake-response.json" target="_blank">implements Schema/1.1_publisher-handshake-response.json</a>
    */
    namespace Protocol
    {
        class PublisherHandshakeResponse : public Util::ISerializable
        {
        public:
            PublisherHandshakeResponse(std::string id, ResponseStatus status);
            ~PublisherHandshakeResponse();

            std::string getId() const;
            
            void setResponseStatus(const ResponseStatus newStatus);
            ResponseStatus getResponseStatus() const;

            nlohmann::json toJson() const;
        private:
            std::string id;
            ResponseStatus status;
        };
        
        
    }
}

#endif
