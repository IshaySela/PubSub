#ifndef BIO_TYPES
#define BIO_TYPES
#include <openssl/ssl.h>
#include "../UniquePtrWrapper.hpp"


namespace PubSub
{
    namespace Util
    {
        // Define here all of the diffrent names for diffrent BIOs.
        using ClientsFactoryBIO = UniquePtr<BIO>;
        using ClientBIO = UniquePtr<BIO>;
    }
}
#endif