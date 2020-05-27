#ifndef _BAKA_OPEN_GL_
#define _BAKA_OPEN_GL_

#include "baka_platform.h"
#include "baka_logger.h"

namespace baka 
{

#ifdef OPEN_GL_AVAILABLE

class GLGraphics
{
public:
    GLGraphics();
    ~GLGraphics();
    virtual void Init();
};

#else

BAKA_PLATFORM_NOT_FOUND(GLGraphics)

#endif /* end open gl available */

}

#endif