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
#include "baka_camera.h"

namespace baka
{
    gl::VertexArray vao;
    gl::VertexBuffer vb;
    gl::IndexBuffer ib;
    gl::Shader shader;

    glm::mat4 modelMat;
    glm::mat4 view;
    glm::mat4 proj;

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

        // float w = (float)Graphics::GetWidth() / 4;
        // float h = (float)Graphics::GetHeight() / 4;
        float positions[] = {
            // -w,     -h,
            //  w,     -h,
            //  w,      h,
            // -w,      h
            -0.5, -0.5, -1.0f,
             0.5, -0.5,  1.0f,
             0.5,  0.5,  1.0f,
            -0.5,  0.5, -1.0f,

             1.5, -0.5,  1.0f,
             1.5,  0.5,  1.0f
        };

        vb.Create(6 * 3 * sizeof(float), positions);

        gl::VertexLayout layout;
        
        gl::VertexAttributeElement attr = {};
        attr.count = 3;
        attr.normalize = GL_FALSE;
        attr.type = GL_FLOAT;
        layout.AddAttribute(attr);

        vao.Create(vb.GetRendererId(), layout);

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,

            1, 4, 5,
            5, 2, 1
        };

        ib.Create(indices, 6 * 2);

        std::string vertShader = Utils::ReadFile("baka_engine/shaders/default.vert");
        std::string fragShader = Utils::ReadFile("baka_engine/shaders/default.frag");
        shader.Create(vertShader.c_str(), fragShader.c_str());
        shader.Bind();

        modelMat = glm::mat4(1.0);

        // 2d camera
        // OrthographicsCamera cam = OrthographicsCamera();

        // 3d camera
        Camera cam = Camera(90.0f);
        cam.SetPosition(glm::vec3(0, 0, -2));

        modelMat = cam.GetViewProjection() * modelMat;

        int location = glGetUniformLocation(shader.GetRendererId(), "u_modelMat");
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMat));
    }

    void GLGraphics::Render()
    {
        this->RenderBegin();

            shader.Bind();

            vao.Bind();
            ib.Bind();

            glDrawElements(GL_TRIANGLES, 6 * 2, GL_UNSIGNED_INT, nullptr);

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