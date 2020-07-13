#include "unp.h"

using namespace std;
using namespace unp;

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_un servaddr;
    struct sockaddr_un cliaddr;

    sockfd = Socket(AF_LOCAL, SOCK_DGRAM, 0);
    unlink(UNIXDG_PATH);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXDG_PATH);

    Bind(sockfd, (SA*)&servaddr, sizeof(servaddr));

    dg_echo(sockfd, (SA*)&cliaddr, sizeof(cliaddr)); 
    return 0;
}
