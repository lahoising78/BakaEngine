#include <baka_logger.h>
#include <baka_material.h>

namespace baka
{
    
Material::Material(Shader *shader)
{
    BAKA_ASSERT(shader);
    this->shader = shader;

    this->buffer = malloc(this->shader->GetUniformsTotalSize());
    const auto &activeUniforms = this->shader->GetActiveUniforms();
    char *ptr = (char*)this->buffer;

    for(auto pair : activeUniforms)
    {
        this->pointers[pair.first] = ptr;
        ptr += GetUniformSize(pair.second);
    }
}

Material::~Material()
{
    if(this->buffer) delete this->buffer;
}

} // namespace baka