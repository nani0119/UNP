#include <iostream>

#include "unp.h"

using namespace std;
using namespace unp;

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr;
    struct sockaddr_in localaddr;
    socklen_t sockaddrlen = sizeof(localaddr);
    if(argc != 2)
    {
        err_quit("usage: tcpcli_echo_exe <ip address>");
    }

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);

    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    if(Connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        err_quit("exit");
    }

    // 显示连接信息
    if(getsockname(sockfd, (struct sockaddr*)&localaddr, &sockaddrlen) < 0)
    {
        err_sys("getsockname error");
    }
    else
    {
        printf("loacal family:%s\n", localaddr.sin_family == AF_INET? "AF_INET":"AF_INET6");
        char addr[INET6_ADDRSTRLEN] = {0};
        printf("local address:%s\n", inet_ntop(localaddr.sin_family, &localaddr, addr, INET6_ADDRSTRLEN));
        printf("local port   :%d\n", localaddr.sin_port);
        printf("----------------------------------------------\n");
    }

    {
        printf("server family:%s\n", servaddr.sin_family == AF_INET? "AF_INET":"AF_INET6");
        char addr[INET6_ADDRSTRLEN] = {0};
        printf("server address:%s\n", inet_ntop(servaddr.sin_family, &servaddr, addr, INET6_ADDRSTRLEN));
        printf("server port   :%d\n", servaddr.sin_port);
        printf("----------------------------------------------\n");
    }


    str_cli(stdin, sockfd);

    return 0;
}
