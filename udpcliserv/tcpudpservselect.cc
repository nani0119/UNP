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
    int listenfd,connfd;
    int udpfd;
    int nready;

    char mesg[MAXLINE];

    pid_t childpid;

    int maxfdp1;
    fd_set rset;

    ssize_t n;
    socklen_t len;
    const int on = 1;

    struct sockaddr_in cliaddr, servaddr;

    // TCP
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    // UDP
    udpfd = Socket(AF_INET, SOCK_DGRAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    Bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    Signal(SIGCHLD, sig_chld);


    // select
    FD_ZERO(&rset);
    maxfdp1 = max(listenfd, udpfd) + 1;
    
    while(1)
    {
        FD_SET(listenfd, &rset);
        FD_SET(udpfd, &rset);

        if((nready = Select(maxfdp1, &rset, NULL,NULL, NULL)) < 0)
        {
            if(errno == EINTR)
            {
                continue;
            
           }

            else
            {
                err_sys("select error");
            
           }

        
       }

       if (FD_ISSET(listenfd, &rset))
       {
           len = sizeof(cliaddr);
           connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &len);
           if ((childpid = Fork()) == 0)
           {
               Close(listenfd);
               str_echo(connfd);
               exit(0);
           }
           else
           {
               Close(connfd);
           }
       }

       if (FD_ISSET(udpfd, &rset))
       {
           dg_echo(udpfd, (SA*)&cliaddr, sizeof(cliaddr));
       }
    }
    return 0;
}
