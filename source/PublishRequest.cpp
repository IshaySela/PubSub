#include "headers/Protocol/PublishDataRequest.hpp"


namespace PubSub
{
    namespace Protocol
    {
        PublishDataRequest::PublishDataRequest(std::string rawJson) : json(nlohmann::json::parse(rawJson))
        {
            this->getValuesFromJson();
        }

        PublishDataRequest::~PublishDataRequest() {}

        PublishDataRequest::PublishDataRequest(const char* rawJson) : json(nlohmann::json::parse(rawJson))
        {
            this->getValuesFromJson();
        }

        void PublishDataRequest::getValuesFromJson()
        {
            this->payloadLength = this->json[HEADER_NAME_PAYLOAD_LENGTH].get<int>();
            this->paylaodType = this->json[HEADER_NAME_DATA_TYPE].get<std::string>();
        }

        nlohmann::json PublishDataRequest::toJson() const 
        {
            // TODO: Add all headers starting with X and their values.
            return {
                { HEADER_NAME_PAYLOAD_LENGTH, this->payloadLength },
                { HEADER_NAME_DATA_TYPE, this->paylaodType }
            };
        }

        int PublishDataRequest::getPayloadLength() const { return this->payloadLength; }
        std::string PublishDataRequest::getPayloadType() const { return this->paylaodType; }
    }
}