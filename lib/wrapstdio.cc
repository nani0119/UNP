#include "unp.h"

namespace unp
{

    int Fclose(FILE *fp)
    {
        int ret;
        if ((ret = fclose(fp)) != 0)
            err_msg("fclose error");
        return ret;
    }

    FILE* Fdopen(int fd, const char *type)
    {
        FILE *fp = nullptr;

        if ((fp = fdopen(fd, type)) == NULL)
            err_msg("fdopen error");

        return (fp);
    }

    char* Fgets(char *ptr, int n, FILE *stream)
    {
        char *rptr = nullptr;

        if ((rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
            err_msg("fgets error");

        return rptr;
    }

    FILE* Fopen(const char *filename, const char *mode)
    {
        FILE *fp;

        if ((fp = fopen(filename, mode)) == NULL)
            err_sys("fopen error");

        return (fp);
    }

    int Fputs(const char *ptr, FILE *stream)
    {
        int ret;
        if ((ret = fputs(ptr, stream)) == EOF)
            err_msg("fputs error");
        return ret;
    }
} // namespace unp