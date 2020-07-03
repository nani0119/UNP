#include "unp.h"

namespace unp
{
    void str_cli(FILE *fp, int sockfd)
    {
    #if 0
        char sendline[MAXLINE], recvline[MAXLINE];

        while (Fgets(sendline, MAXLINE, fp) != NULL)
        {

            Writen(sockfd, sendline, strlen(sendline));

            if (Readline(sockfd, recvline, MAXLINE) == 0)
                err_quit("str_cli: server terminated prematurely");

            Fputs(recvline, stdout);
        }
    #else
        int maxfdp1;
        int stdineof = 0;;
        fd_set rset;
        char buf[MAXLINE];;
        int n;

        FD_ZERO(&rset);
        while(1)
        {
            if(stdineof == 0)
            {
                FD_SET(fileno(fp), &rset);
            }
            FD_SET(sockfd, &rset);
            maxfdp1 = max(fileno(fp), sockfd) + 1;
            Select(maxfdp1,&rset, NULL, NULL, NULL);

            if(FD_ISSET(sockfd, &rset)) /* socket is readable */
            {
                if((n = Read(sockfd, buf, MAXLINE)) == 0)
                {
                    
                    if(stdineof == 1)
                    {
                        //printf("return\n");
                        return;
                    }
                    else
                    {
                        err_quit("str_cli:server terninated prematurelu");
                    }

                }
                //printf("receive:%s\n", buf);
                Write(fileno(stdout), buf, n);
            }

            if(FD_ISSET(fileno(fp), &rset))
            {
                if((n = Read(fileno(fp), buf, MAXLINE)) == 0)
                {
                    stdineof = 1;
                    Shutdown(sockfd, SHUT_WR);  // send FIN
                    FD_CLR(fileno(fp), &rset);
                    continue;
                }
                //printf(" write to socket:%s\n", buf);
                Writen(sockfd, buf, n);
            }
        }
    #endif
    }

}