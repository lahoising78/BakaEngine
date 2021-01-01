#ifndef _BAKA_VERTEX_BUFFER_LAYOUT_H_
#define _BAKA_VERTEX_BUFFER_LAYOUT_H_

#include <cstdint>
#include <vector>

namespace baka
{

typedef enum VertexAttributeType_t: std::uint8_t
{
    ATTRIBUTE_FLOAT,
    ATTRIBUTE_MAT3X3,
    ATTRIBUTE_MAT4X4,
    ATTRIBUTE_INT,
    ATTRIBUTE_BOOL
} VertexAttributeType;

struct VertexAttribute
{
    std::uint32_t count;
    std::uint32_t size;
    std::size_t offset;
    bool normalize;
    VertexAttributeType attribType;

    VertexAttribute(VertexAttributeType attribType, std::uint32_t count);
};

class VertexBufferLayout
{
public:
    VertexBufferLayout( std::initializer_list<VertexAttribute> attributes );
    std::uint32_t GetStride() { return this->stride; }
    static std::uint32_t GetSizeOfAttribType(VertexAttributeType attribType);

    std::vector<VertexAttribute>::iterator begin() { return attributes.begin(); }
    std::vector<VertexAttribute>::iterator end() { return attributes.end(); }

private:
    void CalculateStrideAndOffsets();

private:
    std::vector<VertexAttribute> attributes;
    std::uint32_t stride;
};

} // namespace baka

#endif