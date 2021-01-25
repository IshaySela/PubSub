#include "headers/TlsSocketServer.hpp"

using PubSub::TlsSocketServer;

int main()
{
    TlsSocketServer server(8080);
    server.acceptClients();
}