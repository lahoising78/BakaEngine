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
#include "baka_gl/mesh.h"
#include <baka_path_explorer.h>

namespace baka
{
    extern Graphics *graphics;

    gl::Mesh *m_mesh;
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
        shader.Destroy();
        if(m_mesh) delete m_mesh;

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

        GLenum res = glewInit();
        if( res != GLEW_OK )
        {
            bakawarn("Unable to initialize glew");
            return;
        } 

        bakalog("gl graphics initialized. using version %s", glGetString(GL_VERSION));

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        float w = (float)Graphics::Get().GetWindowWidth() / 4;
        float h = (float)Graphics::Get().GetWindowHeight() / 4;
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

        bakalog("3 * sizeof(float) = %lu", 3 * sizeof(float));
        Array vertices = {};
        vertices.count = 6;
        vertices.data = positions;

        gl::VertexLayout layout;
        
        gl::VertexAttributeElement attr = {};
        attr.count = 3;
        attr.normalize = GL_FALSE;
        attr.type = GL_FLOAT;
        layout.AddAttribute(attr);

        bakalog("layout stride = %lu", layout.GetStride());

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,

            1, 4, 5,
            5, 2, 1
        };

        Array indicesArray = {};
        indicesArray.count = 6 * 2;
        indicesArray.data = indices;

        m_mesh = new gl::Mesh(vertices, layout, indicesArray);

        char buff[512];
        baka::PathExplorer::Get().GetEngineDirectory(buff);
        sprintf(buff, "%s%s", buff, "/shaders/default.vert");
        bakalog("default.vert path: %s", buff);
        char *vertShader = baka::PathExplorer::Get().ReadFile(buff, nullptr);
    	if(vertShader)
        {
            bakalog("vert shader content:\n%s", vertShader);
        }
        
        memset(buff, 0, sizeof(buff));
        baka::PathExplorer::Get().GetEngineDirectory(buff);
        sprintf(buff, "%s%s", buff, "/shaders/default.frag");
        bakalog("default.frag path: %s", buff);
        char *fragShader = baka::PathExplorer::Get().ReadFile(buff, nullptr);
        if(fragShader)
        {
            bakalog("frag shader content:\n%s", fragShader);
        }
        
        shader.Create(vertShader, fragShader);
        shader.Bind();

        if(vertShader) free(vertShader);
        if(fragShader) free(fragShader);

        modelMat = glm::mat4(1.0);

        // 2d camera
        // OrthographicsCamera cam = OrthographicsCamera();

        // 3d camera
        Camera cam = Camera(90.0f);
        // cam.SetPosition(glm::vec3(0, 0, -2));

        modelMat = cam.GetViewProjection() * modelMat;

        int location = glGetUniformLocation(shader.GetRendererId(), "u_modelMat");
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMat));
    }

    void GLGraphics::Render()
    {
        this->RenderBegin();

            shader.Bind();

            if(m_mesh) m_mesh->Render();

        this->RenderEnd();
    }

    void GLGraphics::RenderBegin()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLGraphics::RenderEnd()
    {
        SDL_GL_SwapWindow(graphics->GetWindow());
    }
} // namespace baka


#endif