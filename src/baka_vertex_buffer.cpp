// #include <baka_logger.h>

// #include <baka_graphics.h>

// #include <baka_vertex_buffer.h>

// #include <baka_gl/vertex_buffer.h>

// namespace baka
// {
    
//     VertexBuffer *VertexBuffer::Create(void *data, std::size_t size)
//     {
//         Graphics &graphics = Graphics::Get();

//         switch (graphics.GetEnabledAPI())
//         {
//         case GraphicsAPI::BAKA_GAPI_OPENGL: return new gl::VertexBuffer(data, size);
//         default:                            BAKA_ASSERT(false); return nullptr;
//         }
//     }

// } // namespace baka