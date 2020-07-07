#include "unp.h"

using namespace std;
using namespace unp;

int main(int argc, char const *argv[])
{
    struct servent* hptr;
    for(int i = 1; i < argc; i++)
    {
        if((hptr = getservbyname(argv[i], "tcp")) != NULL)
        {
            printf("official name:%s\n", hptr->s_name);
            printf("\tproto :%s\n", hptr->s_proto);
            printf("\tprot  :%d\n", ntohs(hptr->s_port));
            for(int j = 0; hptr->s_aliases[j] != NULL; j++)
            {
                printf("\talias :%s\n", hptr->s_aliases[j]);
            }
        }
        else
        {
            printf("%s was not use tcp port\n", argv[1]);
        }

        if((hptr = getservbyname(argv[i], "udp")) != NULL)
        {
            printf("official name:%s\n", hptr->s_name);
            printf("\tproto :%s\n", hptr->s_proto);
            printf("\tprot  :%d\n", ntohs(hptr->s_port));
            for(int j = 0; hptr->s_aliases[j] != NULL; j++)
            {
                printf("\talias :%s\n", hptr->s_aliases[j]);
            }
        }
        else
        {
            printf("%s was not use udp port\n", argv[1]);
        }
    } 
    return 0;
}
