#include "../Util/ISerializable.hpp"
#include "ResponseStatus.hpp"

namespace PubSub
{
    namespace Protocol
    {
        /**
         * @brief The response for publish data request. Based on Schema/3_publish-data-response.json.
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