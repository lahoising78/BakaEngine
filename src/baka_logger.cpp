#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "baka_logger.h"

const char *logger_get_filename(const char *filename, char separator = '/')
{
    const char *sepPos = strrchr(filename, separator);

    return sepPos? sepPos + 1 : "";
}

void _baka_log(const char *f, int l, const char *msg,...)
{
    va_list va;
    
    va_start(va, msg);
    printf("%s:%d: ", logger_get_filename(f), l);
    printf(msg, va);
    printf("\n");
    va_end(va);
}