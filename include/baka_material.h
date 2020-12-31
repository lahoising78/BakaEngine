#ifndef _BAKA_MATERIAL_H_
#define _BAKA_MATERIAL_H_

#include <baka_shader.h>

namespace baka
{
    
class Material
{
public:
    Material();

private:
    Shader *shader;
};

} // namespace baka

#endif