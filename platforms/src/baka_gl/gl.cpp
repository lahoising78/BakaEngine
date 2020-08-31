#ifdef OPEN_GL_AVAILABLE

#include <GL/glew.h>
#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <baka_logger.h>
#include <baka_graphics.h>
#include <baka_gl/gl.h>

#include <baka_gl/shaders.h>
#include <baka_buffer.h>
#include <baka_mesh.h>
#include <baka_path_explorer.h>

namespace baka
{
    extern Graphics *graphics;
    gl::Shader *defaultShader = nullptr;
    Mesh *mesh = nullptr;
    // VertexBuffer *vb = nullptr;
    // IndexBuffer *ib = nullptr;
    // unsigned int vertexArray;

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
        // meshes.clear();
        // if(vb) delete vb;
        // if(ib) delete ib;
        if(mesh) delete mesh;
        if(defaultShader) delete defaultShader;

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

        char folder[128];
        char path[256];
        char *vert = nullptr;
        char *frag = nullptr;

        baka::PathExplorer explorer = baka::PathExplorer::Get();
        explorer.GetEngineDirectory(folder);

        std::sprintf(path, "%s/shaders/default.vert", folder);
        vert = explorer.ReadFile(path, nullptr);

        std::sprintf(path, "%s/shaders/default.frag", folder);
        frag = explorer.ReadFile(path, nullptr);

        defaultShader = new gl::Shader();
        defaultShader->Create(vert, frag);

        if(vert) delete vert;
        if(frag) delete frag;

        // glGenVertexArrays(1, &vertexArray);
        // glBindVertexArray(vertexArray);

        float vertices[] = 
        {
            -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f        
        };
        VertexBuffer *vb = VertexBuffer::Create(vertices, sizeof(vertices));

        VertexBufferLayout layout = VertexBufferLayout({
            { VertexAttributeType::ATTRIBUTE_FLOAT, 3 },
            { VertexAttributeType::ATTRIBUTE_FLOAT, 4 }
        });

        // int i = 0;
        // for(const auto &a : layout)
        // {
        //     glEnableVertexAttribArray(i);
        //     glVertexAttribPointer(i, a.count, AttribTypeToGLType(a.attribType), a.normalize? GL_TRUE : GL_FALSE, layout.GetStride(), (const void *)a.offset);
        //     i++;
        // }

        std::uint32_t indices[] = { 0, 1, 2 };
        IndexBuffer *ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(std::uint32_t));

        mesh = Mesh::Create(vb,layout, ib);
    }

    void GLGraphics::Render()
    {
        this->RenderBegin();

            defaultShader->Bind();
            // for(auto &m : meshes)
            // {
            //     m.second->Render();
            // }
            mesh->Render();
            // glBindVertexArray(vertexArray);
            // glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr);

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