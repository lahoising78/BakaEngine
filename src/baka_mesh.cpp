#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

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
        const std::uint32_t heightDivisions = 12;
        const std::uint32_t widthDivisions  = heightDivisions * 2;
        const std::uint32_t numVertices = (heightDivisions + 1) * (widthDivisions + 1);
        const float radius = 1.0f;
        const float pi = glm::pi<float>();
        const float pi2 = pi * 2.0f;

        glm::vec3 vertices[numVertices];
        std::uint32_t index = 0;
        for (int y = 0; y <= heightDivisions; y++) {
            const float v = (float)y / heightDivisions;
            const float phi = v * pi;
            const float sinPhi = sin(phi);
            const float cosPhi = cos(phi);
            
            for (int x = 0; x <= widthDivisions; x++) {
                // Generate a vertex based on its spherical coordinates
                const float u = (float)x / widthDivisions;
                const float theta = u * pi2;
                const float sinTheta = sin(theta);
                const float cosTheta = cos(theta);

                vertices[index++] = glm::vec3(
                    cosTheta * sinPhi, 
                    cosPhi, 
                    sinTheta * sinPhi) * radius;
            }
        }

        const std::uint32_t numVertsAround = widthDivisions + 1;
        std::uint32_t indices[widthDivisions * heightDivisions * 6];
        index = 0;
        for(std::uint32_t x = 0; x < widthDivisions; x++)
        {
            for(std::uint32_t y = 0; y < heightDivisions; y++)
            {
                indices[index++] = (y + 0) * numVertsAround + x + 1;
                indices[index++] = (y + 0) * numVertsAround + x;
                indices[index++] = (y + 1) * numVertsAround + x;
                indices[index++] = (y + 0) * numVertsAround + x + 1;
                indices[index++] = (y + 1) * numVertsAround + x;
                indices[index++] = (y + 1) * numVertsAround + x + 1;
            }
        }

        VertexBuffer *vb = VertexBuffer::Create(&vertices[0].x, sizeof(vertices));
        IndexBuffer *ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(std::uint32_t));
        return Mesh::Create(vb, layout, ib);
    }
} // namespace baka
