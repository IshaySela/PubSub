#include "headers/TlsSocketServer.hpp"
#include "headers/Config.hpp"
#include <cstdlib>
#include <iostream>

using PubSub::TlsSocketServer;
using PubSub::Config;

int main()
{
    Config::useEnvironmentVariables();
    
    TlsSocketServer server(Config::getPort());
    server.acceptClients();
}