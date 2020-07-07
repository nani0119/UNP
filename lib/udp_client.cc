#include "unp.h"

namespace unp
{
    int udp_client(const char *host, const char *serv, struct sockaddr **saptr, socklen_t *lenp)
    {
        int sockfd;
        int n;

        struct addrinfo hints;
        struct addrinfo* res;
        struct addrinfo* ressave;

        bzero(&hints, sizeof(struct addrinfo));
	    hints.ai_family = AF_UNSPEC;
	    hints.ai_socktype = SOCK_DGRAM;

        if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
        {
		    err_msg("udp_client error for %s, %s: %s", host, serv, gai_strerror(n));
            return n;
        }
	    ressave = res;

        
	    do {
		    sockfd = Socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		    if (sockfd >= 0)
            {
			    break;		/* success */
            }
	    } while ( (res = res->ai_next) != NULL);

        if (res == NULL)	/* errno set from final socket() */
        {
		    err_msg("udp_client error for %s, %s", host, serv);
            return -1;
        }

        *saptr = (struct sockaddr*)malloc(res->ai_addrlen);
        memcpy(*saptr, res->ai_addr, res->ai_addrlen);
	    *lenp = res->ai_addrlen;
        freeaddrinfo(ressave);

	    return sockfd;
    }

    int Udp_client(const char *host, const char *serv, SA **saptr, socklen_t *lenptr)
    {
	    return udp_client(host, serv, saptr, lenptr);
    }
}