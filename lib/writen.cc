#include "unp.h"

namespace unp
{
    ssize_t writen(int fd, const void* vptr, size_t n)
    {
        size_t nleft;
        ssize_t nwritten;
        const char *ptr;

        ptr = (const char*)vptr;
        nleft = n;
        while (nleft > 0)
        {
            if ((nwritten = write(fd, ptr, nleft)) <= 0)
            {
                if (nwritten < 0 && errno == EINTR)
                    nwritten = 0; /* and call write() again */
                else
                    return (-1); /* error */
            }

            nleft -= nwritten;
            ptr += nwritten;
        }
        return (n);
    }
    /* end writen */

    ssize_t Writen(int fd, void *ptr, size_t nbytes)
    {
        ssize_t n;
        if ((n = writen(fd, ptr, nbytes)) != nbytes)
            err_msg("writen error");
        return n;
    }
} // namespace unp