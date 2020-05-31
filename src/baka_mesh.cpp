#include <baka_mesh.h>

namespace baka
{

Mesh::Mesh(Array vertices, gl::VertexLayout &vertexLayout, Array indices)
{
    this->vertices = vertices;
    this->vertex_layout = vertexLayout;
    this->indices = indices;
}

Mesh::~Mesh()
{

}


}