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
    
    Mesh *CubePrimitive     (VertexBufferLayout &layout);
    Mesh *SpherePrimitive   (VertexBufferLayout &layout);
    Mesh *PlanePrimitive    (VertexBufferLayout &layout);
    Mesh *ConePrimitive     (VertexBufferLayout &layout);
    Mesh *CylinderPrimitive (VertexBufferLayout &layout);
    
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
            {VertexAttributeType::ATTRIBUTE_FLOAT, 3},
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

        case Primitive::PLANE:
            ret = PlanePrimitive(defaultLayout);
            break;

        case Primitive::CONE:
            ret = ConePrimitive(defaultLayout);
            break;

        case Primitive::CYLINDER:
            ret = CylinderPrimitive(defaultLayout);
            break;

        default: return nullptr;
        }

        meshes[meshName] = ret;
        return ret;
    }

    Mesh *CubePrimitive(VertexBufferLayout &layout)
    {
        float vertices[] = {
            //  1.0f,  1.0f, -1.0f,     0.0f,  0.0f, -1.0f,    // 2 1
            // -1.0f, -1.0f, -1.0f,     0.0f,  0.0f, -1.0f,    // 4 1
            // -1.0f,  1.0f, -1.0f,     0.0f,  0.0f, -1.0f,    // 1 1

            // -1.0f, -1.0f,  1.0f,     0.0f,  0.0f,  1.0f,    // 8 2
            //  1.0f,  1.0f,  1.0f,     0.0f,  0.0f,  1.0f,    // 6 2
            // -1.0f,  1.0f,  1.0f,     0.0f,  0.0f,  1.0f,    // 5 2

            // -1.0f,  1.0f,  1.0f,     0.0f,  1.0f,  0.0f,    // 5 3
            //  1.0f,  1.0f, -1.0f,     0.0f,  1.0f,  0.0f,    // 2 3
            // -1.0f,  1.0f, -1.0f,     0.0f,  1.0f,  0.0f,    // 1 3
             
            //  1.0f,  1.0f,  1.0f,     1.0f,  0.0f,  0.0f,    // 6 4
            //  1.0f, -1.0f, -1.0f,     1.0f,  0.0f,  0.0f,    // 3 4
            //  1.0f,  1.0f, -1.0f,     1.0f,  0.0f,  0.0f,    // 2 4

            // -1.0f,  1.0f,  1.0f,     0.0f, -1.0f,  0.0f,    // 3 5
            // -1.0f, -1.0f,  1.0f,     0.0f, -1.0f,  0.0f,    // 8 5
            // -1.0f, -1.0f, -1.0f,     0.0f, -1.0f,  0.0f,    // 4 5

            // -1.0f,  1.0f, -1.0f,    -1.0f,  0.0f,  0.0f,    // 1 6
            // -1.0f, -1.0f,  1.0f,    -1.0f,  0.0f,  0.0f,    // 8 6
            // -1.0f,  1.0f,  1.0f,    -1.0f,  0.0f,  0.0f,    // 5 6

            // -1.0f,  1.0f,  1.0f,     0.0f,  0.0f, -1.0f,    // 3 1
            //  1.0f, -1.0f,  1.0f,     0.0f,  0.0f,  1.0f,    // 7 2
            //  1.0f,  1.0f,  1.0f,     0.0f,  1.0f,  0.0f,    // 6 3
            //  1.0f, -1.0f,  1.0f,     1.0f,  0.0f,  0.0f,    // 7 4
            //  1.0f, -1.0f,  1.0f,     0.0f, -1.0f,  0.0f,    // 7 5
            // -1.0f, -1.0f, -1.0f,    -1.0f,  0.0f,  0.0f     // 4 6

            // Front face: white
            -1.0, -1.0,  1.0,  0.0,  0.0,  1.0,
            1.0, -1.0,  1.0,  0.0,  0.0,  1.0,
            1.0,  1.0,  1.0,  0.0,  0.0,  1.0, 
            -1.0,  1.0,  1.0,  0.0,  0.0,  1.0,

            // Back face: red
            -1.0, -1.0, -1.0,  0.0,  0.0, -1.0,
            -1.0,  1.0, -1.0,  0.0,  0.0, -1.0,
            1.0,  1.0, -1.0,  0.0,  0.0, -1.0,
            1.0, -1.0, -1.0,  0.0,  0.0, -1.0,

            // Top face: green
            -1.0,  1.0, -1.0,  0.0,  1.0,  0.0,
            -1.0,  1.0,  1.0,  0.0,  1.0,  0.0,
            1.0,  1.0,  1.0,  0.0,  1.0,  0.0,
            1.0,  1.0, -1.0,  0.0,  1.0,  0.0,

            // Bottom face: blue
            -1.0, -1.0, -1.0,  0.0, -1.0,  0.0,
            1.0, -1.0, -1.0,  0.0, -1.0,  0.0,
            1.0, -1.0,  1.0,  0.0, -1.0,  0.0, 
            -1.0, -1.0,  1.0,  0.0, -1.0,  0.0,

            // Right face: yellow
            1.0, -1.0, -1.0,  1.0,  0.0,  0.0,
            1.0,  1.0, -1.0,  1.0,  0.0,  0.0,
            1.0,  1.0,  1.0,  1.0,  0.0,  0.0,
            1.0, -1.0,  1.0,  1.0,  0.0,  0.0,

            // Left face: purple
            -1.0, -1.0, -1.0, -1.0,  0.0,  0.0,
            -1.0, -1.0,  1.0, -1.0,  0.0,  0.0,
            -1.0,  1.0,  1.0, -1.0,  0.0,  0.0,
            -1.0,  1.0, -1.0, -1.0,  0.0,  0.0,
        };

        std::uint32_t indices[] = {
             0,  1,  2,  0,  2,  3, // front
             4,  5,  6,  4,  6,  7, // back
             8,  9, 10,  8, 10, 11, // top
            12, 13, 14, 12, 14, 15, // bottom
            16, 17, 18, 16, 18, 19, // right
            20, 21, 22, 20, 22, 23, // left
        };

        VertexBuffer *vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        IndexBuffer *indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(std::uint32_t));
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

        float vertices[numVertices * (3 + 3)];
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

                const glm::vec3 vert = glm::vec3(
                    cosTheta * sinPhi, 
                    cosPhi, 
                    sinTheta * sinPhi);

                *(glm::vec3*)(&vertices[index]) = vert * radius;
                index += 3;

                *(glm::vec3*)(&vertices[index]) = vert / radius;
                index += 3;
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
                indices[index++] = (y + 1) * numVertsAround + x;
                indices[index++] = (y + 0) * numVertsAround + x;
                indices[index++] = (y + 0) * numVertsAround + x + 1;
                indices[index++] = (y + 1) * numVertsAround + x + 1;
                indices[index++] = (y + 1) * numVertsAround + x;
            }
        }

        VertexBuffer *vb = VertexBuffer::Create(vertices, sizeof(vertices));
        IndexBuffer *ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(std::uint32_t));
        return Mesh::Create(vb, layout, ib);
    }

    Mesh *PlanePrimitive(VertexBufferLayout &layout)
    {
        float vertices[] = {
            -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f
        };
        
        std::uint32_t indices[] = {
            0, 1, 2, 2, 3, 0,
        };

        VertexBuffer *vb = VertexBuffer::Create(vertices, sizeof(vertices));
        IndexBuffer *ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(std::uint32_t));
        return Mesh::Create(vb, layout, ib);
    }

    Mesh *ConePrimitive(VertexBufferLayout &layout)
    {
        const std::uint32_t baseVertCount = 12;
        const float radius = 1.0f;
        const float height = 1.0f;

        glm::vec3 vertices[baseVertCount + 2] = {{}};
        std::uint32_t indices[baseVertCount * 6] = {0};

        const std::uint32_t baseCenterIndex = 0;
        const std::uint32_t peakIndex = baseVertCount + 2 - 1;

        vertices[baseCenterIndex] = glm::vec3(0.0f, -height / 2.0f, 0.0f);
        vertices[peakIndex] = glm::vec3(0.0f, height / 2.0f, 0.0f);

        const float step = 2.0f * glm::pi<float>() / baseVertCount;
        for(std::uint32_t i = 1; i <= baseVertCount; i++)
        {
            float angle = step * i;
            vertices[i] = glm::vec3(
                radius * cos(angle),
                vertices[baseCenterIndex].y,
                radius * sin(angle)
            );
        }

        for(std::uint32_t i = 1; i <= baseVertCount; i++)
        {
            std::uint32_t nextVertexCicle = i + 1;
            if(nextVertexCicle >= peakIndex)
                nextVertexCicle = 1;
            std::uint32_t index = (i - 1) * 6;

            indices[index++] = nextVertexCicle;
            indices[index++] = baseCenterIndex;
            indices[index++] = i;

            indices[index++] = nextVertexCicle;
            indices[index++] = i;
            indices[index] = peakIndex;
        }

        VertexBuffer *vb = VertexBuffer::Create(vertices, sizeof(vertices));
        IndexBuffer *ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(std::uint32_t));
        return Mesh::Create(vb, layout, ib);
    }

    Mesh *CylinderPrimitive(VertexBufferLayout &layout)
    {
        const std::uint32_t sideCount = 12;
        const float radius = 1.0f;
        const float height = 1.0f;
        const std::uint32_t indicesPerSide = 3 * 4; // 4 faces, 3 verts per face

        glm::vec3 vertices[ sideCount * 2 + 2 ] = {{}};
        std::uint32_t indices[ sideCount * indicesPerSide ] = {0}; 

        const std::uint32_t bottomIndex = sideCount * 2 + 1;
        const std::uint32_t topIndex = bottomIndex - 1;

        vertices[bottomIndex] = glm::vec3(0.0f, -height / 2.0f, 0.0f);
        vertices[topIndex] =    glm::vec3(0.0f,  height / 2.0f, 0.0f);

        const float step = 2.0f * glm::pi<float>() / sideCount;
        for(std::uint32_t i = 0; i < sideCount; i++)
        {
            // VERTICES
            float angle = i * step;
            const float x = radius * cos(angle);
            const float z = radius * sin(angle);

            vertices[i] =             glm::vec3(x, -height / 2.0f, z);  // bottom
            vertices[i + sideCount] = glm::vec3(x,  height / 2.0f, z);  // top

            // INDICES
            std::uint32_t index = i * indicesPerSide;
            std::uint32_t botNextVert = (i + 1) % sideCount;
            std::uint32_t topNextVert = botNextVert + sideCount;
            
            indices[index++] = i;
            indices[index++] = botNextVert;
            indices[index++] = bottomIndex;

            indices[index++] = botNextVert;
            indices[index++] = i + sideCount;
            indices[index++] = topNextVert;

            indices[index++] = topNextVert;
            indices[index++] = i + sideCount;
            indices[index++] = topIndex;

            indices[index++] = i + sideCount;
            indices[index++] = botNextVert;
            indices[index++] = i;
        }

        VertexBuffer *vb = VertexBuffer::Create(vertices, sizeof(vertices));
        IndexBuffer *ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(std::uint32_t));
        return Mesh::Create(vb, layout, ib);
    }
} // namespace baka
