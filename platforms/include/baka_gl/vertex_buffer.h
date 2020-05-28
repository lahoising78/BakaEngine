#ifndef _BAKA_GL_VERTEX_BUFFER_H_
#define _BAKA_GL_VERTEX_BUFFER_H_

namespace baka
{
namespace gl
{

class VertexBuffer
{
public:
    void Create(unsigned long size, const void *data);
    void Destroy();
    unsigned int GetRendererId() { return renderer_id; }

private:
    unsigned int renderer_id;
};

} // namespace gl
} // namespace baka


#endif