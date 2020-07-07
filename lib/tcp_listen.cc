#include "unp.h"

namespace unp
{
    int tcp_listen(const char* host, const char* serv, socklen_t* addrlenp)
    {
        int listenfd;
        int n;
        const int on = 1;
        struct addrinfo hints;
        struct addrinfo* res;
        struct addrinfo* ressave;

        bzero(&hints, sizeof(struct addrinfo));
        hints.ai_flags = AI_PASSIVE;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        if((n = getaddrinfo(host, serv, &hints, &res)) != 0)
        {
            err_msg("tcp_listen error for %s, %s: %s",host, serv, gai_strerror(n));
            return n;
        }

        ressave = res;

        for(;res != NULL; res= res->ai_next)
        {
            listenfd = Socket(res->ai_family, res->ai_socktype, res->ai_protocol);
            if(listenfd < 0)
            {
                continue;
            }
            
            Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

            if((n = Bind(listenfd, res->ai_addr, res->ai_addrlen)) == 0)
            {
                break;
            }

            Close(listenfd);
        }

        if(res == NULL)
        {
            err_msg("tcp_listen error for %s, %s", host, serv);
            return n;
        }

        Listen(listenfd, LISTENQ);

        if(addrlenp)
        {
            *addrlenp = res->ai_addrlen;
        }

        freeaddrinfo(ressave);
        return listenfd;
    }

    int Tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
    {
        return tcp_listen(host, serv, addrlenp);
    }
}