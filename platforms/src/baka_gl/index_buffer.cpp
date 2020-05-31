#include <memory>
#include <cstring>

#include <GL/glew.h>

#include <baka_logger.h>
#include "baka_gl/index_buffer.h"
#include "baka_gl/utils.h"

namespace baka
{
namespace gl
{
    
void IndexBuffer::Create(unsigned int *indices, uint32_t count)
{
    this->count = count;

    GLCALL(glGenBuffers(1, &this->renderer_id));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->renderer_id));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->count * sizeof(unsigned int), indices, GL_STATIC_DRAW));

    bakalog("index buffer reserve %lu bytes", this->count * sizeof(unsigned int));
}

void IndexBuffer::Destroy()
{
    GLCALL(glDeleteBuffers(1, &this->renderer_id));
}

void IndexBuffer::Bind()
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->renderer_id));
}

void IndexBuffer::Unbind()
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

} // namespace gl
} // namespace baka
