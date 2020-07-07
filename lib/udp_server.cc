#include "unp.h"

namespace unp
{
    int udp_server(const char *host, const char *serv, socklen_t *addrlenp)
    {
        int sockfd;
        int n;
        struct addrinfo hints;
        struct addrinfo *res;
        struct addrinfo *ressave;

        bzero(&hints, sizeof(struct addrinfo));
        hints.ai_flags = AI_PASSIVE;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;

        if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
        {
            err_quit("udp_server error for %s, %s: %s", host, serv, gai_strerror(n));
            return n;
        }
        ressave = res;
        do
        {
            sockfd = Socket(res->ai_family, res->ai_socktype, res->ai_protocol);
            if (sockfd < 0)
            {
                continue; /* error - try next one */
            }

            if ((n = Bind(sockfd, res->ai_addr, res->ai_addrlen)) == 0)
            {
                break; /* success */
            }
            Close(sockfd); /* bind error - close and try next one */
        } while ((res = res->ai_next) != NULL);

        if (res == NULL) /* errno from final socket() or bind() */
        {
            err_msg("udp_server error for %s, %s", host, serv);
            return n;
        }

        if (addrlenp)
        {
            *addrlenp = res->ai_addrlen; /* return size of protocol address */
        }

        freeaddrinfo(ressave);

        return (sockfd);
    }
    /* end udp_server */

    int Udp_server(const char *host, const char *serv, socklen_t *addrlenp)
    {
        return udp_server(host, serv, addrlenp);
    }
} // namespace unp