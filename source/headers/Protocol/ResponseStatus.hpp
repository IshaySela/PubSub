#ifndef RESOPNSE_STATUS
#define RESPONSE_STATUS

namespace PubSub
{
    namespace Protocol
    {
        enum ResponseStatus
        {
            Success = 0,
            Error = 100
        };

        using ResponseStatus = enum ResponseStatus;
    }
}

#endif