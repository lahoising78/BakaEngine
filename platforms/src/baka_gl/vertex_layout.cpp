#include <GL/glew.h>

#include "baka_logger.h"
#include "baka_gl/vertex_layout.h"

namespace baka
{
namespace gl
{
    VertexLayout::VertexLayout()
        : stride(0)
    {
        attributes.clear();
    }

    void VertexLayout::AddAttribute(VertexAttributeElement attr)
    {
        attributes.push_back(attr);
        stride += (int)attr.count * GetSizeOfType(attr.type);
    }

    int VertexLayout::GetSizeOfType(int type)
    {
        switch (type)
        {
        case GL_FLOAT: return sizeof(float);
        
        default: 
            bakawarn("Type not yet supported %d", type);
            return 0;
        }
    }

} // namespace gl
} // namespace baka
