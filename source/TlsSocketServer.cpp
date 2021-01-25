#include "headers/TlsSocketServer.hpp"
#include "headers/Subscriber.hpp"
#include "headers/Util/Random.hpp"
#include "headers/Protocol/PublisherHandshakeResponse.hpp"
#include "headers/Util/BioUtil.hpp"
#include "headers/Protocol/SubscriberHandshakeResponse.hpp"
#include <openssl/ssl.h>
#include <iostream>
#include <sstream>
#include <csignal>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <vector>
#include <string>

namespace PubSub
{
    TlsSocketServer::TlsSocketServer(int port) : port(port)
    {
        auto socketStr = std::to_string(this->port);
        // Craete the socket factory
        this->clientsFactory = ClientsFactoryBIO(BIO_new_accept(socketStr.c_str()));

        static auto closeSocket = [fd = BIO_get_fd(this->clientsFactory.get(), nullptr)]() { close(fd); };
        std::signal(SIGINT, [](int) { closeSocket(); });

        std::cout << "Server running on port " << this->port << std::endl;
    }

    TlsSocketServer::~TlsSocketServer() {}

    void TlsSocketServer::acceptClients()
    {
        if (BIO_do_accept(this->clientsFactory.get()) <= 0)
            printErrorsAndThrow("An error occoured while executing BIO_do_accept.");

        while (auto client = this->acceptNewTcpConnection())
        {
            try
            {
                std::string headers;

                headers = Util::BioUtil::readHeaders(client);
                auto handshake = Protocol::Handshake::createAndThrow(headers);
                if (handshake.getClientType() == Protocol::ClientType::Publisher)
                    this->handlePublisher(client);

                else if (handshake.getClientType() == Protocol::ClientType::Subscriber)
                    this->handleSubscriber(client, handshake);
            }
            catch (const std::exception &e)
            {
                std::cerr << __FILE__ << ":" << __LINE__ << ":\t" << e.what() << std::endl;
                close(BIO_get_fd(client.get(), nullptr));
            }
        }
    }

    ClientBIO TlsSocketServer::acceptNewTcpConnection()
    {
        if (BIO_do_accept(this->clientsFactory.get()) <= 0)
            return nullptr;

        // BIO_do_accepts pushes the new client BIO into the BIO stack
        // of the clients factory.
        return ClientBIO(BIO_pop(this->clientsFactory.get()));
    }

    std::string TlsSocketServer::getHeaders(ClientBIO &socket)
    {
        std::string headers = "", last = "";

        do
        {

            if (headers.length() > MAX_HEADER_LENGTH)
                throw std::runtime_error("Max headers length execeeded.");

            headers = Util::BioUtil::readSomeData(socket);
            last = headers.substr(headers.size() - 4); // Get the last 4 characters. when done, those characters should be \r\n\r\n.
        } while (last != "\r\n\r\n");

        return headers;
    }

    void TlsSocketServer::handlePublisher(ClientBIO &client)
    {
        std::string publisherId = Util::randomString(32);

        auto response = Protocol::PublisherHandshakeResponse(publisherId, Protocol::ResponseStatus::Success).toJson().dump();
        BIO_write(client.get(), response.c_str(), response.length());
        BIO_write(client.get(), "\r\n\r\n", 4);

        std::unique_ptr<Publisher> publisher(new Publisher(publisherId, std::move(client)));

        publisher->start();

        this->publishers[publisherId] = std::move(publisher);
    }

    void TlsSocketServer::handleSubscriber(ClientBIO &socket, Protocol::Handshake &handshake)
    {
        auto endpointId = handshake.get<std::string>("Id");

        auto publisher = this->publishers.find(endpointId);

        if (publisher == this->publishers.end())
        {
            int fd = BIO_get_fd(socket.get(), nullptr);
            close(fd);
        }
        else
        {
            auto id = Util::randomString(16);
            auto json = Protocol::SubscriberHandshakeResponse(id).toJson().dump();
            BIO_write(socket.get(), json.c_str(), json.length());

            std::unique_ptr<Subscriber> sub(new Subscriber(std::move(socket)));
            publisher->second->addNew(std::move(sub), id);
        }
    }

} // namespace PubSub
