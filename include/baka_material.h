#ifndef _BAKA_MATERIAL_H_
#define _BAKA_MATERIAL_H_

#include <baka_shader.h>

namespace baka
{
    
class Material
{
public:
    Material(Shader *shader);
    ~Material();

private:
    Shader *shader;
    std::unordered_map<std::string, void*> pointers;
    void *buffer;
};

} // namespace baka

#endif