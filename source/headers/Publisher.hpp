#ifndef PUBLISHER
#define PUBLISHER
#include <string>
#include <unordered_map>
#include <future>
#include <atomic>

#include "Util/BioTypes.hpp"
#include "TlsSocketServer.hpp"
#include "Subscriber.hpp"


using PubSub::Util::ClientBIO;

namespace PubSub
{
    using SubscribersMap = std::unordered_map<std::string, std::unique_ptr<Subscriber>>;
    
    class TlsSocketServer;

    /**
     * @brief The class publisher listens for data from the client and emits it to all of the subscribers. 
    */
    class Publisher
    {
    public:
        Publisher(std::string id, ClientBIO socket, TlsSocketServer& server);
        ~Publisher();

        void setClient(ClientBIO client);
        std::string getId() const;
        /**
         * @brief return the status of the worker, atomically
        */
        bool isWorkerDone() const;

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
        std::string id; ///< The id of the publisher, as stored in the publishers map of the server object.
        SubscribersMap subscribers; ///< Map of all of the subscribers.
        std::shared_future<void> workerFtr; ///< The future of the worker thread. This makes sure that when the publisher is removed, the worker thread will exit gracefully. 
        ClientBIO client; ///< The socket of the client.
        std::atomic<bool> workerDone; ///< TODO: Remove.
        TlsSocketServer& server; ///< Reference to the server. Will be used to remove this publisher when the connection is dropped.
        
        /**
         * @brief listen to the socket and emit all of the values to the clients.
        */
        void worker();
        /**
         * @brief Catch any exception thrown by Publisher::worker, and close the publisher if the error is fatal.
        */
        void workerWrapper();
    };
} // namespace PubSub

#endif