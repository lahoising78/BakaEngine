#ifndef _BAKA_OPEN_GL_
#define _BAKA_OPEN_GL_

#include "baka_platform.h"
#include "baka_logger.h"

struct SDL_Window;

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

private:
    static void SetContext( struct SDL_Window *window );
};

#else

BAKA_PLATFORM_NOT_FOUND(GLGraphics)

#endif /* end open gl available */

}

#endif