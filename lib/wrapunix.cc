#include "unp.h"

namespace unp
{
    int Close(int fd)
    {
        int ret;
        if ((ret = close(fd)) == -1)
        {
            err_msg("close error");
        }
        return ret;
    }

    int Ioctl(int fd, int request, void *arg)
    {
        int n;

        if ((n = ioctl(fd, request, arg)) == -1)
        {
            err_msg("ioctl error");
        }
        return n; /* streamio of I_LIST returns value */
    }

    pid_t Fork(void)
    {
        pid_t pid;

        if ((pid = fork()) == -1)
        {
            err_msg("fork error");
        }
        return (pid);
    }

    void *Malloc(size_t size)
    {
        void *ptr;

        if ((ptr = malloc(size)) == NULL)
        {
            err_msg("malloc error");
        }
        return ptr;
    }

    void * Mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset)
    {
        void *ptr;

        if ((ptr = mmap(addr, len, prot, flags, fd, offset)) == ((void *)-1))
        {
            err_msg("mmap error");
        }
        return ptr;
    }

    int Open(const char *pathname, int oflag, mode_t mode)
    {
        int fd;

        if ((fd = open(pathname, oflag, mode)) == -1)
        {
            err_msg("open error for %s", pathname);
        }
        return fd;
    }

    int Pipe(int *fds)
    {
        int ret;
        if (pipe(fds) < 0)
            err_msg("pipe error");
        return ret;
    }

    ssize_t Read(int fd, void *ptr, size_t nbytes)
    {
        ssize_t n;

        if ((n = read(fd, ptr, nbytes)) == -1)
            err_msg("read error");

        return n;
    }

    int Sigaddset(sigset_t *set, int signo)
    {
        int ret;
        if ((ret = sigaddset(set, signo)) == -1)
            err_msg("sigaddset error");
        
        return ret;
    }

    int Sigdelset(sigset_t *set, int signo)
    {
        int ret;
        if ((ret = sigdelset(set, signo)) == -1)
            err_msg("sigdelset error");
        
        return ret;
    }

    int Sigemptyset(sigset_t *set)
    {
        int ret;
        if ((ret = sigemptyset(set)) == -1)
            err_msg("sigemptyset error");
        return ret;
    }

    int Sigfillset(sigset_t *set)
    {
        int ret;
        if ((ret = sigfillset(set)) == -1)
            err_msg("sigfillset error");
        return ret;
    }

    int Sigismember(const sigset_t *set, int signo)
    {
        int n;

        if ((n = sigismember(set, signo)) == -1)
            err_msg("sigismember error");
        return n;
    }

    int Sigpending(sigset_t *set)
    {
        int ret;
        if ((ret = sigpending(set)) == -1)
            err_msg("sigpending error");
        return ret;
    }

    int Sigprocmask(int how, const sigset_t *set, sigset_t *oset)
    {
        int ret;
        if ((ret = sigprocmask(how, set, oset)) == -1)
            err_msg("sigprocmask error");
        
        return ret;
    }

    char* Strdup(const char *str)
    {
        char *ptr;

        if ((ptr = strdup(str)) == NULL)
            err_msg("strdup error");
        return ptr;
    }

    int Unlink(const char *pathname)
    {
        int ret;
        if ((ret = unlink(pathname)) == -1)
            err_msg("unlink error for %s", pathname);

        return ret;
    }

    pid_t Wait(int *iptr)
    {
        pid_t pid;

        if ((pid = wait(iptr)) == -1)
            err_msg("wait error");
        
        return pid;
    }

    pid_t Waitpid(pid_t pid, int *iptr, int options)
    {
        pid_t retpid;

        if ((retpid = waitpid(pid, iptr, options)) == -1)
            err_msg("waitpid error");
        
        return retpid;
    }

    ssize_t Write(int fd, void *ptr, size_t nbytes)
    {
        ssize_t n;
        if ((n = write(fd, ptr, nbytes)) == -1)
        {
            err_msg("write error");
        }
        return n;
    }

    int Fcntl(int fd, int cmd, int arg)
    {
        int n;

        if ((n = fcntl(fd, cmd, arg)) == -1)
        {
            err_msg("fcntl error");
        }
        return (n);
    }
    int Dup2(int fd1, int fd2)
    {
        int ret;
        if ((ret = dup2(fd1, fd2)) == -1)
        {
            err_msg("dup2 error");
        }
        return ret;
    }

} // namespace unp