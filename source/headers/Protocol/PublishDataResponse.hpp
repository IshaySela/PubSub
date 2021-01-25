#include "../Util/ISerializable.hpp"
#include "ResponseStatus.hpp"

namespace PubSub
{
    namespace Protocol
    {
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