#include "headers/Publisher.hpp"
#include "headers/Util/BioUtil.hpp"
#include "headers/Util/Random.hpp"
#include "headers/Protocol/PublishDataRequest.hpp"
#include "headers/Protocol/PublishDataResponse.hpp"
#include "headers/OpenSslErrors.hpp"
#include <sys/socket.h>
#include <iostream>
#include <sstream>

using PubSub::Util::BioUtil;

namespace PubSub
{
    Publisher::Publisher(std::string id, ClientBIO socket, TlsSocketServer &server) : id(id), client(std::move(socket)), server(server)
    {
        this->workerDone = false;
    }

    Publisher::~Publisher() {}

    void Publisher::addNew(std::unique_ptr<Subscriber> sub, std::string id)
    {
        this->subscribers[id] = std::move(sub);
    }

    void Publisher::start()
    {
        this->workerFtr = std::async(&Publisher::workerWrapper, this).share();
    }

    std::string Publisher::getId() const { return this->id; }
    bool Publisher::isWorkerDone() const { return this->workerDone.load(); }

    void Publisher::workerWrapper()
    {
        try
        {
            this->worker();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            //close(BIO_get_fd(this->client.get(), nullptr));
            this->server.removePublisher(this->id);
        }
    }
    void Publisher::worker()
    {
        while (true)
        {
            std::string payload;
            auto headers = BioUtil::readHeaders(this->client, payload);

            auto request = Protocol::PublishDataRequest(headers);
            int length = request.getPayloadLength() - payload.length();
            if (length > 0)
            {
                payload += BioUtil::readBytes(this->client, length).data();
            }

            for (auto &sub : this->subscribers)
            {
                auto sock = sub.second->getSocket();
                auto sent = BIO_write(sock, payload.data(), payload.size());

                // The client is dead, remove it from the clients list.
                if (!BioUtil::socketConnected(sock))
                    this->subscribers.erase(sub.first);
            }

            auto response = Protocol::PublishDataResponse(Protocol::ResponseStatus::Success).toJson().dump();

            BIO_write(this->client.get(), response.c_str(), response.length());
        }

        //auto payload = BioUtil::readBytes(this->client, request.getPayloadLength());
    }

    void Publisher::setClient(ClientBIO client)
    {
        this->client = std::move(client);
    }
} // namespace PubSub
