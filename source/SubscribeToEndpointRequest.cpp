#include "headers/Protocol/SubscribeToEndpointRequest.hpp"


namespace PubSub
{
    namespace Protocol
    {
        SubscribeToEndpointRequest::SubscribeToEndpointRequest(std::string raw) : json(nlohmann::json::parse(raw)) {}
        SubscribeToEndpointRequest::SubscribeToEndpointRequest(const char* raw) : json(nlohmann::json::parse(raw)) {}


        std::string SubscribeToEndpointRequest::getId() const { return this->id; }
        std::string SubscribeToEndpointRequest::getAuthSecret() const { return this->authSecret; }

        void SubscribeToEndpointRequest::getValuesFromJson() 
        {
            this->id = this->json[HEADER_NAME_ENDPOINT_ID].get<std::string>();
            auto authSecretJson = this->json[HEADER_NAME_AUTH_SECRET];

            this->authSecret = authSecretJson.empty() ? "" : authSecretJson.get<std::string>();
        }
    }
}