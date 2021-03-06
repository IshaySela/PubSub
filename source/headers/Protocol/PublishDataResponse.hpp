#include "../Util/ISerializable.hpp"
#include "ResponseStatus.hpp"

namespace PubSub
{
    namespace Protocol
    {
        /**
        * @brief The response for publish data request 
        * <a href="3_publish-data-response.json" target="_blank">implements Schema/3_publish-data-response.json</a>
        */
        class PublishDataResponse : public Util::ISerializable
        {
        public:
            PublishDataResponse(ResponseStatus status);
            nlohmann::json toJson() const;
        private:
            ResponseStatus status;
        };
    }
}