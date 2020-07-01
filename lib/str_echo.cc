#include "unp.h"

namespace unp
{
    void str_echo(int sockfd)
    {
        ssize_t n;
        char buf[MAXLINE] = {0};
    again:
        while((n = read(sockfd, buf, MAXLINE)) > 0)
        {
            Writen(sockfd, buf, n);
        }
        if (n < 0 && errno == EINTR)
        {
            goto again;
        }
        else if(n < 0)
        {
            err_msg("str_echo: read error");
        }
    }
}