#include "headers/Publisher.hpp"
#include "headers/Util/BioUtil.hpp"
#include "headers/Util/Random.hpp"
#include "headers/Protocol/PublishDataRequest.hpp"
#include "headers/Protocol/PublishDataResponse.hpp"
#include <iostream>
#include <string>

using PubSub::Util::BioUtil;

namespace PubSub
{
    Publisher::Publisher(std::string id, ClientBIO socket) : id(id), client(std::move(socket))
    {
    }

    Publisher::~Publisher() {}

    void Publisher::addNew(std::unique_ptr<Subscriber> sub, std::string id)
    {
        this->subscribers[id] = std::move(sub);
    }

    void Publisher::start()
    {
        this->workerFtr = std::async(&Publisher::worker, this).share();
    }

    void Publisher::worker()
    {

        try
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

                for (auto& sub : this->subscribers)
                {
                    auto sock = sub.second->getSocket();
                    BIO_write(sock, payload.data(), payload.size());
                }

                auto response = Protocol::PublishDataResponse(Protocol::ResponseStatus::Success).toJson().dump();

                BIO_write(this->client.get(), response.c_str(), response.length());
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            close(BIO_get_fd(this->client.get(), nullptr));
        }
        
        //auto payload = BioUtil::readBytes(this->client, request.getPayloadLength());
    }

    void Publisher::setClient(ClientBIO client)
    {
        this->client = std::move(client);
    }
} // namespace PubSub
