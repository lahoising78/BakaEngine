#include <GL/glew.h>

#include <baka_logger.h>
#include "baka_gl/vertex_buffer.h"
#include "baka_gl/utils.h"

namespace baka
{
namespace gl
{

void VertexBuffer::Create(unsigned long size, const void *data)
{
    bakalog("vertex buffer reserve %lu bytes", size);
    GLCALL(glGenBuffers(1, &this->renderer_id));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, this->renderer_id));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::Destroy()
{
    glDeleteBuffers(1, &this->renderer_id);
}

} // namespace gl
} // namespace baka
