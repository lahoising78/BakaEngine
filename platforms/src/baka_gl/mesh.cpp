#include <GL/glew.h>

#include <baka_logger.h>
#include <baka_gl/mesh.h>

namespace baka
{
    namespace gl
    {
        static GLenum AttribTypeToGLType(VertexAttributeType type)
        {
            switch (type)
            {
            case VertexAttributeType::ATTRIBUTE_FLOAT: return GL_FLOAT;
            }
            return 0;
        }
        
        Mesh::Mesh(VertexBuffer *vertexBuffer, VertexBufferLayout &layout, IndexBuffer *indexBuffer)
        {
            glCreateVertexArrays(1, &this->vertexArrayId);
            glBindVertexArray(this->vertexArrayId);

            this->vertexBuffer = vertexBuffer;
            BAKA_ASSERT(vertexBuffer);

            this->vertexBuffer->Bind();
            int i = 0;
            for(const auto &a : layout)
            {
                glEnableVertexAttribArray(i);
                glVertexAttribPointer(i, a.count, AttribTypeToGLType(a.attribType), a.normalize? GL_TRUE : GL_FALSE, layout.GetStride(), (const void *)a.offset);
                i++;
            }

            this->indexBuffer = indexBuffer;
            BAKA_ASSERT(indexBuffer);
            this->indexBuffer->Bind();
            glBindVertexArray(0);
        }

        Mesh::~Mesh()
        {
            BAKA_ASSERT(vertexBuffer);
            delete vertexBuffer;
            BAKA_ASSERT(this->indexBuffer);
            delete indexBuffer;
            glDeleteVertexArrays(1, &this->vertexArrayId);
        }

        void Mesh::Render() const
        {
            glBindVertexArray(this->vertexArrayId);
            BAKA_ASSERT(indexBuffer);
            glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
        }

    } // namespace gl
} // namespace baka
