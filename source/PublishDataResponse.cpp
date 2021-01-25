#include "headers/Protocol/PublishDataResponse.hpp"


namespace PubSub
{
    namespace Protocol
    {
        PublishDataResponse::PublishDataResponse(ResponseStatus status) : status(status) {}
        
        nlohmann::json PublishDataResponse::toJson() const
        {
            return {
                { "Status", this->status }
            };
        }
    }
}