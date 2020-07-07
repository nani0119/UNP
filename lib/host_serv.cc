#include "unp.h"

namespace unp
{
    struct addrinfo* Host_serv(const char* host, const char* serv, int family, int socktype)
    {
        int n;
        struct addrinfo hints;
        struct addrinfo* result;

        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_flags = AI_CANONNAME;  // always return canonical name
        hints.ai_family = family;
        hints.ai_socktype = socktype;

        if((n = getaddrinfo(host, serv, &hints, &result)) != 0)
        {
            return NULL;
        }
        return result;
    }
}