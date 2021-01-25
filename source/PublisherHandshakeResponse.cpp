#include "headers/Protocol/PublisherHandshakeResponse.hpp"

namespace PubSub
{
    namespace Protocol
    {
        PublisherHandshakeResponse::PublisherHandshakeResponse(std::string id, ResponseStatus status) : id(id), status(status)
        {
        }
        PublisherHandshakeResponse::~PublisherHandshakeResponse() {}
        
        std::string PublisherHandshakeResponse::getId() const
        {
            return this->id;
        }

        void PublisherHandshakeResponse::setResponseStatus(const ResponseStatus status)
        {
            this->status = status;
        }

        ResponseStatus PublisherHandshakeResponse::getResponseStatus() const
        {
            return this->status;
        }

        nlohmann::json PublisherHandshakeResponse::toJson() const 
        {
            return {
                { "status", this->status },
                { "id", this->id.c_str() }
            };
        }
    }
}