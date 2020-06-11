#ifndef _BAKA_LOGGER_H_
#define _BAKA_LOGGER_H_

#include <cstdlib>

extern "C"
{

typedef enum
{
    BAKA_LOG_BIT_UNKNOWN    = 0,
    BAKA_LOG_BIT_INFO       = 1,
    BAKA_LOG_BIT_WARN       = 2,
    BAKA_LOG_BIT_ERR        = 4,
    BAKA_LOG_BIT_ALL        = (BAKA_LOG_BIT_ERR << 1) - 1
} BakaLogPriorityFlagBit;

typedef char BakaLogBitMask;

enum BakaLogAction
{
    BAKA_LOG_ACTION_UNKNOWN = 0,
    BAKA_LOG_ACTION_ON      = 1,
    BAKA_LOG_ACTION_OFF     = 2,
    BAKA_LOG_ACTION_SET     = 3
};

#define bakalog(...) _baka_log(__FILE__,__LINE__,"","",BAKA_LOG_BIT_INFO,__VA_ARGS__)
#define bakaerr(...) _baka_log(__FILE__, __LINE__, "\033[1;31m", "\033[0m",BAKA_LOG_BIT_ERR,__VA_ARGS__)
#define bakawarn(...) _baka_log(__FILE__, __LINE__, "\033[1;33m", "\033[0m",BAKA_LOG_BIT_WARN,__VA_ARGS__)

void _baka_log(const char *f, int l, const char *colorStart, const char *colorEnd,BakaLogPriorityFlagBit priority,const char *msg,...);
void baka_log_filter_output(BakaLogBitMask, BakaLogAction);

void baka_log_init();

#define BAKA_ASSERT(expr)\
if((expr))\
{\
\
}\
else\
{\
    bakaerr("%s returned false",#expr);\
    abort();\
}

}

#endif