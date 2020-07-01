#include "unp.h"

namespace unp
{
    const char* Inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
    {
        const char *ptr = nullptr;

        if (strptr == NULL) /* check for old code */
            err_msg("NULL 3rd argument to inet_ntop");

        if ((ptr = inet_ntop(family, addrptr, strptr, len)) == NULL)
            err_msg("inet_ntop error"); /* sets errno */

        return ptr;
    }

    int Inet_pton(int family, const char *strptr, void *addrptr)
    {
        int n;

        if ((n = inet_pton(family, strptr, addrptr)) < 0)
            err_msg("inet_pton error for %s", strptr); /* errno set */

        else if (n == 0)
            err_msg("inet_pton error for %s", strptr); /* errno not set */

        return n;
    }
}