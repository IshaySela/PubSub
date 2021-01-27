#ifndef HANDSHAKE
#define HANDSHAKE

#include "../json.hpp"
#include "ClientType.hpp"

#define HEADER_NAME_CLIENT_TYPE "ClientType"
#define HEADER_NAME_AUTHENTICATION_SECRET "AuthSecret"
#define HEADER_NAME_SHOULD_ENCRYPT "Encrypt"
#define HEADER_NAME_ENCRYPTION_STRING "EncryptionString"

using Json = nlohmann::json;

namespace PubSub
{
    namespace Protocol
    {
        /**
        * @brief The handshake class wrapps the json object recived from the client, and creates simple ways to access the headers information.
        * Implmenets /Schema/0_handshake.json
        */
        class Handshake
        {
        public:
            Handshake(const std::string &raw);
            Handshake(const char *raw);

            /**
            * @brief Chek if the json object is valid.
            * @returns boolean. true if the json contains all required keys, false otherwise.
            */
            bool validHeaders();

            bool getShouldEncrypt() const;
            std::string getAuthenticationSecret() const;
            std::string getEncryptionString() const;
            ClientType getClientType() const;

            template <typename T>
            T get(const char* headerName);

            /**
            * Create a handshake class, and throw runtime error if the json is not validate. 
            */
            static Handshake createAndThrow(const std::string &json);
            static Handshake createAndThrow(const char *json);

        private:
            Json json; ///< The raw json object of the class.
            bool shouldEncrypt;
            ClientType clientType;
            std::string authenticationSecret;
            std::string encryptionString;

            /**
            * @brief Set all default headers to their default values (if they do not exists in the json) 
            */
            void setDefaultHeadersForJson();
            /**
            * @brief Get all of the headers from the json into their variables. 
            */
            void setHeadersFromJson();
        };

        template <typename T>
        T Handshake::get(const char* headerName)
        {
            return this->json[headerName].get<T>();
        }

    } // namespace Protocol

} // namespace PubSub

#endif