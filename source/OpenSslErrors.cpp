#include "headers/OpenSslErrors.hpp"

namespace PubSub
{
    void printErrorsAndThrow(const char* msg)
    {
        StringBIO bio;
        ERR_print_errors(bio.bio());
        throw std::runtime_error(std::string(msg) + "\n" + std::move(bio).str());
    }

    void printErrorsAndExit(const char* message)
    {
        fprintf(stderr, "%s\n", message);
        ERR_print_errors_fp(stderr);
        exit(1);
    }
}