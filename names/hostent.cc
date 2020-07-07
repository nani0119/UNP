#include "unp.h"

using namespace std;
using namespace unp;

int main(int argc, char const *argv[])
{
    const char* ptr;
    char** pptr;
    struct hostent *hptr;
    char str[INET_ADDRSTRLEN];

    while(--argc > 0)
    {
        ptr = *++argv;
        if((hptr = gethostbyname(ptr)) == NULL)
        {
            err_msg("gethostbyname error for host: %s: %s", ptr, hstrerror(h_errno));
            continue;
        }

        printf("official hostname:%s\n", hptr->h_name);

        for(pptr = hptr->h_addr_list; *pptr != NULL; pptr++)
        {
            printf("\talias: %s\n", *pptr);
        }

        switch(hptr->h_addrtype)
        {
            case AF_INET:
                pptr = hptr->h_addr_list;
                for(;*pptr != NULL; ++pptr)
                {
                    printf("\taddress: %s\n",Inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
                }
                break;
            default:
                err_ret("unknow address type");
                break;
        }
    } 
    return 0;
}
