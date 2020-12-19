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
            -1.0f,  1.0f,  0.0f,    0.0f, 0.0f, -1.0f,
             1.0f,  1.0f,  0.0f,    0.0f, 0.0f, -1.0f,
             1.0f, -1.0f,  0.0f,    0.0f, 0.0f, -1.0f,
            -1.0f, -1.0f,  0.0f,    0.0f, 0.0f, -1.0f,
            
            -1.0f,  1.0f,  0.0f,    0.0f, 0.0f,  1.0f,
            -1.0f, -1.0f,  0.0f,    0.0f, 0.0f,  1.0f,
             1.0f, -1.0f,  0.0f,    0.0f, 0.0f,  1.0f,
             1.0f,  1.0f,  0.0f,    0.0f, 0.0f,  1.0f
        };
        
        std::uint32_t indices[] = {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4
        };

        VertexBuffer *vb = VertexBuffer::Create(vertices, sizeof(vertices));
        IndexBuffer *ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(std::uint32_t));
        return Mesh::Create(vb, layout, ib);
    }

    void addVertexToConeBuffer(float *buffer, std::uint32_t index, glm::vec3 pos, glm::vec3 normal)
    {
        memcpy(&buffer[index], &pos, sizeof(glm::vec3));
        memcpy(&buffer[index+3], &normal, sizeof(glm::vec3));
    }

    Mesh *ConePrimitive(VertexBufferLayout &layout)
    {
        const std::uint32_t baseVertCount = 12;
        const float radius = 1.0f;
        const float height = 1.0f;
        const std::uint32_t stride = 6;
        const std::uint32_t offset = baseVertCount * stride;

        float vertices[(baseVertCount * 3 + 1) * stride] = {0};
        std::uint32_t indices[baseVertCount * 6] = {0};

        const std::uint32_t baseCenterIndex = (baseVertCount * 3) * stride;
        glm::vec3 pos = glm::vec3(0.0f, -height / 2.0f, 0.0f);
        glm::vec3 normal = glm::vec3(0.0f, -1.0f, 0.0f);
        addVertexToConeBuffer(vertices, baseCenterIndex, pos, normal);

        const glm::vec3 peak = glm::vec3(0.0f, height / 2.0f, 0.0f);
        const float slope = sin(atan2f(peak.y, radius));
        const float step = 2.0f * glm::pi<float>() / baseVertCount;
        for(std::uint32_t i = 0; i < baseVertCount; i++)
        {
            float angle = step * i;
            std::uint32_t index = i * stride;
            
            // base slope
            pos = glm::vec3(
                radius * cos(angle),
                vertices[baseCenterIndex+1],
                radius * sin(angle)
            );
            normal = glm::normalize(glm::vec3(cos(angle), slope, sin(angle)));
            addVertexToConeBuffer(vertices, index, pos, normal);

            // peak
            index += offset;
            angle += step * 0.5f;
            normal = glm::normalize(glm::vec3(cos(angle), slope, sin(angle)));
            addVertexToConeBuffer(vertices, index, peak, normal);
            
            // base down
            index += offset;
            normal = glm::vec3(0.0f, -1.0f, 0.0f);
            addVertexToConeBuffer(vertices, index, pos, normal);
        }

        for(std::uint32_t i = 0; i < baseVertCount; i++)
        {
            std::uint32_t nextVertexCicle = (i + 1) % baseVertCount;
            std::uint32_t index = i * 6;

            indices[index++] = nextVertexCicle + offset * 2;
            indices[index++] = baseCenterIndex;
            indices[index++] = i + offset * 2;

            indices[index++] = nextVertexCicle;
            indices[index++] = i + offset;
            indices[index++] = i;
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

        glm::vec3 vertices[ (sideCount * 4 + 2) * 2 ] = {{}};
        std::uint32_t indices[ sideCount * indicesPerSide ] = {0}; 

        // base and top indices as vertices (pos and normals count as only one)
        const std::uint32_t bottomIndex = sideCount * 4 + 1;
        const std::uint32_t topIndex = bottomIndex - 1;

        vertices[bottomIndex * 2] = glm::vec3(0.0f, -height / 2.0f, 0.0f);
        vertices[bottomIndex * 2 + 1] = glm::vec3(0.0f, -1.0f, 0.0f);

        vertices[topIndex * 2] =    glm::vec3(0.0f,  height / 2.0f, 0.0f);
        vertices[topIndex * 2 + 1] = glm::vec3(0.0f, 1.0f, 0.0f);

        const float step = 2.0f * glm::pi<float>() / sideCount;
        const std::uint32_t offset = sideCount * 2;
        for(std::uint32_t i = 0; i < sideCount; i++)
        {
            // VERTICES
            float angle = i * step;
            const float x = radius * cos(angle);
            const float z = radius * sin(angle);
            std::uint32_t index = i * 2;

            vertices[index] =                   glm::vec3(x, -height / 2.0f, z);    // bottom
            vertices[index + 1] =               glm::vec3(0.0f, -1.0f, 0.0f);       // down

            vertices[index + offset] =          glm::vec3(x,  height / 2.0f, z);    // top
            vertices[index + offset + 1] =      glm::vec3(0.0f,  1.0f, 0.0f);       // up
            
            vertices[index + offset * 2] =      glm::vec3(x, -height / 2.0f, z);    // bottom
            vertices[index + offset * 2 + 1] =  glm::vec3(x, 0.0f, z);              // side

            vertices[index + offset * 3] =      glm::vec3(x, height / 2.0f, z);     // top
            vertices[index + offset * 3 + 1] =  glm::vec3(x, 0.0f, z);              // side

            // INDICES
            index = i * indicesPerSide;
            std::uint32_t nextVert = (i + 1) % sideCount;
            
            indices[index++] = i;
            indices[index++] = nextVert;
            indices[index++] = bottomIndex;

            indices[index++] = i + sideCount * 3;
            indices[index++] = nextVert + sideCount * 3;
            indices[index++] = nextVert + sideCount * 2;

            indices[index++] = nextVert + sideCount;
            indices[index++] = i + sideCount;
            indices[index++] = topIndex;

            indices[index++] = nextVert + sideCount * 2;
            indices[index++] = i + sideCount * 2;
            indices[index++] = i + sideCount * 3;
        }

        VertexBuffer *vb = VertexBuffer::Create(vertices, sizeof(vertices));
        IndexBuffer *ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(std::uint32_t));
        return Mesh::Create(vb, layout, ib);
    }
} // namespace baka
