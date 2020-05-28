#ifndef _BAKA_GL_VERTEX_ARRAY_H_
#define _BAKA_GL_VERTEX_ARRAY_H_

#include "baka_gl/vertex_layout.h"

namespace baka
{
namespace gl
{
    
class VertexArray
{
public:
    void Create(unsigned int vertexBufferId, VertexLayout &vertexLayout);
    void Bind();
    void Unbind();
    void Destroy();

private:
    unsigned int renderer_id;
};

} // namespace gl
} // namespace baka

#endif