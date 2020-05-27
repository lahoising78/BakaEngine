#ifdef OPEN_GL_AVAILABLE

#include "baka_logger.h"
#include "baka_open_gl.h"

namespace baka
{

    GLGraphics::GLGraphics()
    {
        bakalog("Hello from GLGraphics");
    }

    GLGraphics::~GLGraphics()
    {
        bakalog("GLGraphics closed");
    }

    void GLGraphics::Init()
    {
        bakalog("gl graphics initialized");
    }
    
} // namespace baka


#endif