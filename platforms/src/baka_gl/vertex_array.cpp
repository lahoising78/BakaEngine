#include <GL/glew.h>

#include "baka_gl/utils.h"
#include "baka_gl/vertex_array.h"

namespace baka
{
namespace gl
{
    
void VertexArray::Create(unsigned int vertexBufferId, VertexLayout &vertexLayout)
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId));

    GLCALL(glGenVertexArrays(1, &this->renderer_id));
    GLCALL(glBindVertexArray(this->renderer_id));

    long int offset = 0;
    const auto attrs = vertexLayout.GetAttributes();
    unsigned int i;
    for(i = 0; i < attrs.size(); i++)
    {
        GLCALL(glEnableVertexAttribArray(i));
        GLCALL(glVertexAttribPointer(i, attrs[i].count, attrs[i].type, attrs[i].normalize, vertexLayout.GetStride(), (const void *)offset));
        offset += VertexLayout::GetSizeOfType(attrs[i].type) * attrs[i].count;
    }
}

void VertexArray::Bind()
{
    GLCALL(glBindVertexArray(this->renderer_id));
}

void VertexArray::Unbind()
{
    GLCALL(glBindVertexArray(0));
}

void VertexArray::Destroy()
{
    GLCALL(glDeleteVertexArrays(1, &this->renderer_id));
}

} // namespace gl
} // namespace baka
