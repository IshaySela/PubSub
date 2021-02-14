#ifndef CONFIG
#define CONFIG

#define ENV_NAME_PORT "PORT"
#define DEFAULT_VALUE_PORT 8080
#define ENV_NAME_PUBLISHER_CLEANER_TIMEOUT "PUBLISHER_CLEAENER_TIMEOUT"
#define DEFAULT_VALUE_PUBLISHER_CLEANER_TIMEOUT 30

namespace PubSub
{
    
    class Config
    {
    public:
        Config() = delete;
        Config(Config& other) = delete;

        /**
         * @brief Load configuration from the environment variables.
         * 
         * @paragraph enviroment-list Enviroment List
         * @li @c PORT The port of the application.
         * @li @c PUBLISHER_CLEAENER_TIMEOUT The timeout between every TlsSocketServer::publishersCleaner call.
        */
        static void useEnvironmentVariables();
        
        /**
         * @brief Get the port for the application.
        */
        static int getPort();
        
        /**
         * @brief The timeout between every TlsSocketServer::publishersCleaner call.
        */
        static int getDeadPublishersTimeout();

        ~Config();
    private:
        static int port;
        static int deadPublishersTimeout;
    };
        
}

#endif