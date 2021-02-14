#include "headers/Config.hpp"
#include <cstdlib>

int PubSub::Config::port = DEFAULT_VALUE_PORT;

namespace PubSub
{

    void Config::useEnvironmentVariables() 
    {
        const char* portString = std::getenv(ENV_NAME_PORT);

        Config::port = portString == nullptr ? Config::port : std::atoi(portString);

    }

    int Config::getPort() 
    {
        return Config::port;
    }
}