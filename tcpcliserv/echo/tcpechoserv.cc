#include <iostream>
#include "unp.h"

using namespace std;
using namespace unp;

// 防止僵尸进程
void sig_chld(int signo)
{
    pid_t pid;
    int stat;
    // 等候所有进程，no hang
    while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        printf("child %d terninated\n", pid);
    }
    return;
}

int main(int argc, char const *argv[])
{
    int listenfd;
    int connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr;
    struct sockaddr_in servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    if(Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        err_quit("exit");
    }

    socklen_t servaddrlen = sizeof(servaddr);

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

    if(Listen(listenfd, LISTENQ) < 0)
    {
        err_quit("exit");
    }

    Signal(SIGCHLD, sig_chld);

    while(1)
    {
        clilen = sizeof(cliaddr);
        connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
        // 检测等候过程中被中断的情况
        if(connfd < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                err_quit("exit");
            }
        }
        else
        {
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
        }
        if((childpid = Fork()) == 0)
        {

            Close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        Close(connfd);
    }

    return 0;
}
