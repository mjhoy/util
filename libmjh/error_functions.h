#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

void err_msg(const char *format, ...);

#ifdef __GNUC__

    /* This macro stops 'gcc -Wall' complaining that "control reaches
       end of non-void function" if we use the following functions to
       terminate main() or some other non-void function. */

#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

void err_exit(const char *format, ...) NORETURN ;

void _err_exit(const char *format, ...) NORETURN ;

void err_exit_en(int errnum, const char *format, ...) NORETURN ;

void fatal(const char *format, ...) NORETURN ;

void usage_err(const char *format, ...) NORETURN ;

void cmd_line_err(const char *format, ...) NORETURN ;

#endif
