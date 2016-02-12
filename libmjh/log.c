#include <stdarg.h>
#include "mjh_common.h"
#include "log.h"

int log_internalv(const char *str,
                  int error,
                  const char *file,
                  int line,
                  const char *func,
                  const char *format,
                  va_list ap)
{
#define BUF_SIZE 500
    char buf[BUF_SIZE], user_msg[BUF_SIZE], log_text[BUF_SIZE];

    vsnprintf(user_msg, BUF_SIZE, format, ap);
    snprintf(log_text, BUF_SIZE, "%s (%s:%d)", func, file, line);

    snprintf(buf, BUF_SIZE, "%s %s: %s\n", str, log_text, user_msg);

    fputs(buf, stderr);
    fflush(stderr);

    return 0;
}

int log_internal(const char *str,
                 int error,
                 const char *file,
                 int line,
                 const char *func,
                 const char *format, ...)
{
    va_list ap;
    int r;

    va_start(ap, format);
    r = log_internalv(str, error, file, line, func, format, ap);
    va_end(ap);

    return r;
}
