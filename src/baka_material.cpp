#include <baka_logger.h>
#include <baka_material.h>

#include <baka_lights.h>

namespace baka
{
    
Material::Material(Shader *shader)
{
    BAKA_ASSERT(shader);
    this->shader = shader;

    std::size_t bufferSize = this->shader->GetUniformsTotalSize();
    this->buffer = malloc(bufferSize);
    const auto &activeUniforms = this->shader->GetActiveUniforms();
    char *ptr = (char*)this->buffer;

    for(auto pair : activeUniforms)
    {
        this->pointers[pair.first] = ptr;
        ptr += GetUniformSize(pair.second);
    }

    memset(this->buffer, 0, bufferSize);
}

Material::~Material()
{
    if(this->buffer) delete this->buffer;
}

void Material::SetUniform(const char *uniformName, UniformValue value)
{
    const auto &activeUniforms = this->shader->GetActiveUniforms();
    if(this->pointers.find(uniformName) != this->pointers.end())
    {
        memcpy(
            this->pointers[uniformName], 
            &value, 
            GetUniformSize(activeUniforms.at(uniformName))
        );
    }
}

UniformValue Material::GetUniform(const char *uniformName)
{
    const auto &activeUniforms = this->shader->GetActiveUniforms();
    UniformValue val(0.0f);
    if(this->pointers.find(uniformName) != this->pointers.end())
    {
        memcpy(
            &val, 
            this->pointers[uniformName], 
            GetUniformSize(activeUniforms.at(uniformName))
        );
    }
    return val;
}

void Material::Bind()
{
    const auto &activeUniforms = this->shader->GetActiveUniforms();
    for(auto pair : activeUniforms)
    {
        const char *uniformName = pair.first.c_str();
        this->shader->SetUniform(
            pair.second,
            uniformName,
            this->pointers[uniformName]
        );
    }
}

} // namespace baka