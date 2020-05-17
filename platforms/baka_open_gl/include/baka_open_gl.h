#ifndef _BAKA_OPEN_GL_
#define _BAKA_OPEN_GL_

#include "baka_logger.h"

namespace baka 
{

#ifndef OPEN_GL_AVAILABLE

class OpenGLGraphics
{
public:
    OpenGLGraphics() {}
    ~OpenGLGraphics() { bakalog("open gl graphics bye"); }
};

#else

class OpenGLGraphics
{
public:
    OpenGLGraphics();
    ~OpenGLGraphics();
};

#endif /* end open gl available */

}

#endif