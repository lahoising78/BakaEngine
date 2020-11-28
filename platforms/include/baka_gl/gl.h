#ifndef _BAKA_OPEN_GL_
#define _BAKA_OPEN_GL_

#include <unordered_map>

#include "baka_logger.h"
#include "baka_platform.h"

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

    static GLGraphics &Get()
    {
        static GLGraphics glGraphics = GLGraphics();
        return glGraphics;
    }

protected:
    virtual void Init();
    virtual void RenderBegin();
    virtual void Render( );
    virtual void RenderEnd();

private:
    SDL_GLContext gl_context;
};

#else

BAKA_PLATFORM_NOT_FOUND(GLGraphics)

#endif /* end open gl available */

}

#endif