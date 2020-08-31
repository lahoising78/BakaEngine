#include <GL/glew.h>

#include <baka_logger.h>
#include <baka_vertex_buffer_layout.h>

namespace baka
{
    VertexAttribute::VertexAttribute(VertexAttributeType attribType, std::uint32_t count)
        : count(count), 
        size(count * VertexBufferLayout::GetSizeOfAttribType(attribType)), 
        offset(0),
        normalize(false), 
        attribType(attribType) {}

    std::uint32_t VertexBufferLayout::GetSizeOfAttribType(VertexAttributeType attribType)
    {
        switch (attribType)
        {
        case VertexAttributeType::ATTRIBUTE_FLOAT: return sizeof(float);
        }

        BAKA_ASSERT(false);
        return 0;
    }

    VertexBufferLayout::VertexBufferLayout( std::initializer_list<VertexAttribute> attributes )
        : attributes(attributes)
    {
        CalculateStrideAndOffsets();
    }

    void VertexBufferLayout::CalculateStrideAndOffsets()
    {
        stride = 0;

        for(auto &a : attributes)
        {
            a.offset = (std::size_t)stride;
            stride += a.size;
        }
    }
} // namespace baka
