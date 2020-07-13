#include "unp.h"

using namespace std;
using namespace unp;

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_un servaddr;

    sockfd = Socket(AF_LOCAL, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXSTR_PATH);

    Connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    str_cli(stdin, sockfd);
    return 0;
}
