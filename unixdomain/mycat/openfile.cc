#include "unp.h"

using namespace std;
using namespace unp;

int main(int argc, char const *argv[])
{
    int fd;
    if(argc != 4)
    {
        err_quit("openfile <sockfd#> <filename> <mode>");
    }

    if((fd = open(argv[2], atoi(argv[3]))) < 0)
    {
        exit( (errno > 0) ? errno : 255 );
    }

    char c =' ';
    if(Write_fd(atoi(argv[1]), &c , 1, fd) < 0)
    {
        exit( (errno > 0) ? errno : 255 );
    }
    return 0;
}
