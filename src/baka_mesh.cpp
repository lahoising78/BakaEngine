#include <unordered_map>

#include <baka_logger.h>

#include <baka_graphics.h>
#include <baka_mesh.h>

#include <baka_gl/mesh.h>

namespace baka
{
    static std::unordered_map<const char*,Mesh*> meshes;
    Mesh *CubePrimitive(VertexBufferLayout &layout);
    
    Mesh *Mesh::Create(VertexBuffer *vertexBuffer, VertexBufferLayout &layout, IndexBuffer *indexBuffer)
    {
        Graphics &graphics = Graphics::Get();

        switch (graphics.GetEnabledAPI())
        {
        case GraphicsAPI::BAKA_GAPI_OPENGL:         return new gl::Mesh(vertexBuffer, layout, indexBuffer);
        default:                                    BAKA_ASSERT(false); return nullptr;
        }
    }

    Mesh *Mesh::PrimitiveMesh(Primitive primitive)
    {
        static VertexBufferLayout defaultLayout = VertexBufferLayout({
            {VertexAttributeType::ATTRIBUTE_FLOAT, 3}
        });
        
        Mesh *ret = nullptr;
        char meshName[32];
        PrimitiveAsString(primitive, meshName);

        if(meshes.find(meshName) != meshes.end()) 
            return meshes[meshName];
        
        switch (primitive)
        {
        case Primitive::CUBE: 
            ret = CubePrimitive(defaultLayout);
            break;
        default: return nullptr;
        }

        meshes[meshName] = ret;
        return ret;
    }

    Mesh *CubePrimitive(VertexBufferLayout &layout)
    {
        float vertices[] = {
            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f
        };

        std::uint32_t indices[] = {
            1, 3, 0,
            7, 5, 4,
            4, 1, 0,
            5, 2, 1,
            2, 7, 3,
            0, 7, 4,
            1, 2, 3,
            7, 6, 5,
            4, 5, 1,
            5, 6, 2,
            2, 6, 7,
            0, 3, 7
        };

        VertexBuffer *vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        IndexBuffer *indexBuffer = IndexBuffer::Create(indices, sizeof(indices));
        return Mesh::Create(vertexBuffer, layout, indexBuffer);
    }
} // namespace baka
