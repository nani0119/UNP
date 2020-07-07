#include "unp.h"

using namespace std;
using namespace unp;

int main(int argc, char const *argv[])
{
    struct in_addr addr;
    struct hostent	*hptr;

    for(int i = 1; i < argc; i++)
    {
        if(Inet_pton(AF_INET, argv[i], &addr) <= 0)
        {
            printf("Not in presentation format");
        }
		if ( (hptr = gethostbyaddr(&addr, sizeof(addr), AF_INET)) == NULL) {
			err_msg("gethostbyaddr error for host: %s: %s",argv[i], hstrerror(h_errno));
			continue;
		}
        printf("host addres:%s\n", argv[i]);
        printf("\tofficial hostname: %s\n", hptr->h_name);
    }
    return 0;
}
