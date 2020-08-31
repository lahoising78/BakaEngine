// #include <GL/glew.h>

// #include <baka_gl/vertex_buffer.h>

// namespace baka
// {
// namespace gl
// {
    
//     VertexBuffer::VertexBuffer(const void *data, std::size_t size)
//     {
//         glGenBuffers(1, &this->bufferId);
//         glBindBuffer(GL_ARRAY_BUFFER, this->bufferId);
//         glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
//     }

//     VertexBuffer::~VertexBuffer()
//     {
//         glDeleteBuffers(1, &this->bufferId);
//     }

//     void VertexBuffer::Bind() const
//     {
//         glBindBuffer(GL_ARRAY_BUFFER, this->bufferId);
//     }

//     void VertexBuffer::Unbind() const
//     {
//         glBindBuffer(GL_ARRAY_BUFFER, 0);
//     }

// } // namespace gl
// } // namespace baka