#ifdef OPEN_GL_AVAILABLE

#include <GL/glew.h>
#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "baka_logger.h"
#include "baka_gl/gl.h"
#include "baka_graphics.h"
#include "baka_utils.h"
#include "baka_gl/shaders.h"
#include "baka_gl/vertex_buffer.h"
#include "baka_gl/index_buffer.h"
#include "baka_gl/utils.h"
#include "baka_gl/vertex_array.h"

namespace baka
{
    gl::VertexArray vao;
    gl::VertexBuffer vb;
    gl::IndexBuffer ib;
    gl::Shader shader;
    glm::mat4 viewProjection;

    GLGraphics::GLGraphics()
    {
        bakalog("Hello from GLGraphics");
    }

    GLGraphics::~GLGraphics()
    {
        vb.Destroy();
        ib.Destroy();
        shader.Destroy();
        vao.Destroy();
        // glDeleteVertexArrays(1, &vao);

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

        float positions[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f 
        };

        vb.Create(4 * 2 * sizeof(float), positions);

        gl::VertexLayout layout;
        
        gl::VertexAttributeElement attr = {};
        attr.count = 2;
        attr.normalize = GL_FALSE;
        attr.type = GL_FLOAT;
        layout.AddAttribute(attr);

        vao.Create(vb.GetRendererId(), layout);

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        ib.Create(indices, 6);

        std::string vertShader = Utils::ReadFile("baka_engine/shaders/default.vert");
        std::string fragShader = Utils::ReadFile("baka_engine/shaders/default.frag");
        shader.Create(vertShader.c_str(), fragShader.c_str());
        shader.Bind();
    }

    void GLGraphics::Render()
    {
        this->RenderBegin();

            shader.Bind();

            vao.Bind();
            ib.Bind();

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
} // namespace baka


#endif