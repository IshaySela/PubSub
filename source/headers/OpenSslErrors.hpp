#ifndef OPEN_SSL_ERRORS
#define OPEN_SSL_ERRORS
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <exception>
#include "StringBIO.hpp"

namespace PubSub
{
    [[noreturn]] void printErrorsAndExit(const char *message);

    [[noreturn]] void printErrorsAndThrow(const char *message);
} // namespace PubSub

#endif