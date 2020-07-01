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

    Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

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
                err_sys("accept error");
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
