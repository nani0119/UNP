#ifndef	__unp_h
#define	__unp_h
#include "config.h"

extern "C" {
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

}

/* Following shortens all the typecasts of pointer arguments: */
#define	SA	struct sockaddr

#endif
