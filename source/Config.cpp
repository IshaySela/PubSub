#include "headers/Config.hpp"
#include <cstdlib>

int PubSub::Config::port = DEFAULT_VALUE_PORT;
int PubSub::Config::deadPublishersTimeout = DEFAULT_VALUE_PUBLISHER_CLEANER_TIMEOUT;

namespace PubSub
{

    void Config::useEnvironmentVariables() 
    {
        const char* portString = std::getenv(ENV_NAME_PORT);

        Config::port = portString == nullptr ? Config::port : std::atoi(portString);

        const char* cleanrPublishersTimeout = std::getenv(ENV_NAME_PUBLISHER_CLEANER_TIMEOUT);
        Config::deadPublishersTimeout = cleanrPublishersTimeout == nullptr ? Config::deadPublishersTimeout : std::atoi(cleanrPublishersTimeout);

    }

    int Config::getPort() 
    {
        return Config::port;
    }

    int Config::getDeadPublishersTimeout()
    {
        return Config::deadPublishersTimeout;
    }
}