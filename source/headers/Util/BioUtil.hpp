#ifndef BIO_UTIL
#define BIO_UTIL

#include <string>
#include <openssl/ssl.h>
#include <vector>
#include "../UniquePtrWrapper.hpp"
#include "../OpenSslErrors.hpp"

namespace PubSub
{
    namespace Util
    {
        class BioUtil
        {
        public:
            static std::string readSomeData(UniquePtr<BIO> &bio);

            template <std::size_t amount>
            static std::string readBytes(UniquePtr<BIO> &bio);

            template <std::size_t amount> 
            static std::vector<char> readBytesVector(UniquePtr<BIO>& bio);
            
            static std::vector<char> readBytes(UniquePtr<BIO>& bio, int amount);

            static std::string readHeaders(UniquePtr<BIO> &bio);
            static std::string readHeaders(UniquePtr<BIO> &bio, std::string &);

            /**
             * @brief Check if a bio of type socket accepts data.
            */
            static bool socketConnected(BIO* bio);
            static bool socketConnected(UniquePtr<BIO>& bio);
        };

        template <std::size_t size>
        std::string BioUtil::readBytes(UniquePtr<BIO> &bio)
        {
            char buffer[size];
            int len = BIO_read(bio.get(), buffer, sizeof(buffer));

            if (len < 0)
                printErrorsAndThrow("BioUtil::readSomeData\nError reading data from bio");
            else if (len > 0)
                return std::string(buffer, len);
            else if (BIO_should_retry(bio.get()))
                return BioUtil::readBytes<size>(bio);
            else
                printErrorsAndThrow("BioUtil::readSomeData\nUnknown error while reading from bio.");

        }

        template <std::size_t size>
        std::vector<char> BioUtil::readBytesVector(UniquePtr<BIO>& bio)
        {
            std::vector<char> buffer = std::vector<char>(size);

            int len = BIO_read(bio.get(), &buffer[0], size);

            if (len < 0)
                printErrorsAndThrow("BioUtil::readSomeData\nError reading data from bio");
            else if (len > 0)
            {
                buffer.resize(len);
                return buffer;
            }
            else if (BIO_should_retry(bio.get()))
                return BioUtil::readBytesVector<size>(bio);
            else
                printErrorsAndThrow("BioUtil::readSomeData\nUnknown error while reading from bio.");
        }
    } // namespace Util
} // namespace PubSub

#endif