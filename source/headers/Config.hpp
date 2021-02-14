#ifndef CONFIG
#define CONFIG

#define ENV_NAME_PORT "PORT"
#define DEFAULT_VALUE_PORT 8080

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
        */
        static void useEnvironmentVariables();
        
        /**
         * @brief Get the port for the application.
        */
        static int getPort();
        ~Config();
    private:
        static int port;
    };
        
}

#endif