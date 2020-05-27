#ifdef OPEN_GL_AVAILABLE

#include <GL/glew.h>
#include <SDL.h>
#include "baka_logger.h"
#include "baka_open_gl.h"
#include "baka_graphics.h"
#include "baka_utils.h"
#include "baka_gl_shaders.h"

#define GLCALL(fx)  fx;\
                    this->ReadErrors(__LINE__)

namespace baka
{
    unsigned int vao;
    unsigned int vb;
    unsigned int ib;
    GLShader shader;

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

    GLGraphics::GLGraphics()
    {
        bakalog("Hello from GLGraphics");
    }

    GLGraphics::~GLGraphics()
    {
        glDeleteBuffers(1, &vb);
        glDeleteBuffers(1, &ib);
        shader.Destroy();
        glDeleteVertexArrays(1, &vao);

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

        bakalog("gl graphics initialized. using version %s", glGetString(GL_VERSION));

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        GLCALL(glGenVertexArrays(1, &vao));
        GLCALL(glBindVertexArray(vao));

        float positions[] = {
            -0.5f, -0.5f,   1.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f,   0.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f,   0.5f, 0.0f, 0.5f, 1.0f,
            -0.5f,  0.5f,   0.3f, 0.2f, 1.0f, 1.0f
        };

        GLCALL(glGenBuffers(1, &vb));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vb));
        GLCALL(glBufferData(GL_ARRAY_BUFFER, 4 * 6 * sizeof(float), positions, GL_STATIC_DRAW));

        GLCALL(glEnableVertexAttribArray(0));
        GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0));

        GLCALL(glEnableVertexAttribArray(1));
        GLCALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (const void *)(2 * sizeof(float))));

        GLCALL(glGenBuffers(1, &ib));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib));
        GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

        std::string vertShader = Utils::ReadFile("baka_engine/shaders/default.vert");
        std::string fragShader = Utils::ReadFile("baka_engine/shaders/default.frag");
        shader.Create(vertShader.c_str(), fragShader.c_str());
        shader.Bind();
    }

    void GLGraphics::Render()
    {
        this->RenderBegin();

            shader.Bind();

            glBindVertexArray(vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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

    void GLGraphics::ReadErrors(unsigned int line)
    {
        int err;
        while( err = glGetError() )
        {
            bakaerr("gl error at line %u: %s", line, glewGetErrorString(err));
        }
    }
} // namespace baka


#endif