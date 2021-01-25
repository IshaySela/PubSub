#include "headers/Util/BioUtil.hpp"


#include <iostream>

namespace PubSub
{
    namespace Util
    {
        std::vector<char> BioUtil::readBytes(UniquePtr<BIO>& bio, int size)
        {
            std::vector<char> buffer;
            buffer.resize(size);

            int len = BIO_read(bio.get(), &buffer[0], size);

            if (len < 0)
                printErrorsAndThrow("BioUtil::readSomeData\nError reading data from bio");
            else if (len > 0)
            {
                buffer.resize(len);
                return buffer;
            }
            else if (BIO_should_retry(bio.get()))
                return BioUtil::readBytes(bio, size);
            else
                printErrorsAndThrow("BioUtil::readSomeData\nUnknown error while reading from bio.");

            return buffer;
        }
        
        std::string BioUtil::readSomeData(UniquePtr<BIO> &bio)
        {
            return BioUtil::readBytes<1024>(bio).data();
        }


        std::string BioUtil::readHeaders(UniquePtr<BIO> &bio, std::string& leftover)
        {
            std::string headers = "";
            size_t lastIndex = std::string::npos;
            leftover = "";
            
            do
            {
                if (headers.length() > 1024 * 4)
                    throw std::runtime_error("Max headers length execeeded.");

                headers += Util::BioUtil::readSomeData(bio);
                lastIndex = headers.find("\r\n\r\n"); // Search for the delimiter in the buffer recived.
            } while (lastIndex == std::string::npos);


            leftover = headers.substr(lastIndex + 4);
            headers.erase(lastIndex);
            
            return headers;
        }

        std::string BioUtil::readHeaders(UniquePtr<BIO>& bio)
        {
            std::string body;
            return BioUtil::readHeaders(bio, body);
        }

    } // namespace Util

} // namespace PubSub
