#ifndef UNIQUE_PTR_WRAPPER
#define UNIQUE_PTR_WRAPPER

#include <openssl/ssl.h>
#include <memory>

/**
* @file Create wrappers for openssl objects using unique_ptr.
*/

namespace PubSub
{
    template <class T>
    struct DeleterOf;
    template <>
    struct DeleterOf<SSL_CTX>
    {
        void operator()(SSL_CTX *p) const { SSL_CTX_free(p); }
    };
    template <>
    struct DeleterOf<SSL>
    {
        void operator()(SSL *p) const { SSL_free(p); }
    };
    template <>
    struct DeleterOf<BIO>
    {
        void operator()(BIO *p) const { BIO_free_all(p); }
    };
    template <>
    struct DeleterOf<BIO_METHOD>
    {
        void operator()(BIO_METHOD *p) const { BIO_meth_free(p); }
    };

    template <class OpenSSLType>
    using UniquePtr = std::unique_ptr<OpenSSLType, DeleterOf<OpenSSLType>>;

    
} // namespace PubSub

#endif