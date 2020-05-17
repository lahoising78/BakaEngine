#include "baka_logger.h"
#include "baka_open_gl.h"

#ifndef OPEN_GL_AVAILABLE

#else

OpenGLGraphics::OpenGLGraphics()
{
    bakalog("Hello from OpenGLGraphics");
}

OpenGLGraphics::~OpenGLGraphics()
{

}

#endif