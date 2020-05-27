#ifdef OPEN_GL_AVAILABLE

#include <GL/glew.h>
// #include <GL/gl.h>
#include <SDL.h>
#include "baka_logger.h"
#include "baka_open_gl.h"
#include "baka_graphics.h"

namespace baka
{
    GLGraphics::GLGraphics()
    {
        bakalog("Hello from GLGraphics");
    }

    GLGraphics::~GLGraphics()
    {
        SDL_GL_DeleteContext(this->gl_context);
        bakalog("GLGraphics closed");
    }

    void GLGraphics::Init()
    {
        this->gl_context = SDL_GL_CreateContext(Graphics::GetWindow());
        if( !this->gl_context )
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
        bakalog("gl graphics initialized");
    }

    void GLGraphics::Render()
    {
        this->RenderBegin();

            glBegin(GL_TRIANGLES);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f( 0.5f, -0.5f);
            glVertex2f( 0.5f,  0.5f);
            glEnd();

        this->RenderEnd();
    }

    void GLGraphics::RenderBegin()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLGraphics::RenderEnd()
    {
        SDL_GL_SwapWindow(Graphics::GetWindow());
    }

    
} // namespace baka


#endif