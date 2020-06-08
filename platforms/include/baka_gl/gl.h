#ifndef _BAKA_OPEN_GL_
#define _BAKA_OPEN_GL_

#include "baka_platform.h"
#include "baka_logger.h"

struct SDL_Window;
typedef void *SDL_GLContext;

namespace baka 
{

#ifdef OPEN_GL_AVAILABLE

class GLGraphics
{
friend class Graphics;

public:
    GLGraphics();
    ~GLGraphics();
    virtual void Init();
    virtual void Render();

    static GLGraphics &Get()
    {
        static GLGraphics glGraphics = GLGraphics();
        return glGraphics;
    }

private:
    virtual void RenderBegin();
    virtual void RenderEnd();

private:
    SDL_GLContext gl_context;
};

#else

BAKA_PLATFORM_NOT_FOUND(GLGraphics)

#endif /* end open gl available */

}

#endif