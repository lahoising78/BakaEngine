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

    void SetUniform(const char *uniformName, UniformValue value);
    UniformValue GetUniform(const char *uniformName);
    
    void Bind();

private:
    Shader *shader;
    std::unordered_map<std::string, void*> pointers;
    void *buffer;
};

} // namespace baka

#endif