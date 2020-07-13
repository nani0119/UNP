#include "unp.h"
using namespace std;
using namespace unp;

// 防止僵尸进程
void sig_chld(int signo)
{
    pid_t pid;
    int stat;
    // 等候所有进程，no hang
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
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
    struct sockaddr_un cliaddr;
    struct sockaddr_un servaddr;

    listenfd = Socket(AF_LOCAL, SOCK_STREAM, 0);

    unlink(UNIXSTR_PATH);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXSTR_PATH);

    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    Signal(SIGCHLD, sig_chld);

    while (1)
    {
        clilen = sizeof(cliaddr);
        if ((connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) < 0)
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
        if ((childpid = Fork()) == 0)
        {
            Close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        Close(connfd);
    }

    return 0;
}
