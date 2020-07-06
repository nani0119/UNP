#include "unp.h"

namespace unp
{
    void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
    {
        int n;
        socklen_t len;
        char sendline[MAXLINE], recvline[MAXLINE + 1];
        struct sockaddr* preply_addr;
        preply_addr =(struct sockaddr*) malloc(servlen);

        while (Fgets(sendline, MAXLINE, fp) != NULL)
        {

            Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
            len = servlen;
            n = Recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);
            if(len != servlen || memcmp(pservaddr, preply_addr, len) != 0)
            {
                printf("replay from %s (ignored)\n", Sock_ntop(preply_addr, len));
                continue;
            }
            recvline[n] = 0; /* null terminate */
            Fputs(recvline, stdout);
        }
        // can not reach
        free(preply_addr);
    }
}