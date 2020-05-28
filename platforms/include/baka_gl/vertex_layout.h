#ifndef _BAKA_GL_VERTEX_LAYOUT_H_
#define _BAKA_GL_VERTEX_LAYOUT_H_

#include <vector>
#include <stdint.h>

namespace baka
{
namespace gl
{

    typedef struct
    {
        uint32_t    count;
        int         type;
        int         normalize;
    } VertexAttributeElement;

    class VertexLayout
    {
    public:
        VertexLayout();
        void AddAttribute(VertexAttributeElement attr);

        uint32_t GetCount() { return attributes.size(); }
        const std::vector<VertexAttributeElement> &GetAttributes() { return attributes; }
        int GetStride() { return stride; }

        static int GetSizeOfType(int type);

    private:
        std::vector<VertexAttributeElement> attributes;
        int stride;
    };

} // namespace gl
} // namespace baka


#endif