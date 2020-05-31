#ifndef _BAKA_MESH_H_
#define _BAKA_MESH_H_

#include "baka_gl/vertex_layout.h"
#include "baka_utils.h"

namespace baka
{

class Mesh
{
public:
    Mesh(Array vertices, gl::VertexLayout &vertexLayout, Array indices);
    ~Mesh();

private:
    Array vertices;
    Array indices;
    gl::VertexLayout vertex_layout;

};

}

#endif