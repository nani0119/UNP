#include <iostream>
#include "unp.h"

using namespace std;
using namespace unp;

int main(int argc, char const *argv[])
{
    int listenfd;
    int connfd;
    int sockfd;
    int i, maxi, maxfd;

    fd_set rset, allset;

    int nready;
    int client[FD_SETSIZE];
    ssize_t n;
    char buf[MAXLINE];

    struct sockaddr_in cliaddr;
    socklen_t clilen;
    struct sockaddr_in servaddr;
    socklen_t servaddrlen;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    Listen(listenfd,LISTENQ);

    // 显示连接信息
    if(getsockname(listenfd, (struct sockaddr*)&servaddr, &servaddrlen) < 0)
    {
        err_sys("getsockname error");
    }
    else
    {
        printf("server family      :%s\n", servaddr.sin_family == AF_INET? "AF_INET":"AF_INET6");
        char addr[INET6_ADDRSTRLEN] = {0};
        printf("server bind address:%s\n", inet_ntop(servaddr.sin_family, &servaddr, addr, INET6_ADDRSTRLEN));
        printf("server bind port   :%d\n", servaddr.sin_port);
        printf("----------------------------------------------\n");
    }

    maxfd = listenfd;
    maxi = -1;

    for(int i = 0; i < FD_SETSIZE; i++)
    {
        client[i] = -1;
    }

    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    while(1)
    {
        rset = allset;
        nready = Select(maxfd+1, &rset, NULL, NULL, NULL);
        if(FD_ISSET(listenfd, &rset))
        {
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
            // 显示连接信息
            if(getpeername(connfd, (struct sockaddr*)&cliaddr, &clilen) < 0)
            {
                err_msg("getperrname error");
            }
            else
            {
                printf("client family :%s\n", cliaddr.sin_family == AF_INET? "AF_INET":"AF_INET6");
                char addr[INET6_ADDRSTRLEN] = {0};
                printf("client address:%s\n", inet_ntop(cliaddr.sin_family, &cliaddr, addr, INET6_ADDRSTRLEN));
                printf("client port   :%d\n", cliaddr.sin_port);
                printf("----------------------------------------------\n");
            }

            for(i = 0; i < FD_SETSIZE; i++)
            {
                if(client[i] < 0)
                {
                    client[i] = connfd;
                    break;
                }
            }
            if(i == FD_SETSIZE)
            {
                err_quit("too many clients");
            }

            FD_SET(connfd, &allset);
            if(connfd > maxfd)
            {
                maxfd = connfd;
            }
            if(i > maxi)
            {
                maxi = i;
            }

            if(--nready <= 0)
            {
                continue;
            }
        }

        for(i = 0; i <= maxi; i++)
        {
            if((sockfd = client[i]) < 0)
            {
                continue;
            }

            if(FD_ISSET(sockfd, &rset))
            {
                if((n = Read(sockfd, buf, MAXLINE)) == 0)
                {
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }
                else
                {
                    //printf("%s\n", buf);
                    Writen(sockfd, buf, n);
                }

                if(--nready <= 0)
                {
                    break;
                }
            }
        }
    }

}