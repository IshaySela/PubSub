#include "headers/Protocol/SubscriberHandshakeResponse.hpp"

namespace PubSub
{
    namespace Protocol
    {
        SubscriberHandshakeResponse::SubscriberHandshakeResponse(std::string id) : id(id) {}
        SubscriberHandshakeResponse::~SubscriberHandshakeResponse() {}

        std::string SubscriberHandshakeResponse::getId() const { return this->id; }
        nlohmann::json SubscriberHandshakeResponse::toJson() const
        {
            return {
                {HEADER_NAME_ID, this->id}
            };
        }
    } // namespace Protocol
} // namespace PubSub