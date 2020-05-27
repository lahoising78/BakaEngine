#ifndef _BAKA_GL_INDEX_BUFFER_H_
#define _BAKA_GL_INDEX_BUFFER_H_

#include <stdint.h>

namespace baka
{
namespace gl
{
    
class IndexBuffer
{
public:
    void Create(unsigned int *indices, uint32_t count);
    void Destroy();
    void Bind();
    void Unbind();

private:
    unsigned int renderer_id;
    uint32_t count;
};

} // namespace gl
} // namespace baka


#endif