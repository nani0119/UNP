#ifndef	__unp_h
#define	__unp_h
#include "config.h"

extern "C" {
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>	/* inet(3) functions */
#include <sys/un.h>

}

/* Following shortens all the typecasts of pointer arguments: */
#define	SA	struct sockaddr

/* Miscellaneous constants */
#define	MAXLINE		4096	/* max text line length */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

namespace  unp
{
    void err_ret(const char *fmt, ...);
    void err_sys(const char *fmt, ...);
    void err_dump(const char *fmt, ...);
    void err_msg(const char *fmt, ...);
    void err_quit(const char *fmt, ...);
    char *Sock_ntop(const struct sockaddr *sa, socklen_t salen);
}

#endif
