#ifndef TLS_SOCKET_SERVER
#define TLS_SOCKET_SERVER

#include <openssl/ssl.h>
#include <unordered_map>
#include <mutex>
#include "OpenSslErrors.hpp"
#include "UniquePtrWrapper.hpp"
#include "Publisher.hpp"
#include "Util/BioTypes.hpp"
#include "Protocol/Handshake.hpp"

#define MAX_HEADER_LENGTH 1024 * 4 // Set max header length to be 4 kb.

using PubSub::Util::ClientBIO;
using PubSub::Util::ClientsFactoryBIO;

namespace PubSub
{
    class Publisher;
    class TlsSocketServer
    {
    public:
        TlsSocketServer(int port);
        ~TlsSocketServer();
        

        void acceptClients();
        /**
         * @brief Add the string given to the disconnectedPublishsers list.
         * Note this function does not actually remove the publisher from the publishers map, but signals the cleaner thread to remove the publisher. 
         * @param std::string The id of the publisher to remove.
        */
        void removePublisher(std::string id);
    private:
        int port;
        ClientsFactoryBIO clientsFactory;
        std::unordered_map<std::string, std::unique_ptr<Publisher>> publishers;

        /**
         * When a publisher is done, its id will be pushed into this array, for the publisher cleaner to remove. 
        */
        std::vector<std::string> disconnectedPublishsers;
        // The lock for the disconnectedPublishsers array.
        std::mutex disconnectedPublishsersLock;

        ClientBIO acceptNewTcpConnection();
        
        void handlePublisher(ClientBIO& socket);
        void handleSubscriber(ClientBIO& socket, Protocol::Handshake& handshake);

        void publishersCleaner();
    };
}

#endif