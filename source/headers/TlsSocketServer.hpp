#ifndef TLS_SOCKET_SERVER
#define TLS_SOCKET_SERVER

#include <openssl/ssl.h>
#include <unordered_map>
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
    class TlsSocketServer
    {
    public:
        TlsSocketServer(int port);
        ~TlsSocketServer();
        

        void acceptClients();
    private:
        int port;
        ClientsFactoryBIO clientsFactory;
        std::unordered_map<std::string, std::unique_ptr<Publisher>> publishers;

        ClientBIO acceptNewTcpConnection();

        std::string getHeaders(ClientBIO& socket);
        
        void handlePublisher(ClientBIO& socket);
        void handleSubscriber(ClientBIO& socket, Protocol::Handshake& handshake);
    };   
}

#endif