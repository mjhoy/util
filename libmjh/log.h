#ifndef LOG_H
#define LOG_H

#define log_debug(...)      log_internal("[DEBUG]", 0, __FILE__, __LINE__, __func__, __VA_ARGS__)

int log_internal(const char *str,
                 int error,
                 const char *file,
                 int line,
                 const char *func,
                 const char *format, ...);

int log_internalv(const char *str,
                  int error,
                  const char *file,
                  int line,
                  const char *func,
                  const char *format,
                  va_list ap);

#endif
