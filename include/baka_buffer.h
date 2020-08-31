#ifndef _BAKA_BUFFER_H_
#define _BAKA_BUFFER_H_

#include <cstdint>
#include <baka_vertex_buffer_layout.h>

namespace baka
{
    
class VertexBuffer
{
public:
    virtual ~VertexBuffer() {};

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    static VertexBuffer *Create(void *data, std::size_t size);
};
    
class IndexBuffer
{
public:
    virtual ~IndexBuffer() {};

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual std::uint32_t GetCount() const = 0;

    static IndexBuffer *Create(std::uint32_t *data, std::size_t size);
};

} // namespace baka

#endif