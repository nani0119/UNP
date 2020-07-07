#include "unp.h"

using namespace std;
using namespace unp;

int main(int argc, char const *argv[])
{
    char *proto[] = {"tcp", "udp", NULL};
    struct servent *sptr;
    for (int port = 0; port < 1024; port++)
    {
        for (int i = 0; proto[i] != NULL; i++)
        {
            if ((sptr = getservbyport(htons(port), proto[i])) != NULL)
            {
                printf("%d : %-20s\t%+8s\n", port, sptr->s_name, sptr->s_proto);
            }
        }
    }
    return 0;
}
