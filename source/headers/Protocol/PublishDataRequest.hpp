#ifndef PUBLISH_REQUEST
#define PUBLISH_REQUEST

#define HEADER_NAME_PAYLOAD_LENGTH "Length"
#define HEADER_NAME_DATA_TYPE "DataType"

#include "../json.hpp"
#include "../Util/ISerializable.hpp"
#include <string>

namespace PubSub
{
    namespace Protocol
    {
        /**
        * @brief The request headers for publishing data to the clients.
        * <a href="2_publish-data.json" target="_blank">implements /Schema/2_publish-data.json</a>
        */
        class PublishDataRequest : public Util::ISerializable
        {
        public:
            PublishDataRequest(std::string raw);
            PublishDataRequest(const char* raw);
            ~PublishDataRequest();

            int getPayloadLength() const;
            std::string getPayloadType() const;

            nlohmann::json toJson() const;
        private:
            nlohmann::json json;
            int payloadLength = 0;
            std::string paylaodType;

            void getValuesFromJson();
        };
        
    }
}

#endif