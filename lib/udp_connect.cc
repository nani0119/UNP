#include "unp.h"

namespace unp
{
    int udp_connect(const char *host, const char *serv)
    {
        int sockfd;
        int n;
        struct addrinfo hints;
        struct addrinfo *res;
        struct addrinfo *ressave;

        bzero(&hints, sizeof(struct addrinfo));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;

        if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
        {
            err_msg("udp_connect error for %s, %s: %s", host, serv, gai_strerror(n));
            return n;
        }
        ressave = res;

        do
        {
            sockfd = Socket(res->ai_family, res->ai_socktype, res->ai_protocol);
            if (sockfd < 0)
            {
                continue; /* ignore this one */
            }

            if ((n = Connect(sockfd, res->ai_addr, res->ai_addrlen)) == 0)
            {
                break; /* success */
            }
            Close(sockfd); /* ignore this one */
        } while ((res = res->ai_next) != NULL);

        if (res == NULL) /* errno set from final connect() */
        {
            err_msg("udp_connect error for %s, %s", host, serv);
            return n;
        }

        freeaddrinfo(ressave);

        return sockfd;
    }
    /* end udp_connect */

    int Udp_connect(const char *host, const char *serv)
    {
        int n;

        if ((n = udp_connect(host, serv)) < 0)
        {
            err_msg("udp_connect error for %s, %s", host, serv);
        }
        return n;
    }
} // namespace unp