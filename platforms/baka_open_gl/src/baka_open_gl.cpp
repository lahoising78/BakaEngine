#ifdef OPEN_GL_AVAILABLE

#include <GL/glew.h>
// #include <GL/gl.h>
#include <SDL.h>
#include "baka_logger.h"
#include "baka_open_gl.h"

namespace baka
{
    typedef struct
    {
        SDL_GLContext gl_context;
    } GLGraphicsManager;

    static GLGraphicsManager gl_manager = {};

    GLGraphics::GLGraphics()
    {
        bakalog("Hello from GLGraphics");
    }

    GLGraphics::~GLGraphics()
    {
        bakalog("GLGraphics closed");
    }

    void GLGraphics::SetContext( struct SDL_Window *window )
    {
        gl_manager.gl_context = SDL_GL_CreateContext(window);
        if( !gl_manager.gl_context )
        {
            bakawarn("Unable to create gl context");
            return;
        }

        GLenum res = glewInit();
        if( res != GLEW_OK )
        {
            bakawarn("Unable to initialize glew");
            return;
        } 

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    }

    void GLGraphics::Init()
    {
        bakalog("gl graphics initialized");
    }
    
} // namespace baka


#endif