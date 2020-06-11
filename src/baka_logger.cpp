#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "baka_logger.h"

#ifdef _WIN32
    #define BAKA_FILE_SEPARATOR '\\'
#else
    #define BAKA_FILE_SEPARATOR '/'
#endif

const char *logger_get_filename(const char *filename, char separator = BAKA_FILE_SEPARATOR)
{
    const char *sepPos = strrchr(filename, separator);

    return sepPos? sepPos + 1 : filename;
}

void _baka_log(const char *f, int l, const char *colorStart, const char *colorEnd, const char *msg, ...)
{
    va_list va;
    
    va_start(va, msg);
    printf("%s%s(%d):%s ", colorStart, logger_get_filename(f), l, colorEnd);
    vprintf(msg, va);
    printf("\n");
    va_end(va);
}