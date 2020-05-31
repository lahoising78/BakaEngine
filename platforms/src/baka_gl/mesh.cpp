#include <GL/glew.h>
#include "baka_gl/mesh.h"

namespace baka
{
namespace gl
{
    
Mesh::Mesh(Array vertices, VertexLayout &vertexLayout, Array indices)
    : baka::Mesh(vertices, vertexLayout, indices)
{
    this->vao = {};
    this->vb = {};
    this->ib = {};

    this->vb.Create(vertices.count * vertexLayout.GetStride(), vertices.data);
    this->vao.Create(this->vb.GetRendererId(), vertexLayout);
    this->ib.Create((unsigned int *)indices.data, indices.count);
}

Mesh::~Mesh()
{
    this->vb.Destroy();
    this->ib.Destroy();
    this->vao.Destroy();
}

void Mesh::Render()
{
    this->vao.Bind();
    this->ib.Bind();

    glDrawElements(GL_TRIANGLES, this->ib.GetCount(), BAKA_GL_INDEX_TYPE, nullptr);
}

} // namespace gl
} // namespace baka
