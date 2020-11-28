#ifdef OPEN_GL_AVAILABLE

#include <iostream>

#include <GL/glew.h>
#include <SDL.h>

#include <glm/glm.hpp>
// #include <glm/gtx/string_cast.hpp>

#include <baka_logger.h>
#include <baka_input.h>
#include <baka_graphics.h>
#include <baka_gl/gl.h>
#include <baka_vertex_buffer_layout.h>

namespace baka
{
    extern Graphics *graphics;

    static GLenum AttribTypeToGLType(VertexAttributeType type)
    {
        switch (type)
        {
        case VertexAttributeType::ATTRIBUTE_FLOAT: return GL_FLOAT;
        }
        return 0;
    }

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
        this->gl_context = SDL_GL_CreateContext(graphics->GetWindow());
        if( !this->gl_context )
        {
            bakawarn("Unable to create gl context");
            return;
        }

        if( SDL_GL_SetSwapInterval( 0 ) < 0 )
        {
            printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
        }


        GLenum res = glewInit();
        if( res != GLEW_OK )
        {
            bakawarn("Unable to initialize glew");
            return;
        } 

        bakalog("gl graphics initialized. using version %s", glGetString(GL_VERSION));

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    }

    void GLGraphics::Render(  )
    {
        static Input &input = Input::Get();
        if(input.WindowResizedThisFrame()) 
        {
            int w = 0;
            int h = 0;
            graphics->GetWindowSize(&w, &h);
            glViewport(0, 0, w, h);
        }

        this->RenderBegin();
            
        this->RenderEnd();
    }

    void GLGraphics::RenderBegin()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        static Input &input = Input::Get();
        if(input.WindowResizedThisFrame()) 
        {
            int w = 0;
            int h = 0;
            graphics->GetWindowSize(&w, &h);
            glViewport(0, 0, w, h);
        }
    }

    void GLGraphics::RenderEnd()
    {
        SDL_GL_SwapWindow(graphics->GetWindow());
    }
} // namespace baka


#endif