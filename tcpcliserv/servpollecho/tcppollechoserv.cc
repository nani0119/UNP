#include <iostream>
#include "unp.h"

using namespace std;
using namespace unp;
#define OPEN_MAX 1024
int main(int argc, char const *argv[])
{
    int i;
    int maxi;
    int listenfd, connfd, sockfd;
    int nready;
    ssize_t n;
    char buf[MAXLINE];
    struct pollfd client[OPEN_MAX];
    struct sockaddr_in cliaddr, servaddr;
    socklen_t clilen, servaddrlen;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

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

    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;

    for(i = 1; i < OPEN_MAX; i++)
    {
        client[i].fd = -1;
    }
    maxi = 0;

    while(1)
    {
        nready = Poll(client, maxi + 1, -1);
        if(client[0].revents & POLLRDNORM)
        {
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);

            for(i = 1; i < OPEN_MAX; ++i)
            {
                if(client[i].fd < 0)
                {
                    client[i].fd = connfd;
                    break;
                }
            }
            if(i == OPEN_MAX)
            {
                err_quit("too many clients");
            }

            client[i].events = POLLRDNORM;
            if(i > maxi)
            {
                maxi = i;
            }
            
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

            if(--nready <= 0)
            {
                continue;
            }
        }

        for(i = 1; i < OPEN_MAX; i++)
        {
            if((sockfd = client[i].fd) < 0)
            {
                continue;
            }

            if(client[i].revents & (POLLRDNORM|POLLERR))
            {
                if((n = read(sockfd, buf, MAXLINE)) < 0)
                {
                    if(errno == ECONNRESET)
                    {
                        Close(sockfd);
                        client[i].fd = -1;
                    }
                    else
                    {
                        err_sys("read error");
                    }
                }
                else if (n == 0)
                {
                    Close(sockfd);
                    client[i].fd = -1;
                }
                else
                {
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