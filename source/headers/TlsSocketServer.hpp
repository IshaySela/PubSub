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
    /**
     * @brief Listen to incoming connections and sorts the clients to publishers and subscriber, according to the handshake the client sends.
    */
    class TlsSocketServer
    {
    public:
        TlsSocketServer(int port);
        ~TlsSocketServer();

        /**
         * @brief Accepts clients, recive the handshake and handling the client accordingly.
        */
        void acceptClients();
        /**
         * @brief Add the string given to the disconnectedPublishsers list.
         * Note this function does not actually remove the publisher from the publishers map, but signals the cleaner thread to remove the publisher. 
         * @param id The id of the publisher to remove.
        */
        void removePublisher(std::string id);
    private:
        int port;
        ClientsFactoryBIO clientsFactory; ///< The main BIO the clients will connect to.
        std::unordered_map<std::string, std::unique_ptr<Publisher>> publishers; ///< A map of all of the publishers.

        std::vector<std::string> disconnectedPublishsers; ///< When a publisher is done, its id will be pushed into this array, for the publisher cleaner to remove.
        std::mutex disconnectedPublishsersLock; ///< The lock for the disconnectedPublishsers array

        /**
         * @brief Get the latest client and return it.
         * @returns The latest client.
        */
        ClientBIO acceptNewTcpConnection();

        /**
         * @brief Create a publisher and add it to the publishers list. Send the handshake response back to the client.
        */
        void handlePublisher(ClientBIO& socket);
        /**
         * @brief Create a subscriber and add it to requested publisher.
         * @param socket The socket of the subscriber.
         * @param handshake The handshake the client sent.
        */
        void handleSubscriber(ClientBIO& socket, Protocol::Handshake& handshake);

        /**
         * @brief Iterate over the disconnected publishers list and remove the dead connections.
        */
        void publishersCleaner();
    };
}

#endif