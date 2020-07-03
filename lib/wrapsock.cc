#include "unp.h"

namespace unp
{
    int Socket(int family, int type, int protocol)
    {
        int n;
        if ((n = socket(family, type, protocol)) < 0)
        {
            err_msg("socket error");
        }
        return n;
    }

    int Accept(int fd, struct sockaddr* sa, socklen_t* salenptr)
    {
        int acceptfd;
again:     
        if((acceptfd = accept(fd, sa, salenptr)) < 0)
        {
#ifdef	EPROTO
		    if (errno == EPROTO || errno == ECONNABORTED)
#else
		    if (errno == ECONNABORTED)
#endif
            {
                goto again;
            }
            else
            {
                err_msg("accept error");
            }
        }
        return acceptfd;

    }

    int Bind(int fd, const struct sockaddr* sa, socklen_t salen)
    {
        int ret;
        if((ret = bind(fd, sa, salen)) < 0)
        {
            err_msg("bind error");
        }
        return ret;
    }

    int Connect(int fd, const struct sockaddr* sa, socklen_t salen)
    {
        int ret;
        if((ret = connect(fd, sa, salen)) < 0)
        {
            err_msg("connect error");
        }
        return ret;
    }

    int Getpeername(int fd, struct sockaddr *sa, socklen_t *salenptr)
    {
        int ret;
        if ((ret = getpeername(fd, sa, salenptr)) < 0)
        {
            err_msg("getpeername error");
        }
        return ret;
    }

    int Getsockname(int fd, struct sockaddr *sa, socklen_t *salenptr)
    {
        int ret;
        if ((ret = getsockname(fd, sa, salenptr)) < 0)
        {
            err_msg("getsockname error");
        }
        return  ret;
    }

    int Getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlenptr)
    {
        int ret;
        if ((ret = getsockopt(fd, level, optname, optval, optlenptr)) < 0)
        {    
            err_msg("getsockopt error");
        }
        return ret;
    }


    int Listen(int fd, int backlog)
    {
        int ret;
        char *ptr;

        /*4can override 2nd argument with environment variable */
        if ((ptr = getenv("LISTENQ")) != NULL)
        {
            backlog = atoi(ptr);
        }
        if ((ret = listen(fd, backlog)) < 0)
        {
            err_msg("listen error");
        }
        return ret;
    }

    int Poll(struct pollfd *fdarray, unsigned long nfds, int timeout)
    {
        int n;
        if ((n = poll(fdarray, nfds, timeout)) < 0)
        {
            err_msg("poll error");
        }
        return n;
    }

    int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
    {
        int n;

        if ((n = select(nfds, readfds, writefds, exceptfds, timeout)) < 0)
        {
            err_msg("select error");
        }
        return n; /* can return 0 on timeout */
    }

    int Shutdown(int fd, int how)
    {
        int ret;
        if ((ret = shutdown(fd, how)) < 0)
        {
            err_msg("shutdown error");
        }
        return ret;
    }
}