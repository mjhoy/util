#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

#ifdef __GNUC__

    /* This macro stops 'gcc -Wall' complaining that "control reaches
       end of non-void function" if we use the following functions to
       terminate main() or some other non-void function. */

#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

/* TODO this should be log_err? */
#define err_msg(...) err_msg_internal(__FILE__, __LINE__, __func__, __VA_ARGS__)
#define err_exit(...) err_exit_internal(__FILE__, __LINE__, __func__, __VA_ARGS__)
#define _err_exit(...) _err_exit_internal(__FILE__, __LINE__, __func__, __VA_ARGS__)
#define err_exit_en(e, ...) err_exit_en_internal(e, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define fatal(...) fatal_internal(__FILE__, __LINE__, __func__, __VA_ARGS__)

void usage_err(const char *format, ...) NORETURN ;

void cmd_line_err(const char *format, ...) NORETURN ;

/* called from macros with filename, line number, function filled in */
void err_msg_internal(const char *file,
                      int line,
                      const char *func,
                      const char *format, ...);

void err_exit_internal(const char *file,
                       int line,
                       const char *func,
                       const char *format, ...) NORETURN ;

void _err_exit_internal(const char *file,
                        int line,
                        const char *func,
                        const char *format, ...) NORETURN ;

void err_exit_en_internal(int errnum,
                          const char *file,
                          int line,
                          const char *func,
                          const char *format, ...) NORETURN ;

void fatal_internal(const char *file,
                    int line,
                    const char *func,
                    const char *format, ...) NORETURN ;

#endif
