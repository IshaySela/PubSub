#ifndef SUBSRIBER
#define SUBSRIBER
#include "Util/BioTypes.hpp"

using PubSub::Util::ClientBIO;

namespace PubSub
{
    class Subscriber
    {
    public:
        Subscriber(ClientBIO socket);
        ~Subscriber();

        BIO* getSocket() const;
    private:
        ClientBIO socket;
    };
} // namespace PubSub

#endif