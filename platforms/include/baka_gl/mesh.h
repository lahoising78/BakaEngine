#ifndef _BAKA_GL_MESH_H_
#define _BAKA_GL_MESH_H_

#include "baka_gl/vertex_array.h"
#include "baka_gl/vertex_buffer.h"
#include "baka_gl/index_buffer.h"
#include "baka_mesh.h"

namespace baka
{
namespace gl
{
    
class Mesh : public baka::Mesh
{
public:
    Mesh(Array vertices, VertexLayout &vertexLayout, Array indices);
    ~Mesh();

    void Render();

private:
    VertexArray vao;
    VertexBuffer vb;
    IndexBuffer ib;

};

} // namespace gl
} // namespace baka


#endif