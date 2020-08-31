#include <baka_graphics.h>
#include <baka_buffer.h>

#include <baka_gl/buffer.h>

namespace baka
{
    VertexBuffer *VertexBuffer::Create(void *data, std::size_t size)
    {
        Graphics &graphics = Graphics::Get();
        switch (graphics.GetEnabledAPI())
        {
        case GraphicsAPI::BAKA_GAPI_OPENGL:   return new gl::VertexBuffer(data, size);
        default:                              return nullptr;
        }
    }

    IndexBuffer *IndexBuffer::Create(std::uint32_t *data, std::size_t size)
    {
        Graphics &graphics = Graphics::Get();
        switch (graphics.GetEnabledAPI())
        {
        case GraphicsAPI::BAKA_GAPI_OPENGL:   return new gl::IndexBuffer(data, size);
        default:                              return nullptr;
        }
    }
} // namespace baka
