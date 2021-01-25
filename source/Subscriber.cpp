#include "headers/Subscriber.hpp"

namespace PubSub
{
    Subscriber::Subscriber(ClientBIO socket) : socket(std::move(socket)) {}
    Subscriber::~Subscriber() {}

    BIO* Subscriber::getSocket() const { return this->socket.get(); }
}