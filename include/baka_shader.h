#ifndef _BAKA_SHADER_H_
#define _BAKA_SHADER_H_

#include <unordered_map>
#include <baka_path_explorer.h>
#include <baka_uniforms.h>

namespace baka
{
    class Shader
    {
    public:
        static Shader *Create(char *vertSrc, char *fragSrc);
        static Shader *Load(const char *vertPath, const char *fragPath, ResourceType resourceType = ResourceType::ASSET);
        
        virtual ~Shader() {}
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void Destroy() = 0;
        virtual void SetUniform(UniformType shaderType, const char *name, void *data) = 0;

        const std::unordered_map<std::string, UniformType> &GetActiveUniforms()
        {
            return this->activeUniforms;
        }
        std::size_t GetUniformsTotalSize() { return this->uniformsTotalSize; }

    private:
        void UpdateUniformsTotalSize();

        static void GetUniforms(char *source, std::unordered_map<std::string, UniformType> &dst);

    private:
        std::unordered_map<std::string, UniformType> activeUniforms;
        std::size_t uniformsTotalSize;
    };
} // namespace baka


#endif