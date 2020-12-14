#ifndef _BAKA_MESH_H_
#define _BAKA_MESH_H_

#include <baka_buffer.h>
#include <baka_primitives.h>

namespace baka
{
class Mesh
{
public:
    virtual ~Mesh() {}
    
    static Mesh *Create(VertexBuffer *vertexBuffer, VertexBufferLayout &layout, IndexBuffer *indexBuffer);
    static Mesh *PrimitiveMesh(Primitive primitive);

    virtual void Render() const = 0;
};
} // namespace baka


#endif