#include "headers/Protocol/Handshake.hpp"

namespace PubSub
{
    namespace Protocol
    {
        Handshake::Handshake(const std::string& raw)
        {
            this->json = Json::parse(raw);
            this->setDefaultHeadersForJson();
            this->setHeadersFromJson();
        }

        Handshake::Handshake(const char *raw)
        {
            this->json = Json::parse(raw);
            this->setDefaultHeadersForJson();
        }

        bool Handshake::validHeaders()
        {
            auto clientType = this->json[HEADER_NAME_CLIENT_TYPE].get<ClientType>();
            // if should encrypt is set, an encryption string needed to be provided.
            bool validEncryptionSettings = (!this->json[HEADER_NAME_SHOULD_ENCRYPT].empty() && !this->json[HEADER_NAME_ENCRYPTION_STRING].empty());

            return (clientType == ClientType::Publisher || clientType == ClientType::Subscriber) 
                && validEncryptionSettings 
                && this->json[HEADER_NAME_AUTHENTICATION_SECRET].is_string()
                && this->json[HEADER_NAME_SHOULD_ENCRYPT].is_boolean();
        }

        void Handshake::setDefaultHeadersForJson()
        {
            if(this->json[HEADER_NAME_AUTHENTICATION_SECRET].empty()) this->json[HEADER_NAME_AUTHENTICATION_SECRET] = "";
            if(this->json[HEADER_NAME_SHOULD_ENCRYPT].empty()) this->json[HEADER_NAME_SHOULD_ENCRYPT] = false;
            if(this->json[HEADER_NAME_ENCRYPTION_STRING].empty()) this->json[HEADER_NAME_ENCRYPTION_STRING] = "";
        }

        bool Handshake::getShouldEncrypt() const { return this->shouldEncrypt; }
        std::string Handshake::getAuthenticationSecret() const { return this->authenticationSecret; }
        std::string Handshake::getEncryptionString() const { return this->encryptionString; }
        ClientType Handshake::getClientType() const { return this->clientType; }

        
        Handshake Handshake::createAndThrow(const std::string& raw)
        {
            auto header = Handshake(raw);

            if(!header.validHeaders()) throw std::runtime_error("Invalid headers.");
            
            return header;
        }

        void Handshake::setHeadersFromJson()
        {
            this->shouldEncrypt = this->json[HEADER_NAME_SHOULD_ENCRYPT].get<bool>();
            this->authenticationSecret = this->json[HEADER_NAME_AUTHENTICATION_SECRET].get<std::string>();
            this->encryptionString = this->json[HEADER_NAME_ENCRYPTION_STRING].get<std::string>();
            this->clientType = this->json[HEADER_NAME_CLIENT_TYPE].get<Protocol::ClientType>();
        }

    } // namespace Protocol
} // namespace PubSub