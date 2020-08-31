#ifndef _BAKA_MESH_H_
#define _BAKA_MESH_H_

#include <baka_buffer.h>

namespace baka
{
class Mesh
{
public:
    virtual ~Mesh() {}
    static Mesh *Create(VertexBuffer *vertexBuffer, VertexBufferLayout &layout, IndexBuffer *indexBuffer);

    virtual void Render() const = 0;
};
} // namespace baka


#endif