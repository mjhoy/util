#include <stdarg.h>
#include "error_functions.h"
#include "mjh_common.h"
#include "ename.c.inc"          /* Defines ename and MAX_ENAME */

#ifdef __GNUC__                 /* Prevent 'gcc -Wall' complaining  */
__attribute__ ((__noreturn__))  /* if we call this function as last */
#endif                          /* statement in a non-void function */
static void terminate(Boolean use_exit3)
{
    char *s;

    /* Dump core if EF_DUMPCORE environment variable is defined and
       is a nonempty string; otherwise call exit(3) or _exit(2),
       depending on the value of 'useExit3'. */

    s = getenv("EF_DUMPCORE");

    if (s != NULL && *s != '\0')
        abort();
    else if (use_exit3)
        exit(EXIT_FAILURE);
    else
        _exit(EXIT_FAILURE);
}

/* Diagnose 'errno' error by:

      * outputting a string containing the error name (if available
        in 'ename' array) corresponding to the value in 'err', along
        with the corresponding error message from strerror(), and

      * outputting the caller-supplied error message specified in
        'format' and 'ap'. */

/* TODO move to log.c? */
static void output_error(Boolean use_err,
                         int err,
                         Boolean flush_stdout,
                         const char *file,
                         int line,
                         const char *func,
                         const char *format,
                         va_list ap)
{
#define BUF_SIZE 500
    char buf[BUF_SIZE], user_msg[BUF_SIZE], err_text[BUF_SIZE];

    vsnprintf(user_msg, BUF_SIZE, format, ap);

    if (use_err)
        snprintf(err_text, BUF_SIZE, " [%s %s]",
                 (err > 0 && err <= MAX_ENAME) ?
                 ename[err] : "?UNKNOWN?", strerror(err));
    else
        snprintf(err_text, BUF_SIZE, ":");

    snprintf(buf, BUF_SIZE, "ERROR %s (%s:%d)%s %s\n",
             func, file, line,
             err_text, user_msg);

    if (flush_stdout)
        fflush(stdout);       /* Flush any pending stdout */
    fputs(buf, stderr);
    fflush(stderr);           /* In case stderr is not line-buffered */
}

/* Display error message including 'errno' diagnostic, and
   return to caller */

void err_msg_internal(const char *file,
                      int line,
                      const char *func,
                      const char *format, ...)
{
    va_list arg_list;
    int saved_errno;

    saved_errno = errno;       /* In case we change it here */

    va_start(arg_list, format);
    output_error(TRUE, errno, TRUE, file, line, func, format, arg_list);
    va_end(arg_list);

    errno = saved_errno;
}

/* Display error message including 'errno' diagnostic, and
   terminate the process */

void err_exit_internal(const char *file,
                       int line,
                       const char *func,
                       const char *format, ...)
{
    va_list arg_list;

    va_start(arg_list, format);
    output_error(TRUE, errno, TRUE, file, line, func, format, arg_list);
    va_end(arg_list);

    terminate(TRUE);
}

/* Display error message including 'errno' diagnostic, and
   terminate the process by calling _exit().

   The relationship between this function and err_exit() is analogous
   to that between _exit(2) and exit(3): unlike err_exit(), this
   function does not flush stdout and calls _exit(2) to terminate the
   process (rather than exit(3), which would cause exit handlers to be
   invoked).

   These differences make this function especially useful in a library
   function that creates a child process that must then terminate
   because of an error: the child must terminate without flushing
   stdio buffers that were partially filled by the caller and without
   invoking exit handlers that were established by the caller. */

void _err_exit_internal(const char *file,
                        int line,
                        const char *func,
                        const char *format, ...)
{
    va_list arg_list;

    va_start(arg_list, format);
    output_error(TRUE, errno, FALSE, file, line, func, format, arg_list);
    va_end(arg_list);

    terminate(FALSE);
}

/* The following function does the same as errExit(), but expects
   the error number in 'errnum' */

void err_exit_en_internal(int errnum,
                          const char *file,
                          int line,
                          const char *func,
                          const char *format, ...)
{
    va_list arg_list;

    va_start(arg_list, format);
    output_error(TRUE, errnum, TRUE, file, line, func, format, arg_list);
    va_end(arg_list);

    terminate(TRUE);
}

/* Print an error message (without an 'errno' diagnostic) */

void fatal_internal(const char *file,
                    int line,
                    const char *func,
                    const char *format, ...)
{
    va_list arg_list;

    va_start(arg_list, format);
    output_error(FALSE, 0, TRUE, file, line, func, format, arg_list);
    va_end(arg_list);

    terminate(TRUE);
}

/* Print a command usage error message and terminate the process */

void usage_err(const char *format, ...)
{
    va_list arg_list;

    fflush(stdout);           /* Flush any pending stdout */

    fprintf(stderr, "Usage: ");
    va_start(arg_list, format);
    vfprintf(stderr, format, arg_list);
    va_end(arg_list);

    fflush(stderr);           /* In case stderr is not line-buffered */
    exit(EXIT_FAILURE);
}

/* Diagnose an error in command-line arguments and
   terminate the process */

void cmd_line_err(const char *format, ...)
{
    va_list arg_list;

    fflush(stdout);           /* Flush any pending stdout */

    fprintf(stderr, "Command-line usage error: ");
    va_start(arg_list, format);
    vfprintf(stderr, format, arg_list);
    va_end(arg_list);

    fflush(stderr);           /* In case stderr is not line-buffered */
    exit(EXIT_FAILURE);
}
