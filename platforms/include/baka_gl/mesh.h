#ifndef _BAKA_GL_MESH_H_
#define _BAKA_GL_MESH_H_

#include <cstdint>

#include <baka_mesh.h>

namespace baka
{
namespace gl
{
    
class Mesh : public baka::Mesh
{
public:
    Mesh(VertexBuffer *vertexBuffer, VertexBufferLayout &layout, IndexBuffer *indexBuffer);
    ~Mesh();
    void Render() const override;

private:
    VertexBuffer *vertexBuffer;
    IndexBuffer *indexBuffer;
    std::uint32_t vertexArrayId;
};

} // namespace gl
} // namespace baka

#endif