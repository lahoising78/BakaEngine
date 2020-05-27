#ifndef _BAKA_PLATFORM_H_
#define _BAKA_PLATFORM_H_

#include "baka_logger.h"

#define BAKA_PLATFORM_NOT_FOUND(Platform) \
class Platform {\
public:\
    Platform(){ bakaerr( #Platform " not found"); }\
    ~Platform(){}\
    void Init(){}\
};

#endif