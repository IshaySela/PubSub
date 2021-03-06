#include <string>
#include "../json.hpp"

#define HEADER_NAME_ENDPOINT_ID "Id"
#define HEADER_NAME_AUTH_SECRET "AuthSecret"

namespace PubSub
{
    namespace Protocol
    {
        /**
        * @brief Represents the subscribe to endpoint request 
        * <a href="4_subscribe-to-endpoint.json" target="_blank">implements Schema/4_subscribe-to-endpoint.json</a>
        */
        class SubscribeToEndpointRequest
        {
        public:
            SubscribeToEndpointRequest(std::string rawJson);
            SubscribeToEndpointRequest(const char* rawJson);
            ~SubscribeToEndpointRequest();

            std::string getId() const;
            std::string getAuthSecret() const;
        private:
            nlohmann::json json;
            std::string id;
            std::string authSecret;
            
            void getValuesFromJson();
        };
    }
} // namespace PubSub