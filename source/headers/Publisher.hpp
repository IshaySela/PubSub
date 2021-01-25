#ifndef PUBLISHER
#define PUBLISHER
#include <string>
#include <unordered_map>
#include <future>

#include "Util/BioTypes.hpp"
#include "Subscriber.hpp"

using PubSub::Util::ClientBIO;

namespace PubSub
{
    using SubscribersMap = std::unordered_map<std::string, std::unique_ptr<Subscriber>>;

    class Publisher
    {
    public:
        Publisher(std::string id, ClientBIO socket);
        ~Publisher();

        void setClient(ClientBIO client);

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
         * @brief listen to the socket and emit all of the values to the clients.
        */
        void worker();
    };
} // namespace PubSub

#endif