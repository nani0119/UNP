#include "unp.h"

namespace unp
{
    int tcp_connect(const char *host, const char *serv)
    {
        int sockfd;
        int n;
        struct addrinfo hints;
        struct addrinfo *result;
        struct addrinfo *resultsave;

        bzero(&hints, sizeof(struct addrinfo));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        if((n = getaddrinfo(host, serv, &hints, &result)) != 0)
        {
            err_msg("tcp_connect error for %s, %s: %s", host, serv, gai_strerror(n));
            return n;
        }

        resultsave = result;

        for(;result != NULL; result = result->ai_next)
        {
            sockfd = Socket(result->ai_family, result->ai_socktype, result->ai_protocol);
            if(sockfd < 0)
            {
                continue;
            }

            if((n = Connect(sockfd, result->ai_addr, result->ai_addrlen)) == 0)
            {
                break; // success
            }

            Close(sockfd);
        }

        if(result == NULL)
        {
            err_msg("tcp_connect error for %s, %s", host, serv);
            return n;
        }
        freeaddrinfo(resultsave);

        return sockfd;
    }

    int Tcp_connect(const char *host, const char *serv)
    {
        return tcp_connect(host, serv);
    }
}