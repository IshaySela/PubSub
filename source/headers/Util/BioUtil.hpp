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
            /**
             * @brief read 1024 bytes of data and return them.
             * @param bio Reference to the bio.
             * @returns The first 1024 bytes of the data that were read by the bio.
            */
            static std::string readSomeData(UniquePtr<BIO> &bio);

            /**
             * @brief Read X amount of bytes from the bio and return them as string.
             * @param bio Reference to bio. 
             * @tparam amount The amount to read from the bio.
             * @returns The bytes read as string.
            */
            template <std::size_t amount>
            static std::string readBytes(UniquePtr<BIO> &bio);

            /**
             * @brief Read X amount of bytes from the bio and return them as string.
             * @param bio Reference to bio. 
             * @tparam amount The amount to read from the bio.
             * @returns The bytes read as vector of chars.
            */
            template <std::size_t amount> 
            static std::vector<char> readBytesVector(UniquePtr<BIO>& bio);
            
            /**
             * @brief Read X amount of bytes from the bio and return them as string.
             * @param bio Reference to bio. 
             * @param amount The amount to read from the bio.
             * @returns The bytes read as vector of chars.
            */
            static std::vector<char> readBytes(UniquePtr<BIO>& bio, int amount);

            /**
             * @brief Read all bytes until encountering \r\n\r\n, and return the data without the \r\n\r\n. 
             * @param bio The bio to read from.
             * @param leftover all of the data thata was read after \r\n\r\n.s
            */
            static std::string readHeaders(UniquePtr<BIO> &bio, std::string& leftover);
            static std::string readHeaders(UniquePtr<BIO> &bio);
            
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