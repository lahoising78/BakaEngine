#ifndef _BAKA_GL_BUFFER_H_
#define _BAKA_GL_BUFFER_H_

#include <cstdint>

#include <baka_buffer.h>

namespace baka
{
namespace gl
{
    
class VertexBuffer : public baka::VertexBuffer
{
public:
    VertexBuffer(const void *data, std::size_t size);
    ~VertexBuffer();
    void Bind() const override;
    void Unbind() const override;

public:
    unsigned int GetBufferId() { return bufferId; }

private:
    unsigned int bufferId;
};
    
class IndexBuffer : public baka::IndexBuffer
{
public:
    IndexBuffer(std::uint32_t *data, std::uint32_t count);
    ~IndexBuffer();
    void Bind() const override;
    void Unbind() const override;
    std::uint32_t GetCount() const override { return indexCount; }

public:
    unsigned int GetBufferId() { return bufferId; }

private:
    std::uint32_t indexCount;
    unsigned int bufferId;
};

} // namespace gl
} // namespace baka

#endif