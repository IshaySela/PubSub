#ifndef PUBLISHER
#define PUBLISHER
#include <string>
#include <unordered_map>
#include <future>

#include "Util/BioTypes.hpp"
#include "TlsSocketServer.hpp"
#include "Subscriber.hpp"


using PubSub::Util::ClientBIO;

namespace PubSub
{
    using SubscribersMap = std::unordered_map<std::string, std::unique_ptr<Subscriber>>;
    class TlsSocketServer;
    class Publisher
    {
    public:
        Publisher(std::string id, ClientBIO socket, TlsSocketServer& server);
        ~Publisher();

        void setClient(ClientBIO client);
        std::string getId() const;
        /*
        * @brief Add new subscriber to the subscribers list. 
        * @returns The id of the new subscriber.
        */
        void addNew(std::unique_ptr<Subscriber> subscriber, std::string id);

        /*
        * Start the worker thread.
        */
        void start();

        /**
         * @brief emit the buffer to all of the subscribers.
        */
        std::future<void> emit(const char *buffer, size_t size);

    private:
        std::string id;
        SubscribersMap subscribers;
        std::shared_future<void> workerFtr;
        ClientBIO client;
        
        /**
         * Reference to the server. This object will be used to remove the publisher once the worker is done.
        */
        TlsSocketServer& server;

        /**
         * @brief listen to the socket and emit all of the values to the clients.
        */
        void worker();
    };
} // namespace PubSub

#endif