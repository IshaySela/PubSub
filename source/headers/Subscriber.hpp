#ifndef SUBSRIBER
#define SUBSRIBER
#include "Util/BioTypes.hpp"

using PubSub::Util::ClientBIO;

namespace PubSub
{
    /**
     * @brief Contains the BIO of a subscriber and other metadata about the subscriber.
    */
    class Subscriber
    {
    public:
        Subscriber(ClientBIO socket);
        ~Subscriber();

        BIO* getSocket() const;
    private:
        ClientBIO socket; ///< The BIO of the client.
    };
} // namespace PubSub

#endif