#ifndef _BAKA_GL_INDEX_BUFFER_H_
#define _BAKA_GL_INDEX_BUFFER_H_

#include <stdint.h>
#include <GL/glew.h>

#define BAKA_GL_INDEX_TYPE GL_UNSIGNED_INT

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

    uint32_t GetCount() { return this->count; }
    // const unsigned int *GetIndices() { return this->indices; }

private:
    unsigned int renderer_id;
    uint32_t count;
};

} // namespace gl
} // namespace baka


#endif