#include "unp.h"

namespace unp
{
    int sockfd_to_family(int sockfd)
    {
        struct sockaddr_storage ss;
        socklen_t len;

        len = sizeof(ss);
        if(getsockname(sockfd, (struct sockaddr*)&ss, &len) < 0)
        {
            err_msg("getsockname error");
            return -1;
        }
        return ss.ss_family;
    }
}