#include <unordered_map>

#include <baka_logger.h>

#include <baka_graphics.h>
#include <baka_mesh.h>

#include <baka_gl/mesh.h>

namespace baka
{
    static std::unordered_map<const char*,Mesh*> meshes;
    Mesh *CubePrimitive(VertexBufferLayout &layout);
    Mesh *SpherePrimitive(VertexBufferLayout &layout);
    
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

        case Primitive::SPHERE:
            ret = SpherePrimitive(defaultLayout);
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

    Mesh *SpherePrimitive(VertexBufferLayout &layout)
    {
        const float X = 0.525731112119133606f;
        const float Z = 0.850650808352039932f;

        float vertices[] = {
               -X,  0.0f,     Z,
                X,  0.0f,     Z,
               -X,  0.0f,    -Z,
                X,  0.0f,    -Z,
             0.0f,     Z,     X,
             0.0f,     Z,    -X,
             0.0f,    -Z,     X,
             0.0f,    -Z,    -X,
                Z,     X,  0.0f,
               -Z,     X,  0.0f,
                Z,    -X,  0.0f,
               -Z,    -X,  0.0f
        };

        std::uint32_t indices[] = {
            0,4,1,
            0,9,4,
            9,5,4,
            4,5,8,
            4,8,1,
            8,10,1,
            8,3,10,
            5,3,8,
            5,2,3,
            2,7,3,
            7,10,3,
            7,6,10,
            7,11,6,
            11,0,6,
            0,1,6,
            6,1,10,
            9,0,11,
            9,11,2,
            9,2,5,
            7,2,11
        };

        VertexBuffer *vb = VertexBuffer::Create(vertices, sizeof(vertices));
        IndexBuffer *ib = IndexBuffer::Create(indices, sizeof(indices));
        return Mesh::Create(vb, layout, ib);
    }
} // namespace baka
