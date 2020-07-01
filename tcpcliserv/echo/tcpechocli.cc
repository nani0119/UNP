#include <iostream>

#include "unp.h"

using namespace std;
using namespace unp;

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr;
    if(argc != 2)
    {
        err_quit("usage: tcpcli_echo_exe <ip address>");
    }

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);

    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd);

    return 0;
}
