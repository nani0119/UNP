#include "unp.h"

using namespace std;
using namespace unp;

int my_open(const char* pathname, int mode)
{
    int fd;
    int sockfd[2];
    int status;

    pid_t childpid;
    char c;
    char argsockfd[10];
    char argmode[10];

    Socketpair(AF_LOCAL, SOCK_STREAM, 0, sockfd);

    if((childpid = Fork()) == 0)
    {
        Close(sockfd[0]);
        snprintf(argsockfd, sizeof(argsockfd), "%d", sockfd[1]);
        snprintf(argmode, sizeof(argmode), "%d", mode);
        // execl后无法访问sockfd变量，但是文件描述符是打开的
        execl("./openfile", "openfile", argsockfd, pathname, argmode, (char*)NULL);
        err_sys("execl error");
    }

    Close(sockfd[1]);

    Waitpid(childpid, &status, 0);
    if(WIFEXITED(status) == 0)
    {
        err_quit("child did not terminate");
    }

    if((status = WEXITSTATUS(status)) == 0)
    {
        Read_fd(sockfd[0], &c, 1, &fd);
    }
    else
    {
        errno = status;
        fd = -1;
    }

    Close(sockfd[0]);
    return fd;
}

int main(int argc, char const *argv[])
{
    int fd;
    int n;
    char buff[BUFFSIZE] = {0};
    if(argc != 2)
    {
        err_quit("usage mycat_exe <path name>");
    }

    if((fd = my_open(argv[1], O_RDONLY)) < 0)
    {
        err_sys("can not open %s", argv[1]);
    }
    while((n = Read(fd, buff, BUFFSIZE)) > 0)
    {
        Write(STDOUT_FILENO, buff, n);
    }
    return 0;
}
