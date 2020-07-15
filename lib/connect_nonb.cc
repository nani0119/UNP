#include "unp.h"

namespace unp
{
    int connect_nonb(int sockfd, const struct sockaddr* saptr, socklen_t salen, int nsec)
    {
        int flags;
        int n;
        int error;
        socklen_t len;
        fd_set rset;
        fd_set wset;

        struct timeval tval;

        flags = Fcntl(sockfd, F_GETFL, 0);

        Fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

        error = 0;
        if((n = connect(sockfd, saptr, salen)) < 0)
        {
            if(errno != EINPROGRESS)
            {
                return -1;
            }
        }

        /* Do whatever we want while the connect is taking place. */
        if(n == 0)
        {
            goto done;
        }

        FD_ZERO(&rset);
        FD_SET(sockfd, &rset);
        wset = rset;
        tval.tv_usec = nsec;
        tval.tv_usec = 0;
        if((n = Select(sockfd+1, &rset, &wset, NULL, nsec? &tval:NULL)) == 0)
        {
            // time out
            Close(sockfd);
            errno = ETIMEDOUT;
            return -1;
        }

        if(FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset))
        {
            len = sizeof(error);
            if(Getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
            {
                return -1;
            }
            else
            {
                err_msg("select error: sockfd not set");
                return -1;
            }
        }

    done:
        Fcntl(sockfd, F_SETFL, flags);
        if(error)
        {
            Close(sockfd);
            errno = error;
            return -1;
        }
        return 0;
    }
}