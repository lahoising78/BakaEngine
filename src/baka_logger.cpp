#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "baka_logger.h"

#ifdef _WIN32
    #define BAKA_FILE_SEPARATOR '\\'
#else
    #define BAKA_FILE_SEPARATOR '/'
#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    BakaLogBitMask msg_mask;
} BakaLogger;

static BakaLogger g_baka_logger = {0};

void baka_log_filter_output(BakaLogBitMask mask, BakaLogAction action)
{
    switch (action)
    {
    case BAKA_LOG_ACTION_ON:
        g_baka_logger.msg_mask |= mask;
        break;

    case BAKA_LOG_ACTION_OFF:
        g_baka_logger.msg_mask &= ~mask;
        break;
    
    case BAKA_LOG_ACTION_SET:
        g_baka_logger.msg_mask = mask;
        break;

    default:
        break;
    }
}

void baka_log_init()
{
    g_baka_logger.msg_mask = BAKA_LOG_BIT_ALL;
}

const char *logger_get_filename(const char *filename, char separator = BAKA_FILE_SEPARATOR)
{
    const char *sepPos = strrchr(filename, separator);

    return sepPos? sepPos + 1 : filename;
}

void _baka_log(const char *f, int l, const char *colorStart, const char *colorEnd, BakaLogPriorityFlagBit priority, const char *msg,...)
{
    va_list va;

    if( !(g_baka_logger.msg_mask & priority) ) return;
    
    va_start(va, msg);
    printf("%s%s(%d):%s ", colorStart, logger_get_filename(f), l, colorEnd);
    vprintf(msg, va);
    printf("\n");
    va_end(va);
}

#ifdef __cplusplus
}
#endif