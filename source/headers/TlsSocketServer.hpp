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
        void removePublisher(std::string publisherId);
    private:
        int port;
        ClientsFactoryBIO clientsFactory;
        // This mutex is used to remove publishers by other threads.
        std::mutex publishersRemoveLock;
        std::unordered_map<std::string, std::unique_ptr<Publisher>> publishers;

        ClientBIO acceptNewTcpConnection();

        std::string getHeaders(ClientBIO& socket);
        
        void handlePublisher(ClientBIO& socket);
        void handleSubscriber(ClientBIO& socket, Protocol::Handshake& handshake);
    };   
}

#endif